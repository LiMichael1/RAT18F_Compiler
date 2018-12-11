#include "syntax.h"
using namespace std;

int addr = 0;
int addr2 = 0;
string saved_string = " ";
Token saved_token;
string saved_type;
string saved2;
bool isGet = false;
bool isWhile = false;
stack<int> jump_stack;
vector<Instruction> instr_table(1000);
vector<Symbol> sym_table(100);
int line_address = 1;
int instr_address = 0;
int Memory_addr = 5000;
int symbol = 0;
int instr_size = 0;

Syntax::Syntax(vector<Token> t)
{
	for (size_t i = 0; i<t.size(); i++)
	{
		Tokens.push_back(t[i]);		//inserts the Tokens into the class
	}
	index = 0;
	currToken = Tokens[0];			//sets currToken to the first the First Token

	file.open("parseOutput.txt");	//opens output file for Syntax Rules

	file << "Token: " << setw(20) << currToken.TokenName << "\t\t Lexeme: " << currToken.LexemeName << endl << endl;
	cout << "Token: " << setw(20) << currToken.TokenName << "\t\t Lexeme: " << currToken.LexemeName << endl << endl;


}
Syntax::~Syntax()
{
	file.close();
}
bool Syntax::syn_error(string expected, string nonterminal)
{
	print_rules();

	file << "Error: Expected " << expected << " instead of " << currToken.TokenName << "(" << currToken.LexemeName << ") \n";
	file << "No Match for " << nonterminal << endl;
	file << "Line: " << currToken.LineNumber + 1 << endl;

	cout << "Error: Expected " + expected + " instead of " + currToken.TokenName + "( '" + currToken.LexemeName + "' ) \n";
	cout << "No Match for " + nonterminal << endl;
	cout << "Line: " << currToken.LineNumber + 1 << endl;

	print_table();
	system("pause");
	exit(EXIT_FAILURE);
	return false;
}

void Syntax::nextToken()
{
	int size = Tokens.size();
	if (index < size - 1)
	{
		index++;
		currToken = Tokens[index];

		file << "Token: " << setw(20) << currToken.TokenName << " Lexeme: " << currToken.LexemeName << endl << endl;

		cout << "Token: " << setw(20) << currToken.TokenName << " Lexeme: " << currToken.LexemeName << endl << endl;
	}
}

bool Syntax::Accept()
{
	int size = Tokens.size();
	if (index == size - 1)
	{
		file << "Success\n";
		cout << "Success\n";
		return true;
	}
	else
	{
		file << "Failure\n";
		cout << "Failure\n";
		return false;
	}
}

bool Syntax::Match(string str)	//for functions with multiple options
{
	if (currToken.LexemeName == str)
	{
		print_rules();
		file << "Match " << str << " and " << currToken.TokenName << "(" << currToken.LexemeName << ")" << endl << endl;
		cout << "Match " + str + " and " + currToken.TokenName + "(" + currToken.LexemeName + ")" << endl << endl;
		nextToken();
		return true;
	}
	else
	{
		return false;
	}
}
bool Syntax::Match_t(string str)	//for token names
{
	if (currToken.TokenName == str)
	{
		print_rules();
		file << "Match " << str << " and " << currToken.TokenName << "(" << currToken.LexemeName << ")\n\n";
		cout << "Match " + str + " and " + currToken.TokenName + "(" + currToken.LexemeName + ")\n\n";
		nextToken();
		return true;
	}
	else
	{
		return false;
	}
}

void Syntax::print_rules()
{
	for (size_t i = 0; i < rules.size(); i++)
	{
		file << rules[i] << endl;
		cout << rules[i] << endl;
	}
	rules.clear();
}





//<Rat18F> ::= $$ <Opt Declaration List> <Statement List> $$
bool Syntax::Rat18F()
{
	rules.push_back("<RAT18F> ::= $$ <Opt Declaration List> <Statement List> $$");
	if (((Match("$$")) ? true : syn_error("$$", "<RAT18F>")) && Opt_dec_list() && Statement_list() && ((Match("$$")) ? true : syn_error("$$", "<RAT18F>")))
		return Accept();
	else
		return false;
}

