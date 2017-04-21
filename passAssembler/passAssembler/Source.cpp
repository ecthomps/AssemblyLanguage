#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

const int MAX_COUNT = 8;
const string INSTRUCTION[MAX_COUNT] = { "ADD", "ADDI", "SUB", "SUBI",
"MOVE", "TRAP", "END" };
const string HEX_VALS = "0123456789ABCDEF";

string convDec2Hex(string);
string convDec2Hex(int);
int convHex2Dec(string);
void spaceHexNum(string*);
void fillHexNum(string*, int);

class passAssem {
public:
	passAssem() {
		comment = " ", instruction = " ";
		rightOper = " ", leftOper = " ";
		lineName = " ";
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

	string compute(string curLoc, vector<string>& codeItems,
		           vector<string>& symTable) {
		string strAddress, strCom = instruction, valOper;
		
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

			}
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