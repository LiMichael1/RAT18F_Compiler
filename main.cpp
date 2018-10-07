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

	ifstream inFile;
	ofstream outFile;
	string file, input;


	cout << "Enter file name: ";
	getline(cin, file);

	inFile.open(file);
	if (inFile.fail())
	{
		cout << "Invalid file name\n";
	}
	vector<Token> tokens;

	file = "";


	outFile.open("results.txt");
	while (getline(inFile, input))
	{
		char *test = &*input.begin();
		//strcpy_s(test, input.length(), input.c_str());        // Copy text from file into a character array

		tokens = Parser(test);

		for (size_t i = 0; i < tokens.size(); i++)
		{
			cout << left << setw(15) << tokens[i].LexemeName << setw(15) << tokens[i].TokenName << endl << endl;
			outFile << left << setw(15) << tokens[i].LexemeName << setw(15) << tokens[i].TokenName << endl;
		}

	}
	outFile.close();
	inFile.close();
	system("pause");
	return 0;
}