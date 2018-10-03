#include <iostream> 
#include <cmath>
#include <fstream>
#include "fsm.h"


//EXPECTED INPUT : SOURCE FILE 
//EXPECTED OUTPUT: CLASSIFICATION OF THE TOKENS 

int main()
{
    char filename[50];
    printf("Please enter the filename: \n");

    std::cin.getline(filename, 50);

    std::ifstream file(filename);
    if (!file.is_open())
    {
	   printf("File does not exist or you can't access it\n");
	   return EXIT_FAILURE;
    }

    while (!file.eof())		//loops until the end of the file
    {
	   bool commentBracket = false;
	   bool commentStar = false;
	   char buffer;
	   file.get(buffer);
	   if (buffer == '[')
	   {
		  commentBracket = true;
	   }
	   if (commentBracket && buffer == '*')
	   {
		  commentStar = true;
	   }
	   if (commentBracket && commentStar && buffer == '*')
	   {
		  commentStar = false;
	   }
	   if (commentBracket && buffer == ']')
	   {
		  commentBracket = false;
	   }
	   if (!commentBracket && !commentStar)
	   {
		  commentBracket = false;
		  std::cout << FSM(new char(buffer));
	   }

    }

    x=x

    return 0;
}