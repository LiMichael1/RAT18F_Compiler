#include <iostream>
#include <string>
#include <stack>
#include <iomanip>
using namespace std;

int Pop_JS();
void Push_JS(int);
bool exists_symtable(string lex);
int sym_table_type(string lex);


struct Instruction //changeable
{
	int address; 
	string op;
	string oprnd;
};

struct Symbol //changeable
{
	string lexeme;
	int mem_addr;
	string type;   //int/boolean
};

stack<string> type_stack;
stack<int> jump_stack;
vector<Instruction> instr_table(1000);
vector<Symbol> sym_table(100);
int line_address = 1;
int instr_address = 0; 

int Memory_addr = 5000;


void gen_instr(string op, string oprnd)
/* instr_address  shows the current insturction address is global */
{
	instr_table [instr_address].address = line_address;
	instr_table [instr_address].op = op;
	instr_table [instr_address].oprnd = oprnd;
	instr_address++;
	line_address++;
	
}

void back_patch (int jump_addr)
{
	int addr = Pop_JS();
	instr_table[addr].oprnd = to_string(jump_addr);
}
int get_address(string lexeme)
{
    int addr = 0;
    int size = 0;
    bool found = false;

    while (!found && size < instr_table.size())
    {
        if (instr_table[size].op == lexeme)
        {
		found = true;
		if(instr_table[size].oprnd != "nil")
		{
            		addr = stoi(instr_table[size].oprnd);	
		}
		else
			addr = 666;
        }
	size++;
    }
    return addr;
}
void Push_JS(int addr)
{
	jump_stack.push(addr);
}

int Pop_JS()
{
	int s ; 
	if(!jump_stack.empty())
	{
		s = jump_stack.top();
		jump_stack.pop();
	}
	else
	{
		cerr<< "Error : nothing in the stack\n";
	}
	return s;
}
string get_type(string lex)
{
	if(exists_symtable(lex))
	{
		int x = sym_table_type(lex);
		if(x != -1)
		{
			return sym_table[x].type;
		}
		else
			return "Empty";
	}
	else 
		return "Empty";
}
int sym_table_type(string lex)
{
	for(int i =0 ; i< sym_table.size(); i++)
	{
		if(sym_table[i].lexeme == lex)
		{
			return i;
		}
	}
		cerr<< "Doesn't exist\n";
		return -1;
}

//Checks to see if it's in the table
bool exists_symtable(string lex)
{
	for(int i =0 ; i< sym_table.size(); i++)
	{
		if(sym_table[i].lexeme == lex)
		{
			return true;
		}
	}
	return false;
}
//insert into the symbol table
void insert_symtable(string lex , string type)
{
	if(exists_symtable(lex))
	{
		cerr << lex << "already exists\n";
	}
	else 
	{
		if(type == "Real")
		{
			cerr<< "Doesn't exist\n";
		}
		else
		{
			Symbol s;
			s.lexeme = lex;
			s.type = type;
			s.mem_addr = Memory_addr;
			Memory_addr++;

			sym_table.push_back(s);
		}
	}
}

//printing functions

void print_sym_table(ofstream& outputFile)
{
	cout << "Lexeme" << setw(20) << "Memory address" << setw(20) << "type\n";
	outputFile<< "Lexeme" << setw(20) << "Memory address" << setw(20) << "type\n";
	for(int i = 0 ; i< sym_table.size();i++)
	{
		cout << sym_table[i].lexeme << setw(20) << sym_table[i].mem_addr << setw(20) << sym_table[i].type <<endl;
		outputFile<< sym_table[i].lexeme << setw(20) << sym_table[i].mem_addr << setw(20) << sym_table[i].type <<endl;
	}
}
void print_instr_table(ofstream& outputFile)
{
	cout<< "Address" << setw(20) << "Op" << setw(20)<< "Oprnd\n";
	outputFile<< "Address" << setw(20) << "Op" << setw(20)<< "Oprnd\n";
	for(int i = 0 ; i< sym_table.size();i++)
	{
		cout << instr_table[i].address << setw(20) << instr_table[i].op << setw(20) << instr_table[i].oprnd <<endl;
		outputFile<< instr_table[i].address << setw(20) << instr_table[i].op << setw(20) << instr_table[i].oprnd <<endl;
	}
}
