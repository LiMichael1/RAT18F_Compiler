#include "syntax.h"
#include "fsm.h"

using namespace std;

//get linenumber for the  print functions??
Syntax::Syntax(vector<Token> t)
{
	for(int i =0; t.size(); i++)
	{
		Tokens[i] = t[i];
	}
	index = 0;
}
void Syntax::syn_error(Token t, string nonterminal)
{
	cout << t.TokenName + ":" +t.LexemeName + " is not expected\n";
	cout << "No Match for " + nonterminal << endl;
	exit(EXIT_FAILURE);
}

Token Syntax::nextToken()		//???"
{
	index++;
	currToken = Tokens[index];

	cout << "Token: " + currToken.TokenName + "\t\t Lexeme: " + currToken.LexemeName << endl;
	return currToken;
}

bool Syntax::Accept ()
{
	int size = rules.size();
	if(index == size -1)
	{
		cout << "Success\n";
		return true;
	}
}

bool Syntax::Match(string str)	//for functions with multiple options
{
	if(currToken.LexemeName == str)
	{
		print_rules();
		cout << "Match " + str + " and " + currToken.TokenName + ":" + currToken.LexemeName << endl;
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
	if(currToken.TokenName == str)
	{
		print_rules();
		cout << "Match " + str + " and " + currToken.TokenName + ":" + currToken.LexemeName << endl;
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
	for(int i = 0; rules.size(); i++)
		cout << rules[i]<< endl;
	rules.clear();
}





//<Rat18F> ::= <Opt Function Definitions> $$ <Opt Declaration List> <Statement List> $$
bool Syntax::Rat18F() 
{
	nextToken();//first token
	rules.push_back("<RAT18F> ::= <Opt Function Definitions> $$ <Opt Declaration List> <Statement List> $$");
	toggle.push_back(1);
	if(Opt_func_def() && Match("$$") && Opt_dec_list() && Statement_list() && Match("$$"))
		return Accept();

		  
	//Accepting State
}

//<Opt Function Definitions> ::= <Function Definitions> | <Empty>
bool Syntax::Opt_func_def()
{   

	if (currToken.LexemeName == "function")
	{
		rules.push_back("<Opt Function Definitions> ::= <Function Definitions>");
		return ((Func_def())?true:false);
	}
		
	else 
	{	
		rules.push_back("<Opt Function Definitions> ::= <Empty>");	
		return Empty();
	}
}

//<Function Definitions> ::= <Function> <Function Definitions>'
bool Syntax::Func_def() 
{
	rules.push_back("<Function Definitions> ::= <Function> <Function Definitions>'");
	if(Function())
		if(Func_def_prime())
			return true;
		else 
			return false;
	else
		return false;
}
//<Function Definition>' ::= <Function Definitions> | <Empty>
bool Syntax::Func_def_prime()
{
	if(currToken.LexemeName == "function")
	{  
		rules.push_back("<Function Definition>' ::= <Function Definitions> ");
		return ((Func_def())?true:false);
	}
	else 
	{	
		rules.push_back("<Function Definition>' ::= <Empty");
		return Empty();
	}
}
//<Function> ::= function <Identifier> ( <Opt Parameter List>) <Opt Declaration List> <Body>
bool Syntax::Function()
{
	rules.push_back("<Function> ::= function <Identifier> ( <Opt Parameter List>) <Opt Declaration List> <Body>");
	if (Match("function"))
	{
		if (Match_t("Identifier"))
			if (Match("{"))
				if(Opt_para_list())
					if (Match("}"))
						if(Opt_dec_list())
							if(Body())
								return true;
							else 
								return false;
						else
							return false;
					else
						return false;
				else 
					return false;
			else 
				return false;
		else
			return false;
	}
	else 
		return false;
}
//<Opt Parameter List> ::= <Parameter List> | <Empty>
bool Syntax::Opt_para_list() 
{
	if (currToken.TokenName == "Identifier")
	{
		rules.push_back("<Opt Parameter List> ::= <Parameter List>");
		return ((Para_list())?true:false);
	}
	else 
	{
		rules.push_back("<Opt Parameter List> ::= <Empty>");
		return Empty();
	}
}
//<Parameter List> ::= <Parameter> <Parameter List>'
bool Syntax::Para_list()
{
	rules.push_back("<Parameter List> ::= <Parameter> <Parameter List>'");
	if(Parameter())
	{
		if(Para_list_prime())
			return true;
		else 
			return false;
	}
	else
		return false;
	
}
//<Parameter List>' ::= , <Parameter List> | epilson
bool Syntax::Para_list_prime()
{
	if(Match(","))
	{
		if(currToken.TokenName == "Identifier")
		{
			rules.push_back("<Parameter List>' ::= , <Parameter List> ");
			return Para_list();
		}
		else 
			return Empty();
	}
	else 
	{
		rules.push_back("<Parameter List>' ::= epilson");
		return Empty();
	}
}
//<Parameter> ::= <IDs > : <Qualifier>
bool Syntax::Parameter()
{
	rules.push_back("<Parameter> ::= <IDs > : <Qualifier>\n");
	if (IDs())
		if (Match(":"))
			if (Qualifier())
				return true;
			else 
				return false;
		else 
			return false;
	else
		return false;
}
//<Qualifier> ::= int | boolean | real
bool Syntax::Qualifier()
{
	
	if (currToken.LexemeName =="int") 
	{
		rules.push_back("<Qualifier> ::= int\n");
		Match("int");
		return true;
	}
	if (currToken.LexemeName =="boolean") 
	{
		rules.push_back("<Qualifier> ::= boolean\n");
		Match("boolean");
		return true;
	}
	if (currToken.LexemeName =="real") 
	{	
		rules.push_back("<Qualifier> ::= real\n");
		Match("real");
		return true;
	}
	else 
	{
		//syn_error("Expected: int, boolean, real\nGot %s:%s\n", currToken.TokenName, currToken.LexemeName)
		return false;
	}

}
//<Body> ::= { < Statement List> }
bool Syntax::Body()
{
	if (Match("{"))
	{
		if(Statement_list())
		{
			if (Match("}"))
				return true;
		}
		else
			return false;
	}
	else 
		return false;
}
//<Opt Declaration List> ::= <Declaration List> | <Empty>
bool Syntax::Opt_dec_list()
{
	
	if (currToken.LexemeName == "int" || currToken.LexemeName == "boolean" || currToken.LexemeName == "real")
	{
		rules.push_back("<Opt Declaration List> ::= <Declaration List>");
		return ((Dec_list())? true:false);
	}
	else 		//or
		return Empty();
}
//<Declaration List> ::= <Declaration> ; <Declaration List>'
bool Syntax::Dec_list()
{
	rules.push_back("<Declaration> ; <Declaration List>'");
	if(Dec())
		if (Match(";"))
			return((Dec_list_prime())?true:false);
		else 
			return false;
	else 
		return false;

}
//<Declaration List>' ::= <Declaration List> | <Empty>
bool Syntax::Dec_list_prime()
{
	return ((Opt_dec_list()?true:false));
}
//<Declaration> ::= <Qualifier> <IDs>
bool Syntax::Dec()
{
	rules.push_back("<Declaration> ::= <Qualifier> <IDs>");
	if(Qualifier())
		return ((IDs())?true:false);
	else 
		return false;
}
//<IDs> ::= <Identifier> <IDs>'
bool Syntax::IDs()
{
	rules.push_back("<IDs> ::= <Identifier> <IDs>'");
	if (Match_t("Identifier"))
		return((IDs_prime())?true:false);
	else 
		return false;

}
//<IDs>' ::= , <IDs> | epilson
bool Syntax::IDs_prime()
{
	if(currToken.LexemeName == ",")
	{
		rules.push_back("<IDs>' ::= , <IDs>");
		Match(",");
		return((IDs_prime())?true:false);
	}
	else
	{
		return Empty();
	}
}
//<Statement List> ::= <Statement> <Statement List>'
bool Syntax::Statement_list()
{
	if(Statement())
		return Statement_list_prime();
	else 
		return false;
}
//<Statement List>' ::= <Statement List> | epilson
bool Syntax::Statement_list_prime()
{
	string L = currToken.LexemeName;
	string T = currToken.TokenName;
	if(T=="Identifier" || L == "{" || L == "if" || L == "return" || L == "put" || L=="get" || L== "while")
	{
		rules.push_back("<Statement List>' ::= <Statement List>");
		return((IDs_prime())?true:false); 
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
	if(currToken.LexemeName== "{")
	{
		rules.push_back("<Statement> ::= <Compound>");
		return ((Compound())?true:false);
	}	
	else if(currToken.TokenName== "Identifier")
	{
		rules.push_back("<Statement> ::= <Assign>");
		return ((Assign())?true:false);
	}
	else if(currToken.LexemeName== "if")
	{
		rules.push_back("<Statement> ::= <If>");
		return ((If())?true:false);
	}
	else if(currToken.LexemeName== "return")
	{	
		rules.push_back("<Statement> ::= <Return>");
		return ((Return())?true:false);
	}
	else if(currToken.LexemeName== "put")
	{	
		rules.push_back("<Statement> ::= <Print>");
		return ((Print())?true:false);
	}
	else if(currToken.LexemeName== "get") 
	{
		rules.push_back("<Statement> ::= <Print>");
		return ((Scan())?true:false);
	}
	else if(currToken.LexemeName== "while")
	{
		rules.push_back("<Statement> ::= <While>");
		return ((While())?true:false);
	}
	else
	{
		//error
		return false;
	}

}
//<Compound> ::= { <Statement List> }
bool Syntax::Compound()//same as Body?
{
	rules.push_back("<Compound> ::= { <Statement List> }\n");
	if (Match("{"))
	{
		if(Statement_list())
			return((Match("}"))?true:false);
		else 
			return false;
	}
	else 
		return false;
}
//<Assign> ::= <Identifier> = <Expression> ;
bool Syntax::Assign()
{
	rules.push_back("<Assign> ::= <Identifier> = <Expression> ;");
	if (Match_t("Identifier"))
		if (Match("="))
			return ((Expression())?true:false);
		else
			return false;
	return false;
}
//<If> ::= if ( <Condition> ) <Statement> <If>'
bool Syntax::If()
{
	rules.push_back("<If> ::= if ( <Condition> ) <Statement> <If>'");
	if (Match("if"))
		if (Match("("))
			if(Condition())
				if (Match(")"))
					if(Statement())
						return If_prime();
					else
						return false;
				else
					return false;
			else
				return false;
		else
			return false;
	else
		return false;

}
//<If>' ::= ifend | else <Statement> ifend
bool Syntax::If_prime()
{
	if(currToken.LexemeName == "ifend")
	{
		rules.push_back("<If>' ::= ifend");
		return Match("ifend");
	}

	else if (currToken.LexemeName == "else")
	{
		rules.push_back("<If>' ::= else <Statement> ifend");
		Match("else");
		if(Statement())
			return Match("ifend");
	}
	else
		return false;

}
//<Return> ::= return <Return>'
bool Syntax::Return()
{
	if (Match("return"))
	{
		rules.push_back("<Return> ::= return <Return>'");
		Match("<Return> ::= return <Return>'");
		return Return_prime();
	}
	else 
		return false;
}
// <Return>' ::= <Expression> | epilson
bool Syntax::Return_prime()
{
	string t = currToken.TokenName;
	string l = currToken.LexemeName;
	if(t == "Identifier" || t == "Integer" || t == "Real" || l == "(" || l == "true" || l == "false")
	{
		return ((Expression())?true:false);
	}
	else 
		return Empty();
}

//<Print> ::= put ( <Expression>);
bool Syntax::Print()
{
	if (currToken.LexemeName == "put")
	{
		rules.push_back("<Print> ::= put ( <Expression>);");
		Match("put");
		if (Match("("))
			if(Expression())
				if (Match (")"))
					return ((Match(";"))?true:false);
				else
					return false;
			else
				return false;
		else
			return false;
	}
	else 
		return false;
}
//<Scan> ::= get ( <IDs> );
bool Syntax::Scan()
{
	if (currToken.LexemeName == "get")
	{
		rules.push_back("<Scan> ::= get ( <IDs> );");
		Match("get");
		if (Match("("))
			if(IDs())
				if (Match(")"))
					return(Match(";"));
				else
					return false;
			else 
				return false;
		else
			return false;
	}
	else
		return false;
}
//<While> ::= while ( <Condition> ) <Statement> whileend
bool Syntax::While()
{
	if (currToken.LexemeName == "while")
	{
		rules.push_back("<While> ::= while ( <Condition> ) <Statement> whileend");
		Match("while");
		if (Match("("))
			if(Condition())
				if (Match(")"))
					if (Statement())
						return (Match("whileend"));
					else
						return false;
				else
					return false;
			else
				return false;
		else 
			return false;
	}
	else
		return false;
}
//<Condition> ::= <Expression> <Relop> <Expression>
bool Syntax::Condition()
{
	rules.push_back("<Condition> ::= <Express//ion> <Relop> <Expression>");
	if(Expression())
		if(Relop())
			return Expression();
		else
			return false;
	else
		return false;
}
//<Relop> ::= == | ^= | > |<  | => |=<
bool Syntax::Relop()
{
	nextToken();
	if (currToken.LexemeName == "==")
	{
		rules.push_back("<Relop> ::= ==");
		Match("==");
		return true;
	}
		//or
	else if (currToken.LexemeName == "^=")
	{
		rules.push_back("<Relop> ::= ^=");
		Match("^=");
		return true;
	}
		//or
	else if (currToken.LexemeName == ">")
	{
		rules.push_back("<Relop> ::= >");
		Match(">");
		return true;
	}
		//or
	else if (currToken.LexemeName == "<")
	{
		rules.push_back("<Relop> ::= <");
		Match("<");
		return true;
	}
		//or
	else if (currToken.LexemeName == "=>")
	{
		rules.push_back("<Relop> ::= =>");
		Match("=>");
		return true;
	}
		//or
	else if (currToken.LexemeName == "<=")
	{
		rules.push_back("<Relop> ::= <=");
		Match("<=");
		return true;
	}
	else
	{
		//syn_error("No match for <Relop>\nExpected == | ^= | > |<  | => |=<");
		return false;
	}
}
//<Expression> ::= <Term> <Expression>’
bool Syntax::Expression()
{
	rules.push_back("<Expression> ::= <Term> <Expression>'\n");
	return Term() && ExpressionPrime();
}
// <Expression>’ ::= +<Term> <Expression>’ | -<Term> <Expression>’ | epilson
bool Syntax::ExpressionPrime()
{
	if (currToken.LexemeName == "+" || currToken.LexemeName == "-")
	{
		string rule = "<Expression>' ::= " + currToken.LexemeName + "<Term> <Expression>'";
		rules.push_back(rule);
		Match(currToken.LexemeName);
		return Term() && ExpressionPrime();
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
// <Term>’ ::= * <Factor> <Term>’ | / <Factor> <Term>’ | epilson
bool Syntax::TermPrime()
{
	if (currToken.LexemeName == "*" || currToken.LexemeName == "/")
	{
		string rule = "<Term>' ::= " + currToken.LexemeName + "<Factor> <Term>'";
		rules.push_back(rule);
		Match(currToken.LexemeName);
		return Factor() && TermPrime();
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
		return Primary();
	}
	string t = currToken.TokenName;
	string l = currToken.LexemeName;
	if(t == "Identifier" || t == "Integer" || t == "Real" || l == "(" || l == "true" || l == "false")
	{
		rules.push_back(("<Factor> ::= <Primary>"));
		return Primary();
	}
	else
	{
		return false;
	}
	
}
//<Primary> ::= <Identifier> | <Integer> | <Identifier> ( <IDs> ) | ( <Expression> ) | <Real> | true | false
bool Syntax::Primary()
{
	if (currToken.TokenName == "Identifier")
	{	
		if (currToken.LexemeName=="(")
		{
			Match_t("Identifier");
			Match("(");
			if (IDs())
			{
				if (Match(")"))
				{
					rules.push_back("<Primary> ::= <Identifier> ( <IDs> )");
					return true;
				}
			}
		}
		else
		{
			Match_t("Identifier");
			rules.push_back("<Primary> ::= <Identifier>");
			return true;
		}
	}
	//or
	else if (currToken.TokenName == "Integer")
	{ 
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
			return Match(")");
		}
		else
			return false;
	}
		//or
	else if (currToken.TokenName == "Real")
	{
		rules.push_back("<Primary> ::= <Real>");
		return Match_t("Real");
	}
		//or
	else if (currToken.LexemeName == "true")
	{
		rules.push_back("<Primary> ::= true");
		return Match("true");
	}
		//or
	else if (currToken.LexemeName == "false")
	{
		rules.push_back("<Primary> ::= false");
		return Match("false");
	}
	else
	{
		//syn_error("<Identifier> | <Integer> | <Identifier> ( <IDs> ) | ( <Expression> ) | <Real> | true | false" , "<Primary>");
		return false;
	}
}	
//<Empty> ::= epilson
bool Syntax::Empty()
{
	//go to back to previous tokens then return??
	return true;
}
