#include "test.h":
using namespace std;

int main() {

	ifstream inFile;
	string file, input;

	cout << "Enter file name: ";
	getline(cin, file);

	inFile.open(file);
	if (inFile.fail())
	{
		cout << "Invalid file name\n";
	}
	vector<Token> tokens;
	//char arr[] = "x=x-1; ";

	while (getline(inFile, input))
	{
		char *test = new char[input.length() + 1];
		strcpy(test, input.c_str());		// Copy text from file into a character array

		tokens = FSM(test);

		for (size_t i = 0; i < tokens.size(); i++)
			cout << endl << tokens[i].LexemeName << " " << tokens[i].TokenName << endl << endl;

		delete[] test;
	}

	inFile.close();
	system("pause");
	return 0;
}



vector<Token> FSM(char* buffer)
{//)= operator, 1= separator , 2 =int , 3= real, 4= keyword, 5 = identifer , 6 = unknown
	enum TRANSITION_STATES
	{
		INTEGER = 2,
		REAL = 4,
		SINGLE_IDEN = 5,
		IDENTIFIER = 7,
		IGNORE = 8
	};

	int stateTable[8][3] = {
	   { SINGLE_IDEN,	INTEGER,	IGNORE },		// STATE 1
	   { IGNORE,		INTEGER,	3 },				// STATE 2
	   { IGNORE,		REAL,		IGNORE },		// STATE 3
	   { IGNORE,		REAL,		IGNORE },		// STATE 4
	   { IDENTIFIER,	6,			IGNORE },		// STATE 5
	   { IDENTIFIER,	6,			IGNORE },		// STATE 6
	   { IDENTIFIER,	6,			IGNORE },		// STATE 7
	   { IGNORE,		IGNORE,		IGNORE }			// STATE 8
	};

	int buffer_length = strlen(buffer);

	int currentState = 1;

	vector<Token> Holder;

	string currentHolder;

	for (int i = 0; i < buffer_length; i++)
	{

		if (isspace(buffer[i])) //upon seeing spaces
		{
			//save the previous Token
			if (currentState != 1)	 //FLUSH
			{
				Holder.push_back(Id_int_real_helper(currentState, currentHolder));
				currentHolder.clear();
			}
			currentState = 1;
			i++;
		}



		while (isPunct(buffer[i]))                       //1 char check
		{

			if (currentState != 1)	 //FLUSH
			{
				Holder.push_back(Id_int_real_helper(currentState, currentHolder));
				currentHolder.clear();
			}

			currentState = 1;

			currentHolder += buffer[i];

			if (isPunct(buffer[i + 1]))                 //2 char check
			{
				Token t, t2, t3;

				string buff = "";
				buff += buffer[i];
				buff += buffer[i + 1];

				string buff2 = "";		    //{{
				buff2 += buffer[i];

				string buff3 = "";		    //{{
				buff3 += buffer[i + 1];

				t = Sep_Op_helper(buff);
				t2 = Sep_Op_helper(buff2);
				t3 = Sep_Op_helper(buff3);

				if (t.TokenType == -1)	    //unknown two char punctuation
				{
					if (t2.TokenType != -1 || t3.TokenType != -1) //known one char punctuations
					{
						Holder.push_back(t2);
						Holder.push_back(t3);
					}
					else
					{
						Holder.push_back(t);
					}
				}
				else
				{
					Holder.push_back(t);
				}

				currentHolder.clear();
				i = i + 2;
			}
			else {
				string buff = "";
				buff += buffer[i];
				Holder.push_back(Sep_Op_helper(buff));		//FLUSH
				currentHolder.clear();
				i++;
			}

		}

		int Column = GetCol(buffer[i]);
		if (Column != -1)
		{
			currentHolder += buffer[i];

			currentState = stateTable[currentState - 1][Column];
		}
	}


	return Holder;
}

Token Id_int_real_helper(int state, string LexemeName)//returns Token based on Token
{
	Token t;
	t.LexemeName = LexemeName;
	t.TokenType = state;
	t.TokenName = getTokenName(state, LexemeName);

	return t;
}

Token Sep_Op_helper(string LexemeName)	//returns Token based on separators and operators
{
	Token t;
	if (isSeparator(LexemeName))
	{
		t.LexemeName = LexemeName;
		t.TokenName = "Separator";
		t.TokenType = 9;
	}
	else if (isOperator(LexemeName))
	{
		t.LexemeName = LexemeName;
		t.TokenName = "Operator";
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

bool isPunct(int ch)		  //checks that the punctuation isn't a dot
{
	if (ispunct(ch) && ch != '.')
		return true;
	else
		return false;
}

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
	}


}

int GetCol(char buffer)
{
	int enumDigit = -1;
	// checks for letter
	if (isalpha(buffer))
	{
		enumDigit = 0;
	}
	//digits
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

bool isKeyword(string buffer)	//CALL IN FSM_ID

{	//Feel free to add more if needed
	vector<string> keywords = {
	   "if", "ifend", "put", "get", "else",
	   "while", "whileend", "return", "true", "false"
	};

	bool flag = false;

	for (size_t i = 0; i < keywords.size(); i++)
	{
		if (buffer == keywords[i])
		{
			flag = true;
		}
	}

	return flag;
}


bool isOperator(string buffer)
{	//feel free to add if needed
	vector<string> operators = {
	   "+", "-", "*", "=", "==", "^=",
	   ">", "<", "=>", "=<"
	};

	bool flag = false;

	for (size_t i = 0; i < operators.size(); i++)
	{
		if (buffer == operators[i])
		{
			flag = true;
		}
	}

	return flag;

}

bool isSeparator(string buffer)
{	//feel free to add more
	vector<string> separators = {
	   "$$", " ", ":", ",", ";",
	   "{","}", "|", "/", "{}"
	};

	bool flag = false;

	for (size_t i = 0; i < separators.size(); i++)
	{
		if (buffer == separators[i])
		{
			flag = true;
		}
	}

	return flag;
}
