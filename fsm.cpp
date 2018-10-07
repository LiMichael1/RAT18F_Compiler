#include "fsm.h"
using namespace std;



vector<Token> Parser(char* buffer)		//lexer machine
{
	int buffer_length = strlen(buffer);


	int currentState = 1;

	vector<Token> Holder;

	string currentHolder;

	for (int i = 0; i < buffer_length; i++)
	{
		// Comments check
		if (i + 1 < buffer_length &&
			buffer[i] == '[' &&
			buffer[i + 1] == '*')
		{
			comments = true;
		}
		if (i + 1 < buffer_length &&
			buffer[i] == '*' &&
			buffer[i + 1] == ']')
		{
			comments = false;
			i += 2;
		}


		// Lexer() function here
		if (!comments)
		{
			if (isspace(buffer[i])) //Upon seeing empty spaces
			{

				if (currentState != 1)	 //FLUSH
				{
					Holder.push_back(Id_int_real_helper(currentState, currentHolder));
					currentHolder.clear();
				}
				currentState = 1;
				i++;
			}
			Token t = (Lexer(buffer, currentState, currentHolder, i));
			if (t.TokenType != -2)
			{
				Holder.push_back(t);
			}
		}
	}
	return Holder;
}

Token Lexer(char* buffer, int currentState, string currentHolder, int& i)
{

	int buffer_length = strlen(buffer);
	while (i < buffer_length)
	{
		if (isspace(buffer[i])) //Upon seeing empty spaces
		{
			if (currentState != 1)	 //FLUSH
			{
				return Id_int_real_helper(currentState, currentHolder);
				currentHolder.clear();
			}
			currentState = 1;
			i++;
		}
		while (isPunct(buffer[i]))                       //1 char check
		{
			// Comments check
			if (i + 1 < buffer_length &&
				buffer[i] == '[' &&
				buffer[i + 1] == '*')
			{
				comments = true;
			}
			if (i + 1 < buffer_length &&
				buffer[i] == '*' &&
				buffer[i + 1] == ']')
			{
				comments = false;
				i += 2;
			}


			// Lexer() function here
			if (!comments)
			{
				if (currentState != 1)	 //FLUSH
				{
					i--;
					return Id_int_real_helper(currentState, currentHolder);
					currentHolder.clear();
				}

				currentState = 1;

				currentHolder += buffer[i];

				if (isPunct(buffer[i + 1]))                 //2 char punctuation check
				{
					Token t, t2, t3;

					string buff2 = "";
					buff2 += buffer[i];

					if (isDoubleOp(buffer[i], buffer[i + 1], t))
					{
						i++;
						return t;
					}
					else
					{
						t2 = Sep_Op_helper(buff2);
						return t2;

					}
					currentHolder.clear();

				}
				else {				 //1 char punctuation check
					string buff = "";
					buff += buffer[i];
					//i++;
					return Sep_Op_helper(buff);		//FLUSH
					currentHolder.clear();

				}
			}
			else
			{
				Token t;
				t.TokenType = -2;
				return t;
			}
		}

		int Column = GetCol(buffer[i]);
		if (Column != -1)
		{
			currentHolder += buffer[i];
			currentState = stateTable[currentState - 1][Column];
			i++;												//FINITE STATE MACHINE AT WORK
		}

	}
	if (currentHolder.empty())
	{
		currentState = 1;
		Token t;
		t.TokenType = -2;
		return t;
	}
	return Id_int_real_helper(currentState, currentHolder);

}

//returns Token based on State
Token Id_int_real_helper(int state, string LexemeName)
{
	Token t;
	t.LexemeName = LexemeName;
	t.TokenType = state;
	t.TokenName = getTokenName(state, LexemeName);

	return t;
}

//returns Token based on separators and operators | unknown if neither
Token Sep_Op_helper(string LexemeName)
{
	Token t;
	if (isSeparator(LexemeName))
	{
		t.LexemeName = LexemeName;
		t.TokenName = "Separators";
		t.TokenType = 9;
	}
	else if (isOperator(LexemeName))
	{
		t.LexemeName = LexemeName;
		t.TokenName = "Operators";
		t.TokenType = 10;
	}
	else
	{
		t.LexemeName = LexemeName;
		t.TokenName = "Unknown";
		t.TokenType = -1;
	}

	return t;
}

//WRAPPER FUNCTION - checks that it's a punctuation and not a dot
bool isPunct(int ch)
{
	return ispunct(ch) && ch != '.';
}

//Helper function to find TokenName after you determine the state
string getTokenName(int state, string LexemeName)
{

	switch (state)
	{
	case 1: case 3: case 6: case 8:
		return "Undefined";
		break;
	case 2:
		return "Integer";
		break;
	case 4: return "Real";
		break;
	case 5:
		return "Identifier";
		break;
	case 7:
		if (isKeyword(LexemeName))
			return "Keyword";
		else
			return "Identifier";
		break;
	default:
		return "Unknown";
		break;
	}


}

//get the Column : Letter, digit, dot
int GetCol(char buffer) //returns column number 
{
	int enumDigit = -1;
	// checks for letter
	if (isalpha(buffer))
	{
		enumDigit = 0;
	}
	//checks for digits
	else if (isdigit(buffer))
	{
		enumDigit = 1;
	}

	// checks for a period aka real #
	else if (buffer == '.')
	{
		enumDigit = 2;
	}

	\
		return enumDigit;
}

//DETERMINES IF INPUT IS A KEYWORD
bool isKeyword(string buffer)	//call after determining it's an identifier
{
	vector<string> keywords = {
		"if", "ifend", "put", "get", "else",
		"while", "whileend", "return", "true", "false",
		"function", "int", "boolean",
	};

	bool flag = false;

	for (size_t i = 0; i< keywords.size(); i++)
	{
		if (buffer == keywords[i])
		{
			flag = true;
		}
	}

	return flag;
}

//DETERMIENS IF INPUT IS A OPERATOR
bool isOperator(string buffer)
{
	vector<string> operators = {
		"+", "-", "*", "=", "==", "^=",
		">", "<", "=>", "=<"
	};

	bool flag = false;

	for (size_t i = 0; i< operators.size(); i++)
	{
		if (buffer == operators[i])
		{
			flag = true;
		}
	}

	return flag;

}

//DETERMINES IF INPUT IS A SEPARATOR
bool isSeparator(string buffer)
{	//feel free to add more
	vector<string> separators = {
		"$$", " ", ":", ",", ";",
		"{","}", "|", "/", "(", ")"
	};

	bool flag = false;

	for (size_t i = 0; i< separators.size(); i++)
	{
		if (buffer == separators[i])
		{
			flag = true;
		}
	}

	return flag;
}

bool isDoubleOp(char firstChar, char secondChar, Token &t)
{
	vector<string> doubleOpList = { "==", "$$", "<=", ">=", "!=", "^=" };
	string doubleOp = "";
	doubleOp.push_back(firstChar);
	doubleOp.push_back(secondChar);
	bool found = false;
	size_t index = 0;
	while (!found && index < doubleOpList.size())
	{
		if (doubleOp == doubleOpList[index])
		{
			found = true;
		}
		else {
			index++;
		}
		if (found) {
			t = Sep_Op_helper(doubleOp);
		}
	}

	return found;
}