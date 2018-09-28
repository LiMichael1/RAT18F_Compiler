

#include "fsm.h"

int FSM_ID(char* buffer)	//CALL WHEN THE FIRST CHAR IS A LETTER
{
	int flag = 0;

	if (isalpha(buffer[0]) != 0)		//error checking if the first letter is a letter
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

int FSM_REAL_INT(char* buffer) //0= integer , 1= real
{
	int flag = -1;	//returns if neither 

	int length = strlen(buffer);

	int state = 1;

	for (int i = 0; i < length; i++)
	{
		//loop works
		switch (state)
		{
		case 1:
			printf("check 1\n");
			if (isdigit(buffer[i]))
				state = 2;
			if (buffer[i] == '.')
				state = 5;
			if (!isdigit(buffer[i]) && buffer[i] != '.' && buffer[i] != '\0')
			{
				printf("Not an integer or a real number because it is not \n");
				return flag;
			}
			break;
		case 2:
			printf("check2\n");
			if (isdigit(buffer[i]))
				state = 2;
			if (buffer[i] == '.')
				state = 3;
			if (!isdigit(buffer[i]) && buffer[i] != '.' && buffer[i] != '\0')
			{
				printf("Not an integer or a real number because it has an unknown character \n");
				return flag;
			}
			break;
		case 3:
			if (isdigit(buffer[i]))
				state = 4;
			if (buffer[i] == '.')
				state = 5;
			if (!isdigit(buffer[i]) && buffer[i] != '.'  && buffer[i] != '\0')
			{
				printf("Not an integer or a real number because it has an unknown character \n");
				return flag;
			}
			break;
		case 4:
			if (isdigit(buffer[i]))
				state = 4;
			if (buffer[i] == '.')
				state = 5;
			if (!isdigit(buffer[i]) && buffer[i] != '.'  && buffer[i] != '\0')
			{
				printf("Not an integer or a real number because it an unknown character\n");
				return flag;
			}
			break;
		case 5:
			if (isdigit(buffer[i]))
				state = 5;
			if (buffer[i] == '.')
				state = 5;
			if (!isdigit(buffer[i]) && buffer[i] != '.' && buffer[i] != '\0')
			{
				printf("Not an integer or a real number because it an unknown character\n");
				return flag;
			}
			break;
		}

	}

	if (state == 2)//returns 0 if it is an integer
	{
		flag = 0;
		printf("%s is an integer\n", buffer);
	}
	if (state == 4) //returns 1 if it is a real number
	{
		flag = 1;
		printf("%s is a real number\n", buffer);
	}

	return flag;
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