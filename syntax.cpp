#include "syntax.h"
#include "fsm.h"

#include <iostream>

using namespace std;

Token nextToken()		//???
{
	//return ((i == 0) ? v[i] : v[++i]);
}

bool Rat18F() 
{
	return Opt_func_def() &&
		   
	//use syntax rules and call functions
	Opt_func_def();
	if (nextToken().LexemeName == "$$")
	Opt_dec_list();
	Statement_list();
	if (nextToken().LexemeName == "$$")
	//Accepting State


}
bool Opt_func_def()
{
	printf("<RAT18F> ::= <Opt Function Definitions> $$ <Opt Declaration List> <Statement List> $$\n");
	if (Func_def())
	
		
	else if(Empty())		//or
		Empty();
}
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
bool Opt_para_list() 
{
	if ()
		Parameter();
	else if ()		//or
		Empty();
}
bool Para_list()
{
	if ()
		Parameter();
	else if ()		//or
		Parameter();
		if (nextToken().LexemeName == ",")
		Para_list();
}
bool Parameter()
{
	if (nextToken().TokenName == "Identifier")

	if (nextToken().LexemeName == ".")

	Qualifier();
}
bool Qualifier()
{
	if (nextToken().LexemeName == "int")

	else if (nextToken().LexemeName == "boolean")//or
		
	else if (nextToken().LexemeName == "real")//or

}
bool Body()
{
	if (nextToken().LexemeName == "{")
	Statement_list();
	if (nextToken().LexemeName == "}")
}
bool Opt_dec_list()
{
	if ()
		Dec_list();
	else if()		//or
		Empty();
}
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
bool Dec()
{
	Qualifier();
	IDs();
}
bool IDs()
{
	if (nextToken().TokenName == "Identifier")
		//or
	if (nextToken().TokenName == "Identifier")
	IDs();

}
bool Statement_list()
{
	Statement();
	//or 
	Statement();
	Statement_list();
}
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
bool Compound()//same as Body?
{
	if (nextToken().LexemeName == "{")
	Statement_list();
	if (nextToken().LexemeName == "}")
}
bool Assign()
{
	if (nextToken().TokenName == "Identifier")
	if (nextToken().LexemeName == "=")
	Expression();
}
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
bool Return()
{
	if (nextToken().LexemeName == "return")
	if (nextToken().LexemeName == ";")
	//or
	else if (nextToken().LexemeName == "return")
		Expression();
			if (nextToken().LexemeName == ";")
}
bool Print()
{
	if (nextToken().LexemeName == "put")
	if (nextToken().LexemeName == "(")
	Expression();
	if (nextToken().LexemeName == ")")
	if (nextToken().LexemeName == ";")
}
bool Scan()
{
	if (nextToken().LexemeName == "get")
	if (nextToken().LexemeName == "(")
	IDs();
	if (nextToken().LexemeName == ")")
	if (nextToken().LexemeName == ";")
}
bool While()
{
	if (nextToken().LexemeName == "while")
	if (nextToken().LexemeName == "(")
	Condition();
	if (nextToken().LexemeName == ")")
	Statement();
	if (nextToken().LexemeName == "whileend")
}
bool Condition()
{
	printf("<Condition> ::= <Expression> <Relop> <Expression>\n");
	Expression();
	Relop();
	Expression();
}
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
bool Expression()
{
	printf("<Expression> ::= <Term> <Expression>'\n");
	return Term() && ExpressionPrime();
}
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
bool Term()
{
	printf("<Term> ::= <Factor> <Term>'\n");
	return Factor() && TermPrime();
}
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
	}
	
}
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
bool Empty()
{

}