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
	if ()
		Func_def();
	else if()		//or
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
	if(nextToken().TokenName == "Identifier")
	if (nextToken().LexemeName == "{")
	Opt_para_list();
	if (nextToken().LexemeName == "}")
	Opt_dec_list();
	Body();

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
	Expression();
	Relop();
	Expression();
}
bool Relop()
{
	if (nextToken().LexemeName == "==")
		//or
	else if (nextToken().LexemeName == "^=")
		//or
	else if (nextToken().LexemeName == ">")
		//or
	else if (nextToken().LexemeName == "<")
		//or
	else if (nextToken().LexemeName == "=>")
		//or
	else if (nextToken().LexemeName == "<=")
}
bool Expression()
{
	Term();
	ExpressionPrime();
}
bool ExpressionPrime()
{
	if (nextToken().LexemeName == "+")
		Term();
		ExpressionPrime();
	//or
	else if (nextToken().LexemeName == "-")
		Term();
		ExpressionPrime();
	//or
	else
		Empty();
}
bool Term()
{
	Factor();
	TermPrime();
}
bool TermPrime()
{
	if (nextToken().LexemeName == "*")
		Factor();
	TermPrime();
	//or
	else if (nextToken().LexemeName == "/")
		Factor();
	TermPrime();
	else
		Empty();
}
bool Factor()
{
	if (nextToken().LexemeName == "-")
	Primary();
	//or 
	Primary();
}
bool Primary()
{
	if (nextToken().TokenName == "Identifier")
	{
		if (nextToken().LexemeName == "(")
		{
			IDs();
			if (nextToken().LexemeName == ")")
		}
		else
		{
			printf("<Primary> ::= <Identifier>\n");
			return true;
		}
	}
	//or
	else if (nextToken().TokenName == "Integer")
	{ 
		printf("<Primary> ::= <Integer>\n");
		return true;
	}	
		//or
	else if (nextToken().LexemeName == "(")
	{
		Expression();
		if (nextToken().LexemeName == ")")
	}
		//or
	else if (nextToken().TokenName == "Real")
	{
		printf("<Primary> ::= <Real>\n");
		return true;
	}
		//or
	else if (nextToken().LexemeName == "true")
	{
		printf("<Primary> ::= true\n");
		return true;
	}
		//or
	else if (nextToken().LexemeName == "false")
	{
		printf("<Primary> ::= false\n");
		return true;
	}
}
bool Empty()
{

}