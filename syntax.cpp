#include "syntax.h"
#include "fsm.h"

#include <iostream>

using namespace std;

//get linenumber for the print functions??

Token Syntax::nextToken()		//???
{
	//return ((i == 0) ? v[i] : v[++i]);
	//updates current token
}

bool Syntax::Accept ()
{

}

bool Syntax::Match(Token t)
{

	if(t.LexemeName == currToken.LexemeName)
	{
		printf("Match %s and %s:%s\n", t.LexemeName, currToken.TokenName, currToken.LexemeName);
		return true;
	}
	else
	{
		printf("No Match for %s\n", t.LexemeName);
		return false;
	}
}
bool Syntax::check_input(Token t)
{
	return t.LexemeName == nextToken().LexemeName;
}

//<Rat18F> ::= <Opt Function Definitions> $$ <Opt Declaration List> <Statement List> $$
bool Syntax::Rat18F() 
{
	return Opt_func_def() &&
		   
	
	Opt_func_def();
	if (nextToken().LexemeName == "$$")
	Opt_dec_list();
	Statement_list();
	if (nextToken().LexemeName == "$$")
	//Accepting State
}

//<Opt Function Definitions> ::= <Function Definitions> | <Empty>
bool Syntax::Opt_func_def()
{
	printf("<RAT18F> ::= <Opt Function Definitions> $$ <Opt Declaration List> <Statement List> $$\n");
	if (Func_def())
	
		
	else if(Empty())		//or
		Empty();
}

//<Function Definitions> ::= <Function> | <Function> <Function Definitions>
bool Syntax::Func_def() 
{
	if ()
		Function();
	else if ()		//or
	{
		Function();
		Func_def();
	}
}
//<Function> ::= function <Identifier> ( <Opt Parameter List>) <Opt Declaration List> <Body>
bool Syntax::Function()
{
	if (nextToken().LexemeName == "function")
	{
		if (nextToken().TokenName == "Identifier")
			if (nextToken().LexemeName == "{")
				Opt_para_list();
		if (nextToken().LexemeName == "}")
			Opt_dec_list();
		Body();
	}
}
//<Opt Parameter List> ::= <Parameter List> | <Empty>
bool Syntax::Opt_para_list() 
{
	if ()
		Parameter();
	else if ()		//or
		Empty();
}
//<Parameter List> ::= <Parameter> <Parameter List>'
bool Syntax::Para_list()
{
	Parameter();
	Para_list_prime();
}
//<Parameter List>' ::= , <Parameter List> | epilson
bool Syntax::Para_list_prime()
{

}
//<Parameter> ::= <IDs > : <Qualifier>
bool Syntax::Parameter()
{
	if (nextToken().TokenName == "Identifier")

	if (nextToken().LexemeName == ".")

	Qualifier();
}
//<Qualifier> ::= int | boolean | real
bool Syntax::Qualifier()
{
	Token t = nextToken();
	if (t.LexemeName == "int")
	{
		printf("Match %s and %s:int", t.LexemeName , t.TokenName);
		return true;
	}
	else if (t.LexemeName == "boolean")//or
	{
		printf("Match %s and %s:boolean", t.LexemeName , t.TokenName);
		return true;
	}	
	else if (t.LexemeName == "real")//or
	{
		printf("Match %s and %s:real", t.LexemeName , t.TokenName);
		return true;
	}

}
//<Body> ::= { < Statement List> }
bool Syntax::Body()
{
	if (nextToken().LexemeName == "{")
	{
		if(Statement_list())
		{
			if (nextToken().LexemeName == "}")
		}
	}
}
//<Opt Declaration List> ::= <Declaration List> | <Empty>
bool Syntax::Opt_dec_list()
{
	if ()
		Dec_list();
	else if()		//or
		Empty();
}
//<Declaration List> ::= <Declaration> ; <Declaration List>'
bool Syntax::Dec_list()
{
	Dec();
		if (nextToken().LexemeName == ";")
			Dec_list_prime();
}
//<Declaration List>' ::= <Declaration List> | <Empty>
bool Syntax::Dec_list_prime()
{
	
}
//<Declaration> ::= <Qualifier > <IDs>
bool Syntax::Dec()
{
	Qualifier();
	IDs();
}
//<IDs> ::= <Identifier> <IDs>'
bool Syntax::IDs()
{
	if (nextToken().TokenName == "Identifier")
		//or
	if (nextToken().TokenName == "Identifier")
	IDs();

}
//<IDs>' ::= , <IDs> | epilson
bool Syntax::IDs_prime()
{

}
//<Statement List> ::= <Statement> | <Statement> <Statement List>
bool Syntax::Statement_list()
{
	Statement();
	//or 
	Statement();
	Statement_list();
}
//<Statement> ::= <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan> | <While>
bool Syntax::Statement()
{
	Compound();
	//or
	Assign();
	//or
	If();
	//or
	Return();
	//or
	Print();
	//or 
	Scan();
	//or
	While();

}
//<Compound> ::= { <Statement List> }
bool Syntax::Compound()//same as Body?
{
	if (nextToken().LexemeName == "{")
	Statement_list();
	if (nextToken().LexemeName == "}")
}
//<Assign> ::= <Identifier> = <Expression> ;
bool Syntax::Assign()
{
	if (nextToken().TokenName == "Identifier")
	if (nextToken().LexemeName == "=")
	Expression();
}
//<If> ::= if ( <Condition> ) <Statement> <If>'
bool Syntax::If()
{
	if (nextToken().LexemeName == "if")
	if (nextToken().LexemeName == "(")
	Condition();
	if (nextToken().LexemeName == ")")
	Statement();
	If_prime();

}
//<If>' ::= ifend | else <Statement> ifend
bool Syntax::If_prime()
{

}
//<Return> ::= return <Return>'
bool Syntax::Return()
{
	if (nextToken().LexemeName == "return")
		Return_prime();
}

