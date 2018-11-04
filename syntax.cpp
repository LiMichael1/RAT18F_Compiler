#include "syntax.h"
#include "fsm.h"

#include <iostream>

using namespace std;

Token nextToken()		//???
{
	//return ((i == 0) ? v[i] : v[++i]);
}

void Rat18F() 
{
	//use syntax rules and call functions
	Opt_func_def();
	if (nextToken().LexemeName == "$$")
	Opt_dec_list();
	Statement_list();
	if (nextToken().LexemeName == "$$")
	//Accepting State


}
void Opt_func_def()
{
	if ()
		Func_def();
	else if()		//or
		Empty();
}
void Func_def() 
{
	if ()
		Function();
	else if ()		//or
	{
		Function();
		Func_def();
	}
}
void Function() 
{
	if (nextToken().LexemeName == "function")
	if(nextToken().TokenName == "Identifier")
	if (nextToken().LexemeName == "{")
	Opt_para_list();
	if (nextToken().LexemeName == "}")
	Opt_dec_list();
	Body();

}
void Opt_para_list() 
{
	if ()
		Parameter();
	else if ()		//or
		Empty();
}
void Para_list()
{
	if ()
		Parameter();
	else if ()		//or
		Parameter();
		if (nextToken().LexemeName == ",")
		Para_list();
}
void Parameter()
{
	if (nextToken().TokenName == "Identifier")

	if (nextToken().LexemeName == ".")

	Qualifier();
}
void Qualifier()
{
	if (nextToken().LexemeName == "int")

	else if (nextToken().LexemeName == "boolean")//or
		
	else if (nextToken().LexemeName == "real")//or

}
void Body()
{
	if (nextToken().LexemeName == "{")
	Statement_list();
	if (nextToken().LexemeName == "}")
}
void Opt_dec_list()
{
	if ()
		Dec_list();
	else if()		//or
		Empty();
}
void Dec_list()
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
void Dec()
{
	Qualifier();
	IDs();
}
void IDs()
{
	if (nextToken().TokenName == "Identifier")
		//or
	if (nextToken().TokenName == "Identifier")
	IDs();

}
void Statement_list()
{
	Statement();
	//or 
	Statement();
	Statement_list();
}
void Statement()
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
void Compound()//same as Body?
{
	if (nextToken().LexemeName == "{")
	Statement_list();
	if (nextToken().LexemeName == "}")
}
void Assign()
{
	if (nextToken().TokenName == "Identifier")
	if (nextToken().LexemeName == "=")
	Expression();
}
void If()
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
void Return()
{
	if (nextToken().LexemeName == "return")
	if (nextToken().LexemeName == ";")
	//or
	else if (nextToken().LexemeName == "return")
		Expression();
			if (nextToken().LexemeName == ";")
}
void Print()
{
	if (nextToken().LexemeName == "put")
	if (nextToken().LexemeName == "(")
	Expression();
	if (nextToken().LexemeName == ")")
	if (nextToken().LexemeName == ";")
}
void Scan()
{
	if (nextToken().LexemeName == "get")
	if (nextToken().LexemeName == "(")
	IDs();
	if (nextToken().LexemeName == ")")
	if (nextToken().LexemeName == ";")
}
void While()
{
	if (nextToken().LexemeName == "while")
	if (nextToken().LexemeName == "(")
	Condition();
	if (nextToken().LexemeName == ")")
	Statement();
	if (nextToken().LexemeName == "whileend")
}
void Condition()
{
	Expression();
	Relop();
	Expression();
}
void Relop()
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
void Expression()
{
	Term();
	ExpressionPrime();
}
void ExpressionPrime()
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
void Term()
{
	Factor();
	TermPrime();
}
void TermPrime()
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
void Factor()
{
	if (nextToken().LexemeName == "-")
	Primary();
	//or 
	Primary();
}
void Primary()
{
		if (nextToken().TokenName == "Identifier")
		//or
		if (nextToken().TokenName == "Integer")
		//or
		if (nextToken().TokenName == "Identifier")
		if (nextToken().LexemeName == "(")
		IDs();
		if (nextToken().LexemeName == ")")
		//or
		if (nextToken().LexemeName == "(")
		Expression();
		if (nextToken().LexemeName == ")")
		//or
		if (nextToken().TokenName == "Real")
		//or
		if (nextToken().LexemeName == "true")
		//or
		if (nextToken().LexemeName == "false")
}
void Empty()
{

}