//<Qualifier> ::= int | boolean 
bool Syntax::Qualifier()
{

	if (currToken.LexemeName == "int")
	{
		saved_type = "int";
		rules.push_back("<Qualifier> ::= int\n");
		return Match("int");
	}
	if (currToken.LexemeName == "boolean")
	{
		saved_type = "boolean";
		rules.push_back("<Qualifier> ::= boolean\n");
		return Match("boolean");
	}
	else
	{
		return syn_error("int | boolean ", "<Qualifier>");
	}

}
//<Body> ::= { < Statement List> }
bool Syntax::Body()
{
	rules.push_back("<Body> ::= { < Statement List> }");
	if (Match("{"))
	{
		if (Statement_list())
		{
			return ((Match("}")) ? true : syn_error("}", "<Body>"));
		}
		else
			return false;
	}
	else
		return syn_error("{", "<Body>");
}
//<Opt Declaration List> ::= <Declaration List> | <Empty>
bool Syntax::Opt_dec_list()
{

	if (currToken.LexemeName == "int" || currToken.LexemeName == "boolean")
	{
		rules.push_back("<Opt Declaration List> ::= <Declaration List>");
		return Dec_list();
	}
	else
	{
		rules.push_back("<Opt Declaration List> ::= <Empty>");
		return Empty();
	}
}
//<Declaration List> ::= <Declaration> ; <Declaration List>'
bool Syntax::Dec_list()
{
	rules.push_back("<Declaration> ; <Declaration List>'");
	if (Dec())
		if (Match(";"))
			return Dec_list_prime();
		else
			return syn_error(";", "<Declaration List>");
	else
		return false;

}
//<Declaration List>' ::= <Declaration List> | <Empty>
bool Syntax::Dec_list_prime()
{
	if (currToken.LexemeName == "int" || currToken.LexemeName == "boolean")
	{
		rules.push_back("<Declaration List>' ::= <Declaration List>");
		return Dec_list();
	}
	else
	{
		rules.push_back("<Declaration List>' ::= <Empty>");
		return Empty();
	}
}
//<Declaration> ::= <Qualifier> <IDs>
bool Syntax::Dec()
{
	rules.push_back("<Declaration> ::= <Qualifier> <IDs>");
	if (Qualifier())
	{
		cout << saved_type << endl << endl;
		if (IDs())
		{
			return true;
		}
		else
			return false;
	}
	else
		return false;
}
//<IDs> ::= <Identifier> <IDs>'
bool Syntax::IDs()
{

	rules.push_back("<IDs> ::= <Identifier> <IDs>'");
	if (currToken.TokenName == "Identifier")
	{
		saved_token = currToken;
		saved_string = currToken.LexemeName;
		
		if (isGet)
		{
		}
		else
			insert_symtable(saved_token.LexemeName, saved_type);

		Match_t("Identifier");
		return IDs_prime();
	}
	else
		return syn_error("<Identifier>", "<IDs>");

}
//<IDs>' ::= , <IDs> | epilson
bool Syntax::IDs_prime()
{
	if (currToken.LexemeName == ",")
	{
		rules.push_back("<IDs>' ::= , <IDs>");
		Match(",");
		return IDs();
	}
	else
	{
		rules.push_back("<IDs>' ::= epilson");
		return Empty();
	}
}
//<Statement List> ::= <Statement> <Statement List>'
bool Syntax::Statement_list()
{
	rules.push_back("<Statement List> ::= <Statement> <Statement List>'");
	if (Statement())
		return Statement_list_prime();
	else
		return false;
}
//<Statement List>' ::= <Statement List> | epilson
bool Syntax::Statement_list_prime()
{
	string L = currToken.LexemeName;
	string T = currToken.TokenName;
	if (T == "Identifier" || L == "{" || L == "if" || L == "return" || L == "put" || L == "get" || L == "while")
	{
		rules.push_back("<Statement List>' ::= <Statement List>");
		return Statement_list();
	}
	else
	{
		rules.push_back("<Statement List>' ::= epilson");
		return Empty();
	}
}
//<Statement> ::= <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan> | <While>
bool Syntax::Statement()
{
	if (currToken.LexemeName == "{")
	{
		rules.push_back("<Statement> ::= <Compound>");
		return Compound();
	}
	else if (currToken.TokenName == "Identifier")
	{
		rules.push_back("<Statement> ::= <Assign>");
		return Assign();
	}
	else if (currToken.LexemeName == "if")
	{
		rules.push_back("<Statement> ::= <If>");
		return If();
	}
	else if (currToken.LexemeName == "return")
	{
		rules.push_back("<Statement> ::= <Return>");
		return Return();
	}
	else if (currToken.LexemeName == "put")
	{
		rules.push_back("<Statement> ::= <Print>");
		return Print();
	}
	else if (currToken.LexemeName == "get")
	{
		rules.push_back("<Statement> ::= <Print>");
		return Scan();
	}
	else if (currToken.LexemeName == "while")
	{
		rules.push_back("<Statement> ::= <While>");
		return While();
	}
	else
	{
		return syn_error("{ | <Identifier> | if | return | put | get | while", "<Statement>");
	}

}
//<Compound> ::= { <Statement List> }
bool Syntax::Compound()//same as Body?
{
	rules.push_back("<Compound> ::= { <Statement List> }\n");
	if (Match("{"))
	{
		if (Statement_list())
		{
			if (Match("}"))
			{
				return true;
			}
			else
				return syn_error("}", "<Compound>");
		}
		else
			return false;
	}
	else
		return syn_error("{", "<Compound>");
}
//<Assign> ::= <Identifier> = <Expression> ;
bool Syntax::Assign()
{
	rules.push_back("<Assign> ::= <Identifier> = <Expression> ;");
	if (currToken.TokenName == "Identifier" || currToken.TokenName == "Integer")
	{
		
		string a = get_type(currToken.LexemeName);
		if (a == "Empty")
		{
			return syn_error("variable doesn't exist in symbol table1", "<Assign>");
		}
		Token save = currToken;
		cout << "wowo " << save.LexemeName << save.TokenName << "\n\n\n\n";;
		Match_t("Identifier");
		if (Match("="))
		{
			if (Expression())
			{
				string b = get_type(saved_token.LexemeName);
				if (b == "Empty")
				{
					return syn_error("variable doesn't exist in symbol table2", "<Assign>");
				}
				if (a == b)
				{
					gen_instr("POPM", to_string(get_address(save.LexemeName)));
					return ((Match(";")) ? true : syn_error(";", "<Assign>"));
				}
				else
					return syn_error("Incorrect Assigning of variables" ,"<Assign>");
				
			}
			else
				return false;
		}
		else
			return syn_error("=", "<Assign>");
	}
	else
		return syn_error("<Identifier>", "<Assign>");
}
//<If> ::= if ( <Condition> ) <Statement> <If>'
bool Syntax::If()
{
	rules.push_back("<If> ::= if ( <Condition> ) <Statement> <If>'");
	if (currToken.LexemeName == "if")
	{
		addr2 = instr_address;
		Match("if");
		if (Match("("))
			if (Condition())
				if (Match(")"))
					if (Statement())
						return If_prime();
					else
						return false;
				else
					return syn_error(")", "<If>");
			else
				return false;
		else
			return syn_error("(", "<If>");
	}
	else
		return syn_error("if", "<If>");

}
//<If>' ::= ifend | else <Statement> ifend
bool Syntax::If_prime()
{
	if (currToken.LexemeName == "ifend")
	{
		gen_instr("JUMP", to_string(addr2));
		back_patch(instr_address);
		rules.push_back("<If>' ::= ifend");
		return Match("ifend");
	}
	if (currToken.LexemeName == "else")
	{
		rules.push_back("<If>' ::= else <Statement> ifend");
		Match("else");
		if (Statement())
		{
			if (currToken.LexemeName == "ifend")
			{
				gen_instr("JUMP", to_string(addr2));
				back_patch(instr_address);
				return ((Match("ifend")) ? true : syn_error("ifend", "<If>'"));
			}
			else
			{
				return false;
			}

		}
		else
			return false;
	}
	else
		return syn_error("ifend | else", "<If>'");
}
//<Return> ::= return <Return>'
bool Syntax::Return()
{
	if (currToken.LexemeName == "return")
	{
		rules.push_back("<Return> ::= return <Return>'");
		Match("return");
		return Return_prime();
	}
	else
		return syn_error("return", "<Return>");
}
// <Return>' ::= ; | <Expression>; | epilson
bool Syntax::Return_prime()
{

	string t = currToken.TokenName;
	string l = currToken.LexemeName;
	if (l == ";")
	{
		rules.push_back("<Return>' ::= ;");
		return ((Match(";")) ? true : syn_error(";", "<Return>'"));
	}
	else if (t == "Identifier" || t == "Integer" || l == "(" || l == "true" || l == "false")
	{
		rules.push_back("<Return>' ::= <Expression>");
		if (Expression())
			return ((Match(";")) ? true : syn_error(";", "<Return>'"));
		else
			return false;
	}
	else
	{
		rules.push_back("<Return>' ::= epilson");
		return Empty();
	}
}

