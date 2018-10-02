#include "FSM.h"

int FSM(char* buffer) //)= operator, 1= separator , 2 =int , 3= real, 4= keyword, 5 = identifer , 6 = unknown
{
    int flag;	 //flag for the end result 

    //checks for operators or separators first
    if (isOperator(buffer))				   //0 = operator
    {
	   printf("%s is an operator\n\n", buffer);
	   return 0;
    }

    if (isSeparator(buffer))				   //1 = separator
    {
	   printf("%s is a separator\n\n", buffer);
	   return 1;
    }

    int buffer_length = strlen(buffer);

    int state = 1;

    for (int i = 0; i < buffer_length; i++)
    {
	   switch (state)
	   {
	   case 1:
		  if (isalpha(buffer[i]))
			 state = 5;
		  if (isdigit(buffer[i]))
			 state = 2;
		  if (buffer[i] == '.')
			 state = 8;
		  if (Unknown(buffer[i]))
			 return -1;
		  break;
	   case 2:
		  if (isalpha(buffer[i]))
			 state = 8;
		  if (isdigit(buffer[i]))
			 state = 2;
		  if (buffer[i] == '.')
			 state = 3;
		  if (Unknown(buffer[i]))
			 return -1;
		  break;
	   case 3:
		  if (isalpha(buffer[i]))
			 state = 8;
		  if (isdigit(buffer[i]))
			 state = 4;
		  if (buffer[i] == '.')
			 state = 8;
		  if (Unknown(buffer[i]))
			 return -1;
		  break;
	   case 4:
		  if (isalpha(buffer[i]))
			 state = 8;
		  if (isdigit(buffer[i]))
			 state = 4;
		  if (buffer[i] == '.')
			 state = 8;
		  if (Unknown(buffer[i]))
			 return -1;
		  break;
	   case 5:
		  if (isalpha(buffer[i]))
			 state = 7;
		  if (isdigit(buffer[i]))
			 state = 6;
		  if (buffer[i] == '.')
			 state = 8;
		  if (Unknown(buffer[i]))
			 return -1;
		  break;
	   case 6:
		  if (isalpha(buffer[i]))
			 state = 7;
		  if (isdigit(buffer[i]))
			 state = 6;
		  if (buffer[i] == '.')
			 state = 8;
		  if (Unknown(buffer[i]))
			 return -1;
		  break;
	   case 7:
		  if (isalpha(buffer[i]))
			 state = 7;
		  if (isdigit(buffer[i]))
			 state = 6;
		  if (buffer[i] == '.')
			 state = 8;
		  if (Unknown(buffer[i]))
			 return -1;
		  break;
	   case 8:
		  if (isalpha(buffer[i]))
			 state = 8;
		  if (isdigit(buffer[i]))
			 state = 8;
		  if (buffer[i] == '.')
			 state = 8;
		  if (Unknown(buffer[i]))
			 return -1;
		  break;
	   }

    }

    if (state == 2) {	   //2 = integer
	   printf("%s is an integer\n\n", buffer);
	   flag = 2;
    }
    else if (state == 4) {  //3 = real number
	   printf("%s is a real number\n\n", buffer);
	   flag = 3;
    }
    else if (state == 5 || state == 7)
    {
	   if (isKeyword(buffer))
	   {
		  flag = 4;				//4 = keyword
		  printf("%s is a keyword\n\n", buffer);
	   }
	   else {
		  flag = 5;				//5 = identifier
		  printf("%s is an identifier\n\n", buffer);
	   }

    }
    else
    {
	   flag = 6;					//Unknown
	   printf("Can't find the type for %s\n\n", buffer);
    }



    return flag;
}

int Unknown(char buffer)
{
    if (!isdigit(buffer) && !isalpha(buffer) && buffer != '.' && buffer != '\0')
    {
	   printf("Unknown Character: '%c' \n\n", buffer);
	   return 1;

    }
    return 0;
}

int isKeyword(char* buffer)	//CALL IN FSM_ID

{	//Feel free to add more if needed
    std::vector<std::string> keywords = {
	   "if", "ifend", "put", "get", "else",
	   "while", "whileend", "return", "true", "false"
    };

    int flag = 0;

    for (size_t i = 0; i< keywords.size(); i++)
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

    for (size_t i = 0; i< operators.size(); i++)
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

    for (size_t i = 0; i< separators.size(); i++)
    {
	   if (strcmp(buffer, separators[i].c_str()) == 0)
	   {
		  flag = 1;
	   }
    }

    return flag;
}

