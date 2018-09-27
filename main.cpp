#include <iostream> 
#include <string>
#include <vector>
#include <fstream>
#include "fsm.h"


//EXPECTED INPUT : SOURCE FILE 
//EXPECTED OUTPUT: CLASSIFICATION OF THE TOKENS 

int main(int argc, char *argv)
{

	if (argc< 2)
	{

	}

	std::ifstream file(argv);
	if (!file.is_open())
	{
		printf("File does not exist or you can't access it\n");
		return EXIT_FAILURE;
	}

	while (!file.eof())		//reads to the end of the file
	{

	}

	 

	std::cout << "Output\n";
	std::cout << "tokens \t\t\t\t lexeme\n";







	return 0;
}