#include <iostream>
#include <vector>
#include <string>

int FSM_INT(char* buffer);

int FSM_ID(char* buffer);

int FSM_REAL(char* buffer);

int isKeyword(char* buffer);

int isOperator(char* buffer);

int isSeparator(char* buffer);

void Unknown();
