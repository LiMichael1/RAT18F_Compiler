#include <iostream>
#include <string>
#include <stack>
#include <iomanip>
using namespace std;

int Pop_JS();
void Push_JS(int);

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

stack<int> jump_stack;
vector<Instruction> instr_table(1000);
vector<Symbol> sym_table(100);
int inst_address = 1;
int instr_address = 0; 

int Memory_addr = 5000;


void gen_instr(string op, string oprnd)
/* instr_address  shows the current insturction address is global */
{
	instr_table [instr_address].address = inst_address;
	instr_table [instr_address].op = op;
	instr_table [instr_address].oprnd = oprnd;
	instr_address++;
	inst_address++;
	
};

void back_patch (int jump_addr)
{
	int addr = Pop_JS();
	instr_table[addr].oprnd = to_string(instr_address);
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
            addr = instr_table[size].address;
            found = true;
        }
    }
    return addr;
}
void Push_JS(int addr)
{
	if(addr > 4999)
	{
		jump_stack.push(addr);
		
	}
	else
	{
		cerr<< "Please enter something over 5000\n";
	}
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
	cout<< "Address\tOp\tOprnd\n";
	outputFile<< "Address\tOp\tOprnd\n";
	for(int i = 0 ; i< sym_table.size();i++)
	{
		cout << instr_table[i].address << setw(20) << instr_table[i].op << setw(20) << instr_table[i].oprnd <<endl;
		outputFile<< instr_table[i].address << setw(20) << instr_table[i].op << setw(20) << instr_table[i].oprnd <<endl;
	}
}
