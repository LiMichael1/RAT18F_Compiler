#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <ctype.h>

int Unknown(char buffer)
{

    if (!isdigit(buffer) && !isalpha(buffer) && buffer != '.' && buffer != '\0')
    {
	   printf("Unknown Character: '%c' \n\n", buffer);
	   return 1;

    }
    return 0;
}




int FSM(char* buffer)
{


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

    if (state == 2)
	   printf("%s is an integer\n\n", buffer);
    else if (state == 4)
	   printf("%s is a real number\n\n", buffer);
    else if (state == 5 || state == 7)
	   printf("%s is an identifier\n\n", buffer);
    else
	   printf("%s is an unknown type\n\n", buffer);


}


int main()
{

    char a[] = "2.2";
    char b[] = "222234";
    char c[] = "2";
    char d[] = "fewofjewo";
    char e[] = "sfew87832x";
    char f[] = "x";
    char g[] = "x2";
    char h[] = "x73x832";
    char j[] = "x$";

    FSM(a);
    FSM(b);
    FSM(c);
    FSM(d);
    FSM(e);
    FSM(f);
    FSM(g);
    FSM(h);
    FSM(j);

    system("pause");
    return 0;
}