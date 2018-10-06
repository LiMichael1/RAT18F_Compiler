#include <iostream> 
#include <cmath>
#include <fstream>
#include "fsm.h"

using namespace std;

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

    bool commentstar = false;
    bool commentbracket = false;

    outFile.open("results.txt");
    while (getline(inFile, input))
    {
	   char *test = new char[input.length() + 1];
	   strcpy(test, input.c_str());        // Copy text from file into a character array

	   tokens = lexicalAnalyzer(test);

	   for (size_t i = 0; i < tokens.size(); i++)
	   {
		  cout << tokens[i].LexemeName << " " << tokens[i].TokenName << endl << endl;
		  outFile << tokens[i].LexemeName << "\t " << tokens[i].TokenName << endl;
	   }
	   delete[] test;
    }
    outFile.close();
    inFile.close();
    system("pause");
    return 0;
}