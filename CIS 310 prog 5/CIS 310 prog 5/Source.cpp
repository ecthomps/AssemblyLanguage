#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;


string dec2hex(string);
string dec2hex(int);
int hex2dec(string);
void spaceHexNum(string *);
void padHexNum(string *, int);


const string hexVals = "0123456789ABCDEF";				
const int INSTRUCTION_COUNT = 8;
const string INSTRUCTIONS[] = {							
	"ORG", "MOVE", "TRAP", "ADD", "ADDI",
	"SUB", "SUBI", "END" };


ofstream outFile("output");

class instructionLine
{
private:
	string lineName;
	string command;
	string leftOperand;
	string rightOperand;
	string comment;

public:

	instructionLine()
	{
		lineName = "";
		rightOperand = "";
		comment = "";
	}


	void setLineName(string ln)
	{
		lineName = ln;
	}

	void setCommand(string c)
	{
		command = c;
	}


	void setOperand(string o)
	{
		string::size_type pos = o.find(",", 0);
		if (pos == string::npos)
		{
			leftOperand = o;
		}
		else
		{
			leftOperand = o.substr(0, pos);
			rightOperand = o.substr(pos + 1, o.size() - pos + 1);
		}
	}


	void appendComment(string c)
	{
		comment = comment + " " + c;
	}


	string generate(string currentAddress, vector<string> &machineCodes, vector<string> &symbolTable)
	{
		padHexNum(&currentAddress, 4);	


		if (lineName != "")			
		{
			spaceHexNum(&currentAddress);
			string tmp = lineName + "\t" + currentAddress;
			symbolTable.push_back(tmp);
		}
		string upperCommand = command;
		for (int i = 0; i<upperCommand.size(); i++)
			upperCommand[i] = toupper(upperCommand[i]);


		int newNum = hex2dec(currentAddress);


		if (upperCommand == "ORG")
		{
			return leftOperand.substr(1, leftOperand.size() - 1);
		}

		else if (upperCommand == "END")
		{
			return currentAddress;
		}

		else if (upperCommand == "MOVE")
		{

			if (leftOperand[0] == '#' && rightOperand[0] != '$')
			{
				string val = dec2hex(leftOperand.substr(1, leftOperand.size() - 1));
				padHexNum(&val, 2);
				val = "303c " + val;
				machineCodes.push_back(val);
				return dec2hex(newNum + 4);
			}
			else if (leftOperand[0] == '#' && rightOperand[0] == '$')
			{
				string val = dec2hex(leftOperand.substr(1, leftOperand.size() - 1));
				padHexNum(&val, 2);
				string val2 = rightOperand.substr(1, rightOperand.size() - 1);
				padHexNum(&val2, 4);
				spaceHexNum(&val2);
				val = "33fc " + val + " " + val2;
				machineCodes.push_back(val);
				return dec2hex(newNum + 8);
			}
			else if (leftOperand[0] == '$')
			{
				string val2 = leftOperand.substr(1, leftOperand.size() - 1);
				padHexNum(&val2, 4);
				spaceHexNum(&val2);
				val2 = "3039 " + val2;
				machineCodes.push_back(val2);
				return dec2hex(newNum + 6);
			}
			else
			{
				string val2 = rightOperand.substr(1, rightOperand.size() - 1);
				padHexNum(&val2, 4);
				spaceHexNum(&val2);
				val2 = "33c0 " + val2;
				machineCodes.push_back(val2);
				return dec2hex(newNum + 6);
			}
		}
		else if (upperCommand == "ADD")
		{
			if (leftOperand[0] == '$')
			{
				string val2 = leftOperand.substr(1, leftOperand.size() - 1);
				padHexNum(&val2, 4);
				spaceHexNum(&val2);
				val2 = "d079 " + val2;
				machineCodes.push_back(val2);
				return dec2hex(newNum + 6);
			}
			else
			{
				string val2 = rightOperand.substr(1, rightOperand.size() - 1);
				padHexNum(&val2, 4);
				spaceHexNum(&val2);
				val2 = "d179 " + val2;
				machineCodes.push_back(val2);
				return dec2hex(newNum + 6);
			}
		}

		else if (upperCommand == "ADDI")
		{
			if (leftOperand[0] == '#' && rightOperand[0] != '$')
			{
				string val = dec2hex(leftOperand.substr(1, leftOperand.size() - 1));
				padHexNum(&val, 2);
				val = "0640 " + val;
				machineCodes.push_back(val);
				return dec2hex(newNum + 4);
			}
			else
			{
				string val = dec2hex(leftOperand.substr(1, leftOperand.size() - 1));
				padHexNum(&val, 2);
				string val2 = rightOperand.substr(1, rightOperand.size() - 1);
				padHexNum(&val2, 4);
				spaceHexNum(&val2);
				val = "0679 " + val + " " + val2;
				machineCodes.push_back(val);
				return dec2hex(newNum + 8);
			}
		}
		else if (upperCommand == "SUB")
		{
			if (leftOperand[0] == '#')
			{
				string val2 = leftOperand.substr(1, leftOperand.size() - 1);
				padHexNum(&val2, 4);
				spaceHexNum(&val2);
				val2 = "9079 " + val2;
				machineCodes.push_back(val2);
				return dec2hex(newNum + 6);
			}
			else
			{
				string val2 = rightOperand.substr(1, rightOperand.size() - 1);
				padHexNum(&val2, 4);
				spaceHexNum(&val2);
				val2 = "9179 " + val2;
				machineCodes.push_back(val2);
				return dec2hex(newNum + 6);
			}
		}

		else if (upperCommand == "SUBI")
		{
			if (leftOperand[0] == '#' && rightOperand[0] != '$')
			{
				string val = dec2hex(leftOperand.substr(1, leftOperand.size() - 1));
				padHexNum(&val, 2);
				val = "0440 " + val;
				machineCodes.push_back(val);
				return dec2hex(newNum + 4);
			}
			else
			{
				string val = dec2hex(leftOperand.substr(1, leftOperand.size() - 1));
				padHexNum(&val, 2);
				string val2 = rightOperand.substr(1, rightOperand.size() - 1);
				padHexNum(&val2, 4);
				spaceHexNum(&val2);
				val = "0479 " + val + " " + val2;
				machineCodes.push_back(val);
				return dec2hex(newNum + 8);
			}
		}
		else if (upperCommand == "TRAP")
		{
			if (leftOperand == "#0")
			{
				machineCodes.push_back("4e40");
				return dec2hex(newNum + 2);
			}
			else if (leftOperand == "#1")
			{
				machineCodes.push_back("4e41");
				return dec2hex(newNum + 2);
			}
			else if (leftOperand == "#2")
			{
				machineCodes.push_back("4e42");
				return dec2hex(newNum + 2);
			}
		}

		return "";
	}
};

bool isInstruction(string token)
{
	string upperToken = token;
	for (int i = 0; i<token.size(); i++)
		upperToken[i] = toupper(upperToken[i]);

	for (int j = 0; j<INSTRUCTION_COUNT; j++)
	{
		if (INSTRUCTIONS[j] == upperToken)
			return true;
	}

	return false;
}


string dec2hex(string num)
{
	int number = atol(num.c_str());

	return dec2hex(number);
}

string dec2hex(int num)
{
	char hexstring[10];
	_itoa_s(num, hexstring, 16);
	return hexstring;

}

int hex2dec(string num)
{
	int newNum = 0;
	int place = 0;

	for (int i = 0; i<num.size(); i++)
	{
		int val = 0;
		for (int j = 0; j<hexVals.size(); j++)
			if (toupper(num[num.size() - place - 1]) == hexVals[j])
				val = j;

		val = pow(16, place) * val;
		newNum += val;

		place++;
	}

	return newNum;
}



/*

Purpose:	Ensures that hexNum is at least n bytes long, otherwise,
it will pad the number
*/
void padHexNum(string *hexNum, int numBytes)
{
	// There's 2 characters for each byte in a hex number
	numBytes *= 2;

	for (int i = hexNum->size(); i<numBytes; i++)
		*hexNum = "0" + *hexNum;
}

void spaceHexNum(string *hexNum)
{
	int n = 0;
	for (int i = 0; i<hexNum->size(); i++)
	{
		if (n % 4 == 0 && n > 0)
		{
			hexNum->insert(i, " ");
			n = 0;
		}
		else
			n++;
	}
}


int main()
{
	string currentAddress = "0";
	vector<string> machineCodes;
	vector<string> symbolTable;


	outFile << "******************************************************************************" << endl <<
		"* Thank you for using the program.				              *" << endl <<
		"* This program simulates a 2-pass assembler in C++.                           *" << endl <<
		"* The input to this program is an assembly language program.                  *" << endl <<
		"* The output includes a symbol table and the machine code version of the input*" << endl <<
		"* You can view the output through the output file labeled ' output.txt '      *" << endl <<
		"*******************************************************************************" << endl << endl;


	string inFileName;
	cout << "Please, Enter the assembly file name: // followed by the extentiosn for example input.txt" << endl;
	outFile << "Please, Enter the assembly file name: // followed by the extentiosn for example input.txt" << endl;
	cin >> inFileName;

	// Openning the file

	ifstream inFile;
	inFile.open(inFileName.c_str());


	// Read the entire input file
	cout << endl;
	cout << "Inputting Data ........." << endl << endl << endl << endl << endl;
	outFile << "Inputting Data ........." << endl << endl << endl << endl << endl;

	while (!inFile.eof())
	{
		string currentLine;
		getline(inFile, currentLine);

		string token;
		int tokenCount = 1;
		int commentToken = 5;
		bool commandNext = false;
		instructionLine instLine;

		for (int i = 0; i<currentLine.size(); i++)
		{
			if (isspace(currentLine[i]) || i == currentLine.size() - 1)
			{
				if (i == currentLine.size() - 1)
					token.append(1, currentLine[i]);

				if (token.size() > 0)
				{

					if (tokenCount == 1 && isInstruction(token))
					{
						tokenCount = 3;
						commandNext = true;
						cout << token << "\t";
						outFile << token << "\t";

						instLine.setCommand(token);
					}
					else if (tokenCount == 2 && isInstruction(token))
					{
						tokenCount = 4;
						commandNext = true;
						cout << token << "\t";
						outFile << token << "\t";

						instLine.setCommand(token);
					}

					else if (commandNext)
					{
						commandNext = false;
						cout << token << "\t";
						outFile << token << "\t";

						instLine.setOperand(token);
					}

					else if (tokenCount >= commentToken)
					{
						cout << token << " ";
						outFile << token << " ";

						instLine.appendComment(token);
					}

					else
					{
						cout << token << "\t";
						outFile << token << "\t";

						instLine.setLineName(token);
					}

					tokenCount++;

				}
				else
				{
					cout << "\t";
					outFile << "\t";
				}

				token = "";
			}

			else
			{
				token.append(1, currentLine[i]);
			}

		}

		currentAddress = instLine.generate(currentAddress, machineCodes, symbolTable);
		cout << endl;
	}

	inFile.close();


	cout << endl;
	cout << "Preparing the output .........." << endl << endl << endl << endl;
	outFile << "Preparing the output .........." << endl << endl << endl << endl;

	cout << " ________________________" << endl << endl;
	cout << "  Symbol Table " << endl;
	cout << " ________________________" << endl << endl;

	outFile << " ________________________" << endl << endl;
	outFile << "  Symbol Table " << endl;
	outFile << " ________________________" << endl;
	for (int m = 0; m < symbolTable.size(); m++)
	{
		cout << symbolTable.at(m) << endl;
		outFile << symbolTable.at(m) << endl;
		cout << endl;
		outFile << endl;
	}
	cout << " _______________________" << endl << endl;
	cout << " Machine Code Table     " << endl;
	cout << " _______________________ " << endl << endl;

	outFile << " _______________________" << endl << endl;
	outFile << " Machine Code Table     " << endl;
	outFile << " _______________________ " << endl;

	for (int n = 0; n < machineCodes.size(); n++)
	{
		cout << machineCodes.at(n) << endl;
		cout << endl;
		outFile << machineCodes.at(n) << endl;
		outFile << endl;
	}




	outFile.close();

	system("pause");
	return 0;
}