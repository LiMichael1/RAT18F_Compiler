#include "syntax.h"
#include "fsm.h"

#include <iostream>

using namespace std;

Token nextToken()		//???
{
	//return ((i == 0) ? v[i] : v[++i]);
}

bool Match(Token t)
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
bool check_input(Token t)
{
	return t.LexemeName == currToken.LexemeName;
}

//<Rat18F> ::= <Opt Function Definitions> $$ <Opt Declaration List> <Statement List> $$
bool Rat18F() 
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
bool Opt_func_def()
{
	printf("<RAT18F> ::= <Opt Function Definitions> $$ <Opt Declaration List> <Statement List> $$\n");
	if (Func_def())
	
		
	else if(Empty())		//or
		Empty();
}

//<Function Definitions> ::= <Function> | <Function> <Function Definitions>
bool Func_def() 
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
bool Function()
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
bool Opt_para_list() 
{
	if ()
		Parameter();
	else if ()		//or
		Empty();
}
//<Parameter List> ::= <Parameter> | <Parameter> , <Parameter List>
bool Para_list()
{
	if ()
		Parameter();
	else if ()		//or
		Parameter();
		if (nextToken().LexemeName == ",")
		Para_list();
}
//<Parameter> ::= <IDs > : <Qualifier>
bool Parameter()
{
	if (nextToken().TokenName == "Identifier")

	if (nextToken().LexemeName == ".")

	Qualifier();
}
//<Qualifier> ::= int | boolean | real
bool Qualifier()
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
bool Body()
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
bool Opt_dec_list()
{
	if ()
		Dec_list();
	else if()		//or
		Empty();
}
//<Declaration List> := <Declaration> ; | <Declaration> ; <Declaration List>
bool Dec_list()
{
	if ()
	{
		Dec();
		if (nextToken().LexemeName == ";")
	}
	else if ()		//or
	{
		Dec();
		if (nextToken().LexemeName == ";")
		Dec_list();
	}
}
//<Declaration> ::= <Qualifier > <IDs>
bool Dec()
{
	Qualifier();
	IDs();
}
//<IDs> ::= <Identifier> | <Identifier>, <IDs>
bool IDs()
{
	if (nextToken().TokenName == "Identifier")
		//or
	if (nextToken().TokenName == "Identifier")
	IDs();

}
//<Statement List> ::= <Statement> | <Statement> <Statement List>
bool Statement_list()
{
	Statement();
	//or 
	Statement();
	Statement_list();
}
//<Statement> ::= <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan> | <While>
bool Statement()
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
bool Compound()//same as Body?
{
	if (nextToken().LexemeName == "{")
	Statement_list();
	if (nextToken().LexemeName == "}")
}
//<Assign> ::= <Identifier> = <Expression> ;
bool Assign()
{
	if (nextToken().TokenName == "Identifier")
	if (nextToken().LexemeName == "=")
	Expression();
}
//<If> ::= if ( <Condition> ) <Statement> ifend |
//         if ( <Condition> ) <Statement> else <Statement> ifend
bool If()
{
	if (nextToken().LexemeName == "if")
	if (nextToken().LexemeName == "(")
	Condition();
	if (nextToken().LexemeName == ")")
	Statement();
	if (nextToken().LexemeName == "ifend")

	//or
	if (nextToken().LexemeName == "if")
	if (nextToken().LexemeName == "(")
	Condition();
	if (nextToken().LexemeName == ")")
	Statement();
	if (nextToken().LexemeName == "else")
	Statement();
	if (nextToken().LexemeName == "ifend")

}
//<Return> ::= return ; | return <Expression> ;
bool Return()
{
	if (nextToken().LexemeName == "return")
	if (nextToken().LexemeName == ";")
	//or
	else if (nextToken().LexemeName == "return")
		Expression();
			if (nextToken().LexemeName == ";")
}
//<Print> ::= put ( <Expression>);
bool Print()
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
bool Scan()
{
	if (nextToken().LexemeName == "get")
	if (nextToken().LexemeName == "(")
	IDs();
	if (nextToken().LexemeName == ")")
	if (nextToken().LexemeName == ";")
}
//<While> ::= while ( <Condition> ) <Statement> whileend
bool While()
{
	if (nextToken().LexemeName == "while")
	if (nextToken().LexemeName == "(")
	Condition();
	if (nextToken().LexemeName == ")")
	Statement();
	if (nextToken().LexemeName == "whileend")
}
//<Condition> ::= <Expression> <Relop> <Expression>
bool Condition()
{
	printf("<Condition> ::= <Express//ion> <Relop> <Expression>\n");
	Expression();
	Relop();
	Expression();
}
//<Relop> ::= == | ^= | > |<  | => |=<
bool Relop()
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
bool Expression()
{
	printf("<Expression> ::= <Term> <Expression>'\n");
	return Term() && ExpressionPrime();
}
//R26. <Expression>’ ::= +<Term> <Expression>’ | -<Term> <Expression>’ | empty
bool ExpressionPrime()
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
bool Term()
{
	printf("<Term> ::= <Factor> <Term>'\n");
	return Factor() && TermPrime();
}
// <Term>’ ::= * <Factor> <Term>’ | / <Factor> <Term>’ | empty
bool TermPrime()
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
bool Factor()
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
bool Primary()
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
//<Empty> ::= empty
bool Empty()
{

}