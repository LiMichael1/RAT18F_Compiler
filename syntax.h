#pragma once
#ifndef SYNTAX_H
#define SYNTAX_H

//could put it in a class if you want. 
class Parser {
private:
	Token currToken;
	Token nextToken();

public:
	bool Rat18F();
	bool Opt_func_def();
	bool Func_def();
	bool Function();
	bool Opt_para_list();
	bool Para_list();
	bool Parameter();
	bool Qualifier();
	bool Body();
	bool Opt_dec_list();
	bool Dec_list();
	bool Dec();
	bool IDs();
	bool Statement_list();
	bool Statement();
	bool Compound();
	bool Assign();
	bool If();
	bool Return();
	bool Print();
	bool Scan();
	bool While();
	bool Condition();
	bool Relop();
	bool Expression();
	bool ExpressionPrime();
	bool Term();
	bool TermPrime();
	bool Factor();
	bool Primary();
	bool Empty();
};
#endif