//<Print> ::= put ( <Expression>);
bool Syntax::Print()
{
	if (currToken.LexemeName == "put")
	{
		rules.push_back("<Print> ::= put ( <Expression>);");
		Match("put");
		if (Match("("))
			if (Expression())
				if (Match(")"))
				{
					gen_instr("STDOUT", "nil");
					return ((Match(";")) ? true : syn_error(";", "<Print>"));
				}
				else
					return syn_error(")", "<Print>");
			else
				return false;
		else
			return syn_error("(", "<Print>");
	}
	else
		return syn_error("put", "<Print>");
}
//<Scan> ::= get ( <IDs> );
bool Syntax::Scan()
{
	if (currToken.LexemeName == "get")
	{
		isGet = true;
		rules.push_back("<Scan> ::= get ( <IDs> );");
		Match("get");
		if (Match("("))
			if (IDs())
			{
				cout << "STDIN and POPM\n\n\n";
				gen_instr("STDIN", "nil");
				gen_instr("POPM", to_string(get_address(saved_string)));
				if (Match(")"))
					return ((Match(";")) ? true : syn_error(";", "<Scan>"));
				else
					return syn_error(")", "<Scan>");
			}
			else
				return false;
		else
			return syn_error("(", "<Scan>");
	}
	else
		return syn_error("get", "<Scan>");;
}
//<While> ::= while ( <Condition> ) <Statement> whileend
bool Syntax::While()
{
	if (currToken.LexemeName == "while")
	{
		isWhile = true;
		int addr = instr_address;
		cout << "wow";
		gen_instr("LABEL", "nil");
		rules.push_back("<While> ::= while ( <Condition> ) <Statement> whileend");
		Match("while");
		if (Match("("))
			if (Condition())
				if (Match(")"))
					if (Statement())
					{
						gen_instr("JUMP", to_string(addr));
						back_patch(instr_address);
						return ((Match("whileend")) ? true : syn_error("whileend", "<While>"));
					}
					else
						return false;
				else
					return syn_error(")", "<While>");
			else
				return false;
		else
			return syn_error("(", "<While>");
	}
	else
		return syn_error("while", "<While>");
}
//<Condition> ::= <Expression> <Relop> <Expression>
bool Syntax::Condition()
{
	rules.push_back("<Condition> ::= <Expression> <Relop> <Expression>");
	if (Expression())
	{
		string a = get_type(saved_token.LexemeName);
		cout << "Boolean ? " << a << endl << endl;
		if (a != "Empty" && a != "boolean")
		{
			if (Relop())
			{
				string b = get_type(saved_token.LexemeName);
				cout << "Boolean ??? " << b << endl << endl;
				if (b != "Empty" && b!= "boolean")
				{
					if (a == b)
					{
						return Expression();
					}
					else
						return syn_error("variables aren't equal", "<Condition>");
				}
				else
					return syn_error("No boolean Arithmetic Operations", "Condition");
			}
			else
			{
				
				return false;
			}
			return true;
		}
		else
		{
			return syn_error("No boolean Arithmetic Operations", "Condition");
		}
	}
	else
		return false;
}
//<Relop> ::= == | ^= | > |<  | => |=<
bool Syntax::Relop()
{
	if (currToken.LexemeName == "==")
	{
		gen_instr("EQU", "nil");
		Push_JS(instr_address);
		gen_instr("JUMPZ", "nil");
		rules.push_back("<Relop> ::= ==");
		return Match("==");
	}
	//or
	else if (currToken.LexemeName == "^=")
	{
		gen_instr("NEQ", "nil");
		Push_JS(instr_address);
		gen_instr("JUMPZ", "nil");
		rules.push_back("<Relop> ::= ^=");
		return Match("^=");
	}
	//or
	else if (currToken.LexemeName == ">")
	{
		gen_instr("LES", "nil");
		Push_JS(instr_address);
		gen_instr("JUMPZ", "nil");
		rules.push_back("<Relop> ::= >");
		return Match(">");
	}
	//or
	else if (currToken.LexemeName == "<")
	{
		gen_instr("GRT", "nil");
		Push_JS(instr_address);
		gen_instr("JUMPZ", "nil");
		rules.push_back("<Relop> ::= <");
		return Match("<");
	}
	//or
	else if (currToken.LexemeName == "=>")
	{
		gen_instr("GEQ", "nil");
		Push_JS(instr_address);
		gen_instr("JUMPZ", "nil");
		rules.push_back("<Relop> ::= =>");
		return Match("=>");
	}
	//or
	else if (currToken.LexemeName == "=<")
	{
		gen_instr("LEQ", "nil");
		Push_JS(instr_address);
		gen_instr("JUMPZ", "nil");
		rules.push_back("<Relop> ::= =<");
		return Match("=<");
	}
	else
	{
		return syn_error("== | ^= | > |<  | => |=<", "<Relop>");
	}
}
//<Expression> ::= <Term> <Expression>'
bool Syntax::Expression()
{
	rules.push_back("<Expression> ::= <Term> <Expression>'");
	return Term() && ExpressionPrime();
}
// <Expression>' ::= +<Term> <Expression>' | -<Term> <Expression>' | epilson
bool Syntax::ExpressionPrime()
{
	if (currToken.LexemeName == "+" || currToken.LexemeName == "-")
	{
		string rule = "<Expression>' ::= " + currToken.LexemeName + "<Term> <Expression>'";
		rules.push_back(rule);

		string saved_symbol = currToken.LexemeName;

		Match(currToken.LexemeName);

		if (Term())
		{
			cout << "Saved: " << saved_symbol << endl;
			if (saved_symbol == "+")
			{
				gen_instr("ADD", "nil");
				cout << "WTF Bro \n\n";
			}
			else
				gen_instr("SUB", "nil");

			return ExpressionPrime();
		}
		else
			return false;
	}
	else
	{
		rules.push_back("<Expression>' ::= epilson");
		return Empty();
	}
}
// <Term> = <Factor> <Term>'
bool Syntax::Term()
{
	rules.push_back("<Term> ::= <Factor> <Term>'");
	return Factor() && TermPrime();
}
// <Term>? ::= * <Factor> <Term>? | / <Factor> <Term>? | epilson
bool Syntax::TermPrime()
{
	if (currToken.LexemeName == "*" || currToken.LexemeName == "/")
	{
		string rule = "<Term>' ::= " + currToken.LexemeName + "<Factor> <Term>'";
		rules.push_back(rule);

		string saved_symbol = currToken.LexemeName;

		Match(currToken.LexemeName);
		if (Factor())
		{
			(saved_symbol == "*") ? gen_instr("MUL", "nil") : gen_instr("DIV", "nil");

			return TermPrime();
		}
		else
			return false;
	}
	else //changable 
	{
		rules.push_back("<Term>' ::= epilson");
		return Empty();
	}
}
//<Factor> ::= - <Primary> | <Primary>
bool Syntax::Factor()
{
	if (currToken.LexemeName == "-")
	{
		rules.push_back("<Factor> ::= -<Primary>");
		Match("-");
		return Primary();
	}
	string t = currToken.TokenName;
	string l = currToken.LexemeName;
	if (t == "Identifier" || t == "Integer" || l == "(" || l == "true" || l == "false")
	{
		rules.push_back(("<Factor> ::= <Primary>"));
		return Primary();
	}
	else
	{
		return syn_error("- | <Identifier>| <Integer | '('|   true | false", "<Factor>");
	}

}
//<Primary> ::= <Integer> | <Identifier> <Primary>'  | ( <Expression> ) | true | false
bool Syntax::Primary()
{
	if (currToken.TokenName == "Identifier")
	{
		saved_token = currToken;
		gen_instr("PUSHM", to_string(get_address(currToken.LexemeName)));
		saved_string = currToken.LexemeName;
		rules.push_back("<Primary> ::= <Identifier> <Primary>'");
		if (Match_t("Identifier"))
			return Primary_prime();
		else
			return syn_error("<Identifier>", "<Primary>");
	}
	//or
	else if (currToken.TokenName == "Integer")
	{
		saved_token = currToken;
		cout << currToken.LexemeName << endl << endl;
		saved2 = "int";
		gen_instr("PUSHI", currToken.LexemeName);
		rules.push_back("<Primary> ::= <Integer>");
		return Match_t("Integer");
	}
	//or
	else if (currToken.LexemeName == "(")
	{
		rules.push_back("<Primary> ::= (<Expression>)");
		Match("(");
		if (Expression())
		{
			return ((Match(")")) ? true : syn_error(")", "<Primary>"));
		}
		else
			return false;
	}
	//or
	else if (currToken.LexemeName == "true")
	{
		saved_token = currToken;
		gen_instr("PUSHI", "1");
		rules.push_back("<Primary> ::= true");
		return Match("true");
	}
	//or
	else if (currToken.LexemeName == "false")
	{
		saved_token = currToken;
		gen_instr("PUSHI", "0");
		rules.push_back("<Primary> ::= false");
		return Match("false");
	}
	else
	{
		return syn_error("<Identifier>| <Integer | '('|   true | false", "<Primary>");
	}
}
//<Primary>' ::= ( <IDs> ) | epilson
bool Syntax::Primary_prime()
{
	if (currToken.LexemeName == "(")
	{
		rules.push_back("<Primary>' ::= ( <IDs> )");
		Match("(");
		if (IDs())
			return ((Match(")")) ? true : syn_error(")", "<Primary>'"));
		else
			return false;
	}
	else
	{
		rules.push_back("<Primary>' ::= epilson");
		return Empty();
	}
}

//<Empty> ::= epilson
bool Syntax::Empty()
{
	//go to back to previous tokens then return??
	return true;
}


void gen_instr(string op, string oprnd)
/* instr_address  shows the current insturction address is global */
{
	Instruction n;
	n.address = line_address;
	n.op = op;
	n.oprnd = oprnd;
	instr_table[instr_address] = n;

	cout << "Instruction: " << instr_table[instr_address].op << endl;
	instr_address++;
	line_address++;
	instr_size++;
	
}

void back_patch(int jump_addr)
{

	int addr = Pop_JS();
	instr_table[addr].oprnd = to_string(jump_addr);

}
int get_address(string lexeme)
{
	int addr = 0;
	size_t size = 0;
	bool found = false;

	while (!found && size < symbol)
	{
		if (sym_table[size].lexeme == lexeme)
		{
			found = true;
			addr = sym_table[size].mem_addr;
		}
		size++;
	}
	return addr;

}
void Push_JS(int addr)
{
	jump_stack.push(addr);
}

int Pop_JS()
{
	int s = -1;
	if (!jump_stack.empty())
	{
		s = jump_stack.top();
		jump_stack.pop();
	}
	else
	{
		cerr << "Error : nothing in the stack\n";
	}
	return s;
}
bool is_number(string str)
{
	bool has_only_digits = true;
	for (int i = 0; i < (strlen(str.c_str()) - 1); i++) {
		if (!isdigit(str[i])) {
			return false;
		}
	}
	return has_only_digits;
}
string get_type(string lex)
{
	bool flag = false;
	if (exists_symtable(lex))
	{
		int x = sym_table_type(lex);
		if (x != -1)
		{
			return sym_table[x].type;
		}
	}
	if (is_number(lex))
	{
		return "int";
	}
	if (lex == "true" || lex == "false")
	{
		return "boolean";
	}
	else
	{
		return "Empty";
	}
}
int sym_table_type(string lex)
{

	for (int i = 0; i< symbol; i++)
	{
		if (sym_table[i].lexeme == lex)
		{
			return i;
		}
	}
	cerr << "Doesn't exist\n";
	return -1;

}

