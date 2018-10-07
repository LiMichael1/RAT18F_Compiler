#include <iostream> 
#include <cmath>
#include <fstream>
#include "fsm.h"
#include <iomanip>
using namespace std;

bool comments;

//EXPECTED INPUT : SOURCE FILE 
//EXPECTED OUTPUT: CLASSIFICATION OF THE TOKENS 

int main() {

	ifstream inFile;				//STORES THE INPUT FILE 
	ofstream outFile;				//STORES THE OUTPUT FILE 
	string file, input;				//STORES THE FILENAME AND THE FILE INPUT 


	cout << "Enter file name: ";
	getline(cin, file);					//GETS FILENAME

	inFile.open(file);					//OPENS FILENAME
	if (inFile.fail())					//ERROR CHECKING IF YOU CAN'T OPEN THE FILE 
	{
		cout << "Invalid file name\n";
	}
	vector<Token> tokens;				//STORES COLLECTION OF TOKENS

	file = "";							


	outFile.open("results.txt");		//OUTPUT FILE
	while (getline(inFile, input))			//GET INPUT LINE BY LINE 
	{
		char *test = &*input.begin();
		tokens = Parser(test);				//GET TOKENS 

		for (size_t i = 0; i < tokens.size(); i++)	//OUTPUT 
		{
			cout << left << setw(15) << tokens[i].LexemeName << setw(15) << tokens[i].TokenName << endl << endl;
			outFile << left << setw(15) << tokens[i].LexemeName << setw(15) << tokens[i].TokenName << endl;
		}

	}
	outFile.close();				//CLOSE THE INPUT/OUTPUT FILES 
	inFile.close();
	system("pause");
	return 0;
}