bool Syntax::Return_prime()
{

}

//<Print> ::= put ( <Expression>);
bool Syntax::Print()
{
	if (nextToken().LexemeName == "put")
	{
		if (nextToken().LexemeName == "(")
			Expression();
		if (nextToken().LexemeName == ")")
		if (nextToken().LexemeName == ";")
	}
}
//<Scan> ::= get ( <IDs> );
bool Syntax::Scan()
{
	if (nextToken().LexemeName == "get")
	if (nextToken().LexemeName == "(")
	IDs();
	if (nextToken().LexemeName == ")")
	if (nextToken().LexemeName == ";")
}
//<While> ::= while ( <Condition> ) <Statement> whileend
bool Syntax::While()
{
	if (nextToken().LexemeName == "while")
	if (nextToken().LexemeName == "(")
	Condition();
	if (nextToken().LexemeName == ")")
	Statement();
	if (nextToken().LexemeName == "whileend")
}
//<Condition> ::= <Expression> <Relop> <Expression>
bool Syntax::Condition()
{
	printf("<Condition> ::= <Express//ion> <Relop> <Expression>\n");
	Expression();
	Relop();
	Expression();
}
//<Relop> ::= == | ^= | > |<  | => |=<
bool Syntax::Relop()
{
	Token t = nextToken();
	if (t.LexemeName == "==")
	{
		printf("<Relop> ::= ==\n");
		printf("Match %s and ==\n", t.LexemeName);
		return true;
	}
		//or
	else if (nextToken().LexemeName == "^=")
	{
		printf("<Relop> ::= ^=\n");
		printf("Match %s and ^=\n", t.LexemeName);
		return true;
	}
		//or
	else if (nextToken().LexemeName == ">")
	{
		printf("<Relop> ::= >\n");
		printf("Match %s and >\n", t.LexemeName);
		return true;
	}
		//or
	else if (nextToken().LexemeName == "<")
	{
		printf("<Relop> ::= <\n");
		printf("Match %s and <\n", t.LexemeName);
		return true;
	}
		//or
	else if (nextToken().LexemeName == "=>")
	{
		printf("<Relop> ::= =>\n");
		printf("Match %s and =>\n", t.LexemeName);
		return true;
	}
		//or
	else if (nextToken().LexemeName == "<=")
	{
		printf("<Relop> ::= <=\n");
		printf("Match %s and <=\n", t.LexemeName);
		return true;
	}
	//error message 
	printf("No Match for <Relop>\n");
	return false;

}
//<Expression> ::= <Term> <Expression>’
bool Syntax::Expression()
{
	printf("<Expression> ::= <Term> <Expression>'\n");
	return Term() && ExpressionPrime();
}
// <Expression>’ ::= +<Term> <Expression>’ | -<Term> <Expression>’ | epilson
bool Syntax::ExpressionPrime()
{
	Token t = nextToken();
	if (t.LexemeName == "+" || t.LexemeName == "-")
	{
		printf("<Expression>' ::= %s<Term>\n", t.LexemeName);
		return Term() && ExpressionPrime();
	}
	//or
	else
		Empty();
}
// <Term> = <Factor> <Term>'
bool Syntax::Term()
{
	printf("<Term> ::= <Factor> <Term>'\n");
	return Factor() && TermPrime();
}
// <Term>’ ::= * <Factor> <Term>’ | / <Factor> <Term>’ | epilson
bool Syntax::TermPrime()
{
	Token t = nextToken();
	if (t.LexemeName == "*" || t.LexemeName == "/")
	{
		printf("<Term>' ::= %s<Factor><Term>\n", t.LexemeName);
		return Factor() && TermPrime();
	}
	else //changable 
		Empty();
}
//<Factor> ::= - <Primary> | <Primary>
bool Syntax::Factor()
{
	Token t = nextToken();
	if (t.LexemeName == "-")
	{
		printf("<Factor> ::= -<Primary>\n");
		printf("Match %s and -\n", currToken.LexemeName);
		return Primary();
	}
	else if (Primary())
	{
		printf("<Factor> ::= <Primary>\n");
		return true;
	}
	else
	{
		printf("No Match for Factor");
		return false;
	}
	
}
//<Primary> ::= <Identifier> | <Integer> | <Identifier> ( <IDs> ) | ( <Expression> ) | <Real> | true | false
bool Syntax::Primary()
{
	Token t = nextToken();
	if (t.TokenName == "Identifier")
	{
		
		if (nextToken().LexemeName == "(")
		{
			if (IDs())
			{
				if (nextToken().LexemeName == ")")
				{

				}
			}
		}
		else
		{
			printf("<Primary> ::= <Identifier>\n");
			return true;
		}
	}
	//or
	else if (t.TokenName == "Integer")
	{ 
		printf("<Primary> ::= <Integer>\n");
		printf("Match %s and %s:%s\n", t.LexemeName, t.TokenName, t.LexemeName);
		return true;
	}	
		//or
	else if (t.LexemeName == "(")
	{
		if (Expression())
		{
			if (nextToken().LexemeName == ")")
			{

			}
		}
	}
		//or
	else if (t.TokenName == "Real")
	{
		printf("<Primary> ::= <Real>\n");
		printf("Match %s and %s:%s\n", t.LexemeName, t.TokenName, t.LexemeName);
		return true;
	}
		//or
	else if (t.LexemeName == "true")
	{
		printf("<Primary> ::= true\n");
		printf("Match %s and %s:%s\n", t.LexemeName, t.TokenName, t.LexemeName);
		return true;
	}
		//or
	else if (t.LexemeName == "false")
	{
		printf("<Primary> ::= false\n");
		printf("Match %s and %s:%s\n", t.LexemeName, t.TokenName, t.LexemeName);
		return true;
	}
	else
	{
		printf("No Match for <Primary>\n")
		return false;
	}
}
//<Empty> ::= epilson
bool Syntax::Empty()
{
	//go to back to previous tokens then return
}