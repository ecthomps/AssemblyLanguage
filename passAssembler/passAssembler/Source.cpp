#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

const int MAX_COUNT = 8;
const int HEX_VAL = 10;
const int HEX_BASE = 16;
const string COMMANDS[MAX_COUNT] = { "ADD", "ADDI", "SUB", "SUBI",
									    "MOVE", "ORG", "TRAP", "END" };
const string HEX_VALS = "0123456789ABCDEF";

string decHexConv(int numVal) {
	char hexString[HEX_VAL];

	_itoa_s(numVal, hexString, 16);
	return hexString;
}

string convDec2Hex(string numVal) {
	int val = atol(numVal.c_str());
	return decHexConv(val);
}

int convHex2Dec(string numVal) {
	int total = 0, val = 0;	
	int loc;
	for (int i = 0; i<numVal.size(); i++) {	
		loc = 0;
		for (int j = 0; j < HEX_VALS.size(); j++)
			if (toupper(numVal[numVal.size() - loc - 1]) == HEX_VALS[i])
				val = i;

		val = pow(HEX_BASE, loc) * val;
		total += val;
		loc++;
	}

	return total;
}

bool isCommand(string symInstruc) {
	string signCom = symInstruc;

	for (int i = 0; i < symInstruc.size(); i++)
		signCom.at(i) = toupper(signCom[i]);
	
	for (int j = 0; j < MAX_COUNT; j++)	{
		if (COMMANDS[j] == signCom)
			return true;
	}

	return false;
}

void spaceHexNum(string* numVal) {
	int val = 0;
	for (int i = 0; i < numVal->size(); i++)
	{
		if (val % 4 == 0 && val > 0)
		{
			numVal->insert(i, " ");
			val = 0;
		}
		else
			val++;
	}
}

void fillHexNum(string* numVal, int numMem) {

	for (int i = numVal->size(); i < numMem; i++)
		*numVal = "0" + *numVal;
}

class passAssem {
public:
	passAssem() {
		comment = "", instruction = "";
		rightOper = "", leftOper = "";
		lineName = "";
	}

	void setComment(string cmt) {
		this->comment = comment + " " + cmt;
	}

	void setInstruction(string instruc) {
		this->instruction = instruc;
	}

	void setLineName(string ln) {
		this->lineName = ln;
	}

	void setOper(string oper) {
		string::size_type posVal = oper.find(",", 0); 
		if (posVal == string::npos) {
			leftOper = oper;
		}
		else {
			rightOper = oper.substr(posVal + 1, oper.size() - posVal + 1);
			leftOper = oper.substr(0, posVal);
		}
	}

