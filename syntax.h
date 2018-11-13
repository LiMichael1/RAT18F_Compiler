#ifndef SYNTAX_H
#define SYNTAX_H

#include "fsm.h"
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <stdlib.h> 
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <tuple>
using namespace std;

extern vector<string> numberLinesVec;

class Syntax {
private:
	vector<Token> Tokens;
	ofstream file;
	int index;
	vector<string> rules;
	Token currToken;
	void nextToken();
	bool Accept();
	bool Match(string);
	bool Match_t(string);
	bool syn_error(string, string);
	void print_rules();


public:
	Syntax(vector<Token>);
	~Syntax();
	bool Rat18F();
	bool Opt_func_def();
	bool Func_def();
	bool Func_def_prime();
	bool Function();
	bool Opt_para_list();
	bool Para_list();
	bool Para_list_prime();
	bool Parameter();
	bool Qualifier();
	bool Body();
	bool Opt_dec_list();
	bool Dec_list();
	bool Dec_list_prime();
	bool Dec();
	bool IDs();
	bool IDs_prime();
	bool Statement_list();
	bool Statement_list_prime();
	bool Statement();
	bool Compound();
	bool Assign();
	bool If();
	bool If_prime();
	bool Return();
	bool Return_prime();
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
	bool Primary_prime();
	bool Empty();
};
#endif