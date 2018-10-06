#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <ctype.h>
#include <fstream>
using namespace std;

struct Token
{
    string LexemeName;
    int TokenType;
    string TokenName;
};

vector<Token> FSM(char*);

bool isKeyword(string);

bool isOperator(string);

bool isSeparator(string);

bool Unknown(char);

Token Id_int_real_helper(int, string);

Token Sep_Op_helper(string);

bool isPunct(int);

int GetCol(char);

string getTokenName(int, string);
