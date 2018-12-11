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
#include <stack>
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

int Pop_JS();
void Push_JS(int);
bool exists_symtable(string lex);
int sym_table_type(string lex);
void print_table();
void gen_instr(string op, string oprnd);
void back_patch(int jump_addr);
int get_address(string lexeme);
string get_type(string lex);
void insert_symtable(string lex, string type);

struct Instruction //changeable
{
	int address;
	string op;
	string oprnd;
};

struct Symbol //changeable
{
	string lexeme;
	int mem_addr;
	string type;   //int/boolean
};





#endif