//Checks to see if it's in the table
bool exists_symtable(string lex)
{
	for (int i = 0; i< symbol; i++)
	{

		if (sym_table[i].lexeme == lex)
		{
			return true;
		}
	}
	return false;
}
//insert into the symbol table
void insert_symtable(string lex, string type)
{
	
	if (exists_symtable(lex))
	{
		cerr << lex << "already exists\n";
	}
	else
	{
		if (type == "Real")
		{
			cerr << "Doesn't exist\n";
		}
		else
		{
			Symbol s;
			s.lexeme = lex;
			s.type = type;
			s.mem_addr = Memory_addr;
			sym_table[symbol] = s;
			cout << "lex: " << lex << "\n\n\n\n";
			cout << "Insert " << sym_table[symbol].lexeme << endl;
			cout << "Type " << sym_table[symbol].type << endl << endl;
			cout << "Memory: " << sym_table[symbol].mem_addr << endl;
			Memory_addr++;
			symbol++;
			
		}
	}


}

//printing functions

void print_table()
{
	ofstream outputFile;
	outputFile.open("tableOutput.txt");

	cout << left << setw(20) << "Lexeme" << setw(20) << "Memory address" << setw(20) << "type" << endl;
	outputFile << setw(20) << "Lexeme" << setw(20) << "Memory address" << setw(20) << "type" << endl;
	for (int i = 0; i< symbol; i++)
	{
		cout << setw(20) << sym_table[i].lexeme << setw(20) << sym_table[i].mem_addr << setw(20) << sym_table[i].type << endl;
		outputFile << setw(20) << sym_table[i].lexeme << setw(20) << sym_table[i].mem_addr << setw(20) << sym_table[i].type << endl;
	}
	cout << endl << setw(20) << "Address" << setw(20) << "Op" << setw(20) << "Oprnd" << endl;
	outputFile << endl << setw(20) << "Address" << setw(20) << "Op" << setw(20) << "Oprnd" << endl;
	for (int i = 0; i< instr_size; i++)
	{
		cout << setw(20) << instr_table[i].address << setw(20) << instr_table[i].op << setw(20) << instr_table[i].oprnd << endl;
		outputFile << setw(20) << instr_table[i].address << setw(20) << instr_table[i].op << setw(20) << instr_table[i].oprnd << endl;
	}

	outputFile.close();
}