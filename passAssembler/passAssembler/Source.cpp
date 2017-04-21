#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

const int MAX_COUNT = 8;
const string INSTRUCTION[MAX_COUNT] = { "ADD", "ADDI", "SUB", "SUBI",
"MOVE", "ORG", "TRAP", "END" };
const string HEX_VALS = "0123456789ABCDEF";

string convDec2Hex(string);
string decHexConv(int);
int convHex2Dec(string);
void spaceHexNum(string*);
void fillHexNum(string*, int);

class passAssem {
public:
	passAssem() {
		comment = " ", instruction = " ";
		rightOper = " ", leftOper = " ";
		//lineName = " ";
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
		string pos; //FIXME

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

	return 0;
}