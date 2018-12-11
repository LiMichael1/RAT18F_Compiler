#include "syntax.h"
#include "semantics.h"
using namespace std;

int addr;
int addr2;
string saved_string = " ";
Token saved_token;
string saved_type;
bool isGet = false;
bool isWhile = false;
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
	file << "Line: " << currToken.LineNumber+1 << endl;

	cout << "Error: Expected " + expected + " instead of " + currToken.TokenName + "( '" + currToken.LexemeName + "' ) \n";
	cout << "No Match for " + nonterminal << endl;
	cout << "Line: " << currToken.LineNumber+1 << endl;
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
	rules.push_back("<RAT18F> ::= <Opt Function Definitions> $$ <Opt Declaration List> <Statement List> $$");
	if ( ((Match("$$")) ? true : syn_error("$$", "<RAT18F>")) && Opt_dec_list() && Statement_list() && ((Match("$$")) ? true : syn_error("$$", "<RAT18F>")))
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

	if (currToken.LexemeName == "int" || currToken.LexemeName == "boolean" )
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
		if(IDs())
		{
			insert_symtable(saved_token.LexemeName, saved_type);
		}
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
		if(!isGet)
		{
			insert_symtable(saved_token.LexemeName, saved_type);
		}
		
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
			if(Match("}"))
			{
				if(isWhile)
					gen_instr("JUMP", to_string(addr)); 
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
	if (currToken.TokenName == "Identifier")
	{	
		string a = get_type(currToken.LexemeName);
		if(a == "Empty")
		{
			return syn_error("variable doesn't exist in symbol table", "<Assign>");
		}
		Token save = currToken;
		Match_t("Identifier");
		if (Match("="))
		{
			if (Expression())
			{
				string b = get_type(currToken.LexemeName);
				if(b == "Empty")
				{
					return syn_error("variable doesn't exist in symbol table", "<Assign>");
				}
				if(a == b)
				{
					gen_instr("POPM", to_string(get_address(save.LexemeName)));
					return ((Match(";")) ? true : syn_error("<Identifier>", "<Assign>"));
				}
				else
					return syn_error("Variables don't match ", "<Assign>");
			}
			else
				return false;
		}
		else
			return syn_error("=", "<Assign>");
	}
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
			if(currToken.LexemeName == "ifend")
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
		gen_instr("STDOUT", "nil");
		rules.push_back("<Print> ::= put ( <Expression>);");
		Match("put");
		if (Match("("))
			if (Expression())
				if (Match(")"))
					return ((Match(";")) ? true : syn_error(";", "<Print>"));
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
				gen_instr("STDIN", "nil");
				gen_instr("POPM" , to_string(get_address(saved_string)));
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
		string a = get_type(currToken.LexemeName);
		if(a != "Empty")
		{
			if (Relop())
			{
				string b = get_type(currToken.LexemeName);
				if(b != "Empty")
				{
					if(a == b)
					{
						return Expression();
					}
					else 
						return syn_error("variables aren't equal", "<Condition>");
				}
				else
				{
					cerr<< "No Boolean Arithmetic Operations\n";
					return false;
				}
			}
			else
				return false;
		}
		else
		{

		else
		{
			cerr<< "No Boolean Arithmetic Operations\n";
			return false;
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
		gen_instr ("EQU", "nil");
        	Push_JS (instr_address);  
        	gen_instr ("JUMPZ", "nil");  
		rules.push_back("<Relop> ::= ==");
		return Match("==");
	}
	//or
	else if (currToken.LexemeName == "^=")
	{
		gen_instr ("NEQ", "nil");
        	Push_JS (instr_address); 
        	gen_instr ("JUMPZ", "nil");
		rules.push_back("<Relop> ::= ^=");
		return Match("^=");
	}
	//or
	else if (currToken.LexemeName == ">")
	{
		gen_instr ("LES", "nil");
        	Push_JS (instr_address);  
        	gen_instr ("JUMPZ", "nil");
		rules.push_back("<Relop> ::= >");
		return Match(">");
	}
	//or
	else if (currToken.LexemeName == "<")
	{
		gen_instr ("GRT", "nil");
       		Push_JS (instr_address); 
        	gen_instr ("JUMPZ", "nil");
		rules.push_back("<Relop> ::= <");
		return Match("<");
	}
	//or
	else if (currToken.LexemeName == "=>")
	{
		gen_instr ("GEQ", "nil");
        	Push_JS (instr_address);  
        	gen_instr ("JUMPZ", "nil");
		rules.push_back("<Relop> ::= =>");
		return Match("=>");
	}
	//or
	else if (currToken.LexemeName == "=<")
	{
		gen_instr ("LEQ", "nil");
        	Push_JS (instr_address); 
        	gen_instr ("JUMPZ", "nil");
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
			(saved_symbol == "+")?gen_instr("ADD", "nil"):gen_instr("SUB", "nil");

			return ExpressionPrime();
		}
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
		if(Factor())
		{
			(saved_symbol == "*")?gen_instr("MUL", "nil"):gen_instr("DIV", "nil");

			return TermPrime();
		}
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
	if (t == "Identifier" || t == "Integer"  || l == "(" || l == "true" || l == "false")
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
		gen_instr("PUSHI" , "1");
		rules.push_back("<Primary> ::= true");
		return Match("true");
	}
	//or
	else if (currToken.LexemeName == "false")
	{
		gen_instr("PUSHI" , "0");
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