	string computeDecHex(string curLoc, vector<string>& codeItems,
		           vector<string>& symTable) {
		string strAddress, strCom = instruction, valLeftOper;
		string valRightOper, valOper;
		
		fillHexNum(&curLoc, 4);

		if (lineName != "") {
			spaceHexNum(&curLoc);
			strAddress = lineName + "\t" + curLoc;
			symTable.push_back(strAddress);
		}
		
		for (int i = 0; i < strCom.size(); i++)
			strCom.push_back(toupper(strCom[i]));

		int val = convHex2Dec(curLoc);

		if (strCom == "ADD") {
			if (leftOper.at(0) == '$') {
				valLeftOper = leftOper.substr(1, leftOper.size() - 1);
				fillHexNum(&valLeftOper, 4);
				spaceHexNum(&valLeftOper);
				valLeftOper = "d079 " + valLeftOper;
				codeItems.push_back(valLeftOper);
				return decHexConv(val + 6);
			}
			else {
				valRightOper = rightOper.substr(1, rightOper.size() - 1);
				fillHexNum(&valRightOper, 4);
				spaceHexNum(&valRightOper);
				valRightOper = "d179 " + valRightOper;
				codeItems.push_back(valRightOper);
				return decHexConv(val + 6);
			}
		}
		else if (strCom == "ADDI") {
			if (leftOper.at(0) == '#' && rightOper.at(0) != '$') {
				valOper = convDec2Hex(leftOper.substr(1, leftOper.size() - 1));
				fillHexNum(&valOper, 2);
				valOper = "0640 " + valOper;
				codeItems.push_back(valOper);
				return decHexConv(val + 4);
			}
			else {
				valOper = convDec2Hex(leftOper.substr(1, leftOper.size() - 1));
				fillHexNum(&valOper, 2);
				valRightOper = rightOper.substr(1, rightOper.size() - 1);
				fillHexNum(&valRightOper, 4);
				spaceHexNum(&valRightOper);
				valOper = "0679 " + valOper + " " + valRightOper;
				codeItems.push_back(valOper);
				return decHexConv(val + 8);
			}
		}
		else if (strCom == "SUB") {
			if (leftOper.at(0) == '#')
			{
				valLeftOper = leftOper.substr(1, leftOper.size() - 1);
				fillHexNum(&valLeftOper, 4);
				spaceHexNum(&valLeftOper);
				valLeftOper = "9079 " + valLeftOper;
				codeItems.push_back(valLeftOper);
				return decHexConv(val + 6);
			}
			else
			{
				valRightOper = rightOper.substr(1, rightOper.size() - 1);
				fillHexNum(&valRightOper, 4);
				spaceHexNum(&valRightOper);
				valRightOper = "9179 " + valRightOper;
				codeItems.push_back(valRightOper);
				return decHexConv(val + 6);
			}
		}
		else if (strCom == "SUBI") {
			if (leftOper.at(0) == '#' && rightOper.at(0) != '$')
			{
				valOper = convDec2Hex(leftOper.substr(1, leftOper.size() - 1));
				fillHexNum(&valOper, 2);
				valOper = "0440 " + valOper;
				codeItems.push_back(valOper);
				return decHexConv(val + 4);
			}
			else
			{
				valOper = convDec2Hex(leftOper.substr(1, leftOper.size() - 1));
				fillHexNum(&valOper, 2);
				valRightOper = rightOper.substr(1, rightOper.size() - 1);
				fillHexNum(&valRightOper, 4);
				spaceHexNum(&valRightOper);
				valOper = "0479 " + valOper + " " + valRightOper;
				codeItems.push_back(valOper);
				return decHexConv(val + 8);
			}
		}
		else if (strCom == "MOVE") {
			if (leftOper.at(0) == '#' && rightOper.at(0) == '$')
			{
				valOper = convDec2Hex(leftOper.substr(1, leftOper.size() - 1));
				fillHexNum(&valOper, 2);
				valRightOper = rightOper.substr(1, rightOper.size() - 1);
				fillHexNum(&valRightOper, 4);
				spaceHexNum(&valRightOper);
				valOper = "33fc " + valOper + " " + valRightOper;
				codeItems.push_back(valOper);
				return decHexConv(val + 8);
			}
			else if (leftOper.at(0) == '#' && rightOper.at(0) != '$')
			{
				valOper = convDec2Hex(leftOper.substr(1, leftOper.size() - 1));
				fillHexNum(&valOper, 2);
				valOper = "303c " + valOper;
				codeItems.push_back(valOper);
				return decHexConv(val + 4);
			}			
			else if (leftOper.at(0) == '$') 	{
				valLeftOper = leftOper.substr(1, leftOper.size() - 1);
				fillHexNum(&valLeftOper, 4);
				spaceHexNum(&valLeftOper);
				valLeftOper = "3039 " + valLeftOper;
				codeItems.push_back(valLeftOper);
				return decHexConv(val + 6);
			}
			else {
				valRightOper = rightOper.substr(1, rightOper.size() - 1);
				fillHexNum(&valRightOper, 4);
				spaceHexNum(&valRightOper);
				valRightOper = "33c0 " + valRightOper;
				codeItems.push_back(valRightOper);
				return decHexConv(val + 6);
			}
		}
		else if (strCom == "TRAP") {
			if (leftOper == "#0")
			{
				codeItems.push_back("4e40");
				return decHexConv(val + 2);
			}
			else if (leftOper == "#1")
			{
				codeItems.push_back("4e41");
				return decHexConv(val + 2);
			}
			else if (leftOper == "#2")
			{
				codeItems.push_back("4e42");
				return decHexConv(val + 2);
			}
		}
		else if (strCom == "ORG") {
			return leftOper.substr(1, leftOper.size() - 1);
		}
		else if (strCom == "END") {
			return curLoc;
		}
	}

private:
	string comment, instruction;
	string rightOper, leftOper;
	string lineName;
};

int main() {

	ifstream infile;
	ofstream outfile;
	infile.open("dataFile.txt");
	outfile.open("outFile.txt");

	passAssem machLine;

	vector<string> codeItems, instrucTable;
	string memAddress = "0", newLine, symbol;
	int symNum, comNum;
	bool instruc = false;

	while (!infile.eof()) {
		
		getline(infile, newLine);
		symNum = 1, comNum = 5;
	}	

	return 0;
}