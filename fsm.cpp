#include "fsm.h"

int FSM_ID(char* buffer)	//CALL WHEN THE FIRST CHAR IS A LETTER
{
	int flag = 0;

	if (isalpha(buffer[0])!= 0)		//error checking if the first letter is a letter
	{
		std::cerr << "First character is not a letter\n";
		return EXIT_FAILURE; 
	}


	
	


	if (isKeyword(buffer))		//if it is an identifier
	{
		flag = 2;		//keyword
	}
	else
	{
		flag = 1; 		//an identifier, but not a keyword
	}

	return flag;
}

int FSM_INT(char* buffer)	//CALL WHEN THE FIRST CHAR IS A DIGIT
{
	int flag = 0;

	if (isdigit(buffer[0]) != 0)	
	{
		std::cerr << "First character is not a digit\n";
		return EXIT_FAILURE;
	}




	
	if (FSM_REAL(buffer))  //real vs integers //call when encountering a decimal point 
	{
			flag = 2;
	}


	return flag;
}

int FSM_REAL(char* buffer)	//CALL IN FSM_INT- CHECK FOR DECIMALS 
{
	int flag = 0;



	return flag;			//returns 1 if it is a real number 
}

void Unknown()		//CALL WHEN NOT A TOKEN
{


}

int isKeyword(char* buffer)	//CALL IN FSM_ID

{	//Feel free to add more if needed
	std::vector<std::string> keywords = {
		"if", "ifend", "put", "get", "else",
		"while", "whileend", "return", "true", "false"
	};

	int flag = 0;

	for (int i = 0; i< keywords.size(); i++)
	{
		if (strcmp(buffer, keywords[i].c_str()) == 0)
		{
			flag = 1;
		}
	}

	return flag;
}


int isOperator(char * buffer)
{	//feel free to add if needed
	std::vector<std::string> operators = {
		"+", "-", "*", "=", "==", "^=",
		">", "<", "=>", "=<"
	};

	int flag = 0;

	for (int i = 0; i< operators.size(); i++)
	{
		if (strcmp(buffer, operators[i].c_str()) == 0)
		{
			flag = 1;
		}
	}

	return flag;

}

int isSeparator(char * buffer)
{	//feel free to add more
	std::vector<std::string> separators = {
		"$$", " ", ":", ",", ";",
		"{}", "::=", "|", "/"
	};

	int flag = 0;

	for (int i = 0; i< separators.size(); i++)
	{
		if (strcmp(buffer, separators[i].c_str()) == 0)
		{
			flag = 1;
			break;
		}
	}

	return flag;
}
