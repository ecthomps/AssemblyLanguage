#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

class hexNumLibr {

	public:
		void setHex(string val) {
			hexVal = val;
			sDigit = val.size();
		}

		char revertHex(int decVal) {
			if (decVal == 0) 
				return '0';			
			else if (decVal == 1) 
				return '1';			
			else if (decVal == 2) 
				return '2';			
			else if (decVal == 3) 
				return '3';			
			else if (decVal == 4) 
				return '4';			
			else if (decVal == 5) 
				return '5';			
			else if (decVal == 6) 
				return '6';			
			else if (decVal == 7) 
				return '7';			
			else if (decVal == 8) 
				return '8';			
			else if (decVal == 9) 
				return '9';			
			else if (decVal == 10) 
				return 'A';			
			else if (decVal == 11) 
				return 'B';			
			else if (decVal == 12) 
				return 'C';			
			else if (decVal == 13) 
				return 'D';			
			else if (decVal == 14) 
				return 'E';			
			else if (decVal == 15)
				return 'F';
			else
				return 'x';
		}

		int convertDecimal(char decVal) {
			if (decVal == '0')
				return 0;
			else if (decVal == '1')
				return 1;
			else if (decVal == '2')
				return 2;
			else if (decVal == '3')
				return 3;
			else if (decVal == '4')
				return 4;
			else if (decVal == '5')
				return 5;
			else if (decVal == '6')
				return 6;
			else if (decVal == '7')
				return 7;
			else if (decVal == '8')
				return 8;
			else if (decVal == '9')
				return 9;
			else if (decVal == 'A')
				return 10;
			else if (decVal == 'B')
				return 11;
			else if (decVal == 'C')
				return 12;
			else if (decVal == 'D')
				return 13;
			else if (decVal == 'E')
				return 14;
			else if (decVal == 'F')
				return 15;
			else
				return 0;
		}

		string addHex(hexNumLibr hexNum) {
			int val = sDigit - 1;
			int carry = 0, sum;
			char val1, val2;
			for (int i = hexNum.sDigit - 1; i != -1; i--) {
				val1 = hexVal[val];
				val2 = hexNum.hexVal[i];		

				int sum;
				sum = convertDecimal(val1) + convertDecimal(val2) + carry;
				if (sum >= 16) {
					carry = 1;
					sum = sum - 16;
				}
				else
					carry = 0;

				hexVal[val] = revertHex(sum);
				val--;
			}
			sum = 0;
			while (carry > 0)	{
				if (val == -1)	{
					hexVal.insert(hexVal.begin(), revertHex(1));
					sDigit = sDigit + 1;
					val++;
					carry = 0;
				}
				val1 = hexVal[val];
				sum = convertDecimal(val1) + carry;
				if (sum >= 16) {
					carry = 1;
					sum -= 16;
					hexVal[val] = revertHex(sum);
					if (val == 0 && carry == 1) 	{
						hexVal.insert(hexVal.begin(), revertHex(1));
						sDigit = sDigit + 1;
						val++;
						carry = 0;
					}
					val--;
				}
				else {
					carry = 0;
					hexVal[val] = revertHex(sum);
					val--;
				}
			}
			return hexVal;
		}

		string getHex() {
			return hexVal;
		}	

private:
	string hexVal;
	int sDigit;	
};

string clearSpaces(string fixStr) {
	stringstream getString;
	string newString;

	getString << fixStr;
	getString >> newString;
	getString.flush();

	return newString;
}



class hexTable
{

public:
	string findEntry(string numVal) {
		for (string::size_type i = 0; i < newTable.size(); i++) {
			if (newTable[i].token == numVal)
				return newTable[i].memLoc;
		}
	}

	void addEntry(string val1, string val2) {
		SymbolEn temp;
		temp.token = val1;
		temp.memLoc = val2;

		newTable.push_back(temp);
	}

	int getSize() {
		return newTable.size();
	}

	string getSymbol(int val) {
		return newTable[val].token;
	}

	string getAddress(int val) {
		return newTable[val].memLoc;
	}

private:
	struct SymbolEn
	{
		string token;
		string memLoc;

		SymbolEn() {
			token = "";
			memLoc = "";
		}

	};

	vector<SymbolEn> newTable;
};

class TwoAssembler {
	
	public:
		void inputDataItems() {

			fstream fin;
			fin.open("dataFile.txt");
			cout << "Collecting Data from Data.txt" << endl;

			if (fin)
			{
				string TestString;

				while (fin)
				{
					getline(fin, TestString);
					macLine.push_back(TestString);


				}
			}
			else
				cout << "Could not read the file";

			string lastAddress;
			entryTemp.memLoc = "";
			entryTemp.macOper = "";
			entryTemp.oper = "";
			entryTemp.comMand = "";

			for (string::size_type i = 0; i<macLine.size() - 1; i++)
			{

				entryTemp.memLoc = "";
				entryTemp.macOper = "";
				entryTemp.oper = "";
				entryTemp.comMand = "";

				if (isLabel(i))
				{
					string wString = macLine[i].substr(10, 10);
					wString = clearSpaces(wString);
					if (wString == "ORG") {
						entryTemp.memLoc = wString.substr(5, 3);
						lastAddress = entryTemp.memLoc;
					}
					else {
						string Label;
						Label = macLine[i].substr(0, 10);
						Label = clearSpaces(Label);
						symTable.addEntry(Label, lastAddress);
						string machineCode = getCommand(i);

						if (machineCode == "END")
							break;

						entryTemp.macOper = machineCode;
						entryTemp.memLoc = lastAddress;

						int resolveAddress = getLocation(machineCode);

						hexNumLibr addressHex, incrementHex;
						char temp = incrementHex.revertHex(resolveAddress);
						string toSetIncrement;

						toSetIncrement.push_back(temp);
						addressHex.setHex(lastAddress);
						incrementHex.setHex(toSetIncrement);
						addressHex.addHex(incrementHex);
						lastAddress = addressHex.getHex();
						outputEnt.push_back(entryTemp);
					}
				}
				else {
					string wString = macLine[i].substr(10, 10);
					wString = clearSpaces(wString);
					if (wString == "ORG")
					{
						entryTemp.memLoc = macLine[i].substr(21, 3);
						lastAddress = entryTemp.memLoc;
					}
					else {
						string machineCode = getCommand(i);

						if (machineCode == "END")
							break;

						entryTemp.macOper = machineCode;
						entryTemp.memLoc = lastAddress;

						int resolveAddress = getLocation(machineCode);
						hexNumLibr addressHex, incrementHex;
						char temp = incrementHex.revertHex(resolveAddress);
						string toSetIncrement;

						toSetIncrement.push_back(temp);
						addressHex.setHex(lastAddress);
						incrementHex.setHex(toSetIncrement);
						addressHex.addHex(incrementHex);
						lastAddress = addressHex.getHex();
						outputEnt.push_back(entryTemp);
					}

				}
			}
		}

		void operTable() {
			
		}

		void printLines() {
			ofstream fout("dataOUt.txt");

			cout << "Inputting Data to Output.txt" << endl;
			fout << "******************************************************************************" << endl;
			fout << "Input Data:" << endl;

			for (string::size_type i = 0; i< macLine.size() - 1; i++)
				fout << macLine[i] << endl;

			fout << "******************************************************************************" << endl << endl;
			fout << "Output Data:" << endl;

			fout << "Address" << "\t\t\t" << "Machine Code" << "\t\t\t" << "Operands"
				<< "\t\t\t" << "Instructions" << endl;

			for (string::size_type i = 0; i <outputEnt.size(); i++) {
				fout << outputEnt[i].memLoc << "\\t\t\t" << outputEnt[i].macOper
					<< "\t\t\t" << outputEnt[i].oper << "\t\t\t" << outputEnt[i].comMand
					<< endl;
			}

			fout << endl << endl << endl;
			fout << "Symbol" << "\t\t" << "Address" << endl;

			for (int i = 0; i< symTable.getSize() - 1; i++)
				fout << symTable.getSymbol(i) << "      " << symTable.getAddress(i) << endl;

			fout << "******************************************************************************" << endl;
		}

