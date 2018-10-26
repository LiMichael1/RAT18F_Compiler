#include "syntax.h"
#include "fsm.h""

#include <iostream>

using namespace std;

void Rat18F(vector<Token> tokens) 
{
	//use syntax rules and call functions

	Opt_func_def();
	//if next token == $$
	//Opt_dec_list();
	//Statement_list();
	//if next token == $$
	//Accepting State


}
void Opt_func_def()
{
	if ()
		Functions();
	else
		Empty();
}
void Func_def() 
{
	if ()
		Function();
	else
	{
		Function();
		Func_def();
	}
}
void Function() 
{
	//if first token is function
	//and next token = identifier

}
void Opt_para_list() 
{

}
void Para_list()
{

}
void Parameter()
{

}
void Qualifier()
{

}
void Body()
{

}
void Opt_dec_list()
{

}
void Dec_list()
{

}
void Dec()
{

}
void IDs()
{

}
void Statement_list()
{

}
void Statement()
{

}
void Compound()
{

}
void Assign()
{

}
void If()
{

}
void Return()
{

}
void Print()
{

}
void Scan()
{

}
void While()
{

}
void Condition()
{

}
void Relop()
{

}
void Expression()
{

}
void ExpressionPrime()
{

}
void Term()
{

}
void TermPrime()
{

}
void Factor()
{

}
void Primary()
{

}
void Empty()
{

}