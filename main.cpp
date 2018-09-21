#include <iostream> 
#include <string>
#include <vector>

int main()
{
	

	


	return 0;
}

int FSM_ID(char* buffer)	//CALL WHEN THE FIRST CHAR IS A LETTER
{
	int flag = 0;

	
	if(isKeyword(buffer))		//if it is an identifier
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

	

	return flag; 
}

int FSM_REAL(char* buffer)	//CALL IN INT- CHECK FOR DECIMALS 
{
	int flag = 0; 



	return flag; 
}

void Unknown()		//CALL WHEN NOT A TOKEN
{
	

}

int isKeyword   ( char* buffer)	//CALL IN FSM_ID

{	//Feel free to add more if needed
	vector<string> keywords  = {
		"if", "ifend", "put", "get", "else", 
		"while", "whileend", "return", "true", "false" 
	};	
	
	int flag = 0;

	for(int i = 0; i< keywords.length();i++)
	{
		if(strcmp(buffer, keywords[i].c_str()) == 0)
		{
			flag = 1; 
			break;
		}
	}
	
	return flag; 
}


int isOperator (char * buffer)
{	//feel free to add if needed
	vector<string> operators = {
		"+", "-", "*", "=", "==", "^=",
		">", "<", "=>", "=<"
	};	
	
	int flag = 0;

	for(int i = 0; i< operators.length();i++)
	{
		if(strcmp(buffer, operators[i].c_str()) == 0)
		{
			flag = 1; 
			break;
		}
	}
	
	return flag; 

}

int isSeparator (char * buffer)
{	//feel free to add more
	vector<string> separators  = {
		"$$", " ", ":", ",", ";",
		"{}", "::=", "|", "/"			 
	};

	int flag = 0;

	for(int i = 0; i< separators.length();i++)
	{
		if(strcmp(buffer, separators[i].c_str()) == 0)
		{
			flag = 1; 
			break;
		}
	}
	
	return flag; 
}