	private:
		struct OutlineEntry {
			string memLoc, macOper;
			string oper, comMand;
		};

		vector<string> macLine;
		vector<OutlineEntry> outputEnt;
		OutlineEntry entryTemp;
		hexTable symTable;

		bool isLabel(int val) {
			string wString = macLine[val];
			if (wString[0] == ' ')
			{
				return false;
			}
			else
				return true;
		}

		string getCommand(int val) {
			string wString = macLine[val].substr(10, 30);
			string Operator = clearSpaces(wString);
			string Operand1;
			string Operand2;

			if (Operator == "END")
				return "END";

			if (Operator == "TRAP")
			{

				Operand1 = clearSpaces(wString.substr(10, 10));

				if (Operand1 == "#0")
				{
					entryTemp.comMand = wString;
					entryTemp.oper = "0000";
					return "4E40";

				}
				else
					if (Operand1 == "#1")
					{
						entryTemp.comMand = wString;
						entryTemp.oper = "0001";
						return "4E41";
					}
					else
						if (Operand1 == "#2")
						{
							entryTemp.comMand = wString;
							entryTemp.oper = "0002";
							return "4E42";

						}

			}
			else
			{
				stringstream twoOperands;

				twoOperands << wString.substr(10, wString.length() - 10);
				if (Operator == "MOVE")
				{
					twoOperands >> Operand1;
					if (Operand1[0] == '#')
					{
						entryTemp.comMand = wString;
						Operand1 = Operand1.substr(1, 2);
						int decimalNum = atoi(Operand1.c_str());
						char buffer[20];
						Operand1 = _itoa_s(decimalNum, buffer, 16);

						twoOperands >> Operand2;
						entryTemp.oper = Operand1 + ',' + ' ' + Operand2;
						return "33FC";

					}
					if (Operand1[0] == 'D')
					{
						entryTemp.comMand = wString;
						Operand1 = Operand1.substr(0, 2);
						twoOperands >> Operand2;
						Operand2.erase(Operand2.end());
						entryTemp.oper = Operand2;
						return "33C0";
					}
					if (Operand1[0] == '$')
					{
						entryTemp.comMand = wString;
						twoOperands >> Operand2;
						entryTemp.oper = Operand1;
						return "3039";
					}

				}
				else
				{
					if (Operator == "ADD")
					{
						entryTemp.comMand = wString;
						twoOperands >> Operand2;
						Operand2.erase(Operand2.end());
						entryTemp.oper = Operand2;
						return "D079";
					}
					else
					{

						if (Operator == "ADDI")
						{
							entryTemp.comMand = wString;
							twoOperands >> Operand1;
							Operand1 = Operand1.substr(1, 2);
							int decimalNum = atoi(Operand1.c_str());
							char buffer[20];
							Operand1 = _itoa_s(decimalNum, buffer, 16);
							twoOperands >> Operand2;
							entryTemp.oper = Operand1 + ',' + ' ' + Operand2;
							return "0679";
						}
						else
							return "0000";
					}
				}
			}
		}

		int getLocation(string codeItems) {
			if (codeItems == "33FC" | codeItems == "0679")
				return 8;
			if (codeItems == "33C0" | codeItems == "3039" | codeItems == "D079")
				return 6;
			if (codeItems == "4E41" | codeItems == "4E42" | codeItems == "4E40")
				return 2;
		}		
};

int main()
{
	TwoAssembler passAssem;

	passAssem.inputDataItems();
	passAssem.printLines();

	return 0;
}
