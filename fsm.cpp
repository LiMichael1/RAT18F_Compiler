#include "fsm.h"
using namespace std;

// RETURNS THE TOTAL COLLECTION OF TOKENS BASED ON THE INPUT 
vector<Token> Parser(char* buffer)		
{
	int buffer_length = strlen(buffer);		//get length of the input

	int currentState = 1;					//current State

	vector<Token> Holder;					//Holds collection of Tokens

	string currentHolder;					//Holds the current lexeme

	for (int i = 0; i < buffer_length; i++)		//loop for checking the input
	{
		// COMMENT CHECK at the start of a new line
		if (i + 1 < buffer_length &&
			buffer[i] == '[' &&
			buffer[i + 1] == '*')
		{
			comments = true;				//if you get [*
		}
		if (i + 1 < buffer_length &&
			buffer[i] == '*' &&
			buffer[i + 1] == ']')
		{
			comments = false;				//if you get *] after having comments = true
			i += 2;
		}


		// Lexer() function here
		if (!comments)				//check if it's not comments
		{
			if (isspace(buffer[i])) //Upon seeing empty spaces
			{

				if (currentState != 1)	 //FLUSH FOR lexeme after a space
				{
					Holder.push_back(Id_int_real_helper(currentState, currentHolder));	
				}
				currentState = 1;
				i++;
			}
			Token t = (Lexer(buffer, currentState, currentHolder, i));
			if (t.TokenType != -2)		//error checking for not flushing blank spaces or comments
			{
				Holder.push_back(t);	
			}
		}
	}
	return Holder;
}


//LEXER FUNCTION THAT RETURNS ONE TOKEN 
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
			}
			currentState = 1;
			i++;
		}
		while (isPunct(buffer[i]))                       //1 char PUNCTUATION check
		{
			// Comments check in the middle of a line
			if (i + 1 < buffer_length &&
				buffer[i] == '[' &&
				buffer[i + 1] == '*')
			{
				comments = true;				//true if you get the start of a comment segment: [*
			}
			if (i + 1 < buffer_length &&
				buffer[i] == '*' &&
				buffer[i + 1] == ']')
			{
				comments = false;				//false if you get comment = true and the end of a comment segment: *]
				i += 2;
			}


			// Lexer() function here
			if (!comments)
			{
				if (currentState != 1)	 //FLUSH
				{
					i--;							//decrements because the for loop in parser functions would skip some tokens 
					return Id_int_real_helper(currentState, currentHolder);
				}

				currentState = 1;

				currentHolder += buffer[i];					//adds one character to the current holder

				if (isPunct(buffer[i + 1]))                 //2 char punctuation check
				{
					Token t, t2;						//tokens

					string buff2 = "";					//one char token for string input into a function
					buff2 += buffer[i];

					if (isDoubleOp(buffer[i], buffer[i + 1], t))
					{
						i++;
						return t;							//two char Separator/Operator token
					}
					else
					{
						t2 = Sep_Op_helper(buff2);			//one individual char Sep/Op token after two punctuations in a row
						return t2;

					}

				}
				else {				 //1 char punctuation check
					string buff = "";
					buff += buffer[i];

					return Sep_Op_helper(buff);		//FLUSH	 after confirming only one punctuation in a row
				}
			}
			else
			{
				Token t;
				t.TokenType = -2;
				return t;
			}
		}

		int Column = GetCol(buffer[i]);				//get input : " Id, int , . " for FINITE STATE MACHINE
		if (Column != -1)					//error, so we don't send an incorrect input 
		{
			currentHolder += buffer[i];		//adds to currrent holder
			currentState = stateTable[currentState - 1][Column];	//FINITE STATE MACHINE AT WORK
			i++;													//increment to go to next character				
		}

	}	
	if (currentHolder.empty())				//blank spaces/ new line check 
	{										//sends a -2 token which will not add to collection of tokens
		currentState = 1;
		Token t;
		t.TokenType = -2;
		return t;
	}
	return Id_int_real_helper(currentState, currentHolder);		//returns once you get an identifier, real number, or integer

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
		"function", "int", "boolean", "real",
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

//double Operator or Separator check 
bool isDoubleOp(char firstChar, char secondChar, Token &t)
{
	vector<string> doubleOpList = { "==", "$$", "=<", "=>", "!=", "^=" };
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
