#pragma once

#ifndef FSM_H_
#define FSM_H_

#include <iostream>
#include <vector>
#include <string>
#include <ctype.h>
extern bool comments;
using namespace std;

//TOKEN STRUCTURE 
struct Token
{
	string LexemeName;
	int TokenType;
	string TokenName;
	int LineNumber;
};

enum TRANSITION_STATES			//FOR THE FINITE STATE MACHINE
{
	INTEGER = 2,
	REAL = 4,
	SINGLE_IDEN = 5,
	IDENTIFIER = 7,
	IGNORE = 8
};

//FINITE STATE MACHINE 
const int stateTable[8][3] = {			
	{ SINGLE_IDEN,	INTEGER,	IGNORE },			// STATE 1
	{ IGNORE,		INTEGER,	3 },				// STATE 2
	{ IGNORE,		REAL,		IGNORE },		// STATE 3
	{ IGNORE,		REAL,		IGNORE },		// STATE 4
	{ IDENTIFIER,	6,			IGNORE },		// STATE 5
	{ IDENTIFIER,	6,			IGNORE },		// STATE 6
	{ IDENTIFIER,	6,			IGNORE },		// STATE 7
	{ IGNORE,		IGNORE,		IGNORE }		// STATE 8
};

Token Lexer(char* buffer, int currentState, string currentHolder, int& i);

bool isDoubleOp(char, char, Token&);

vector<Token> Parser(char*);

bool isKeyword(string);

bool isOperator(string);

bool isSeparator(string);

Token Id_int_real_helper(int, string);

Token Sep_Op_helper(string);

bool isPunct(int);

int GetCol(char);

string getTokenName(int, string);

#endif