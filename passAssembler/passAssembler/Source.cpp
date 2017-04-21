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

	string compute; //FIXME

private:
	string comment, instruction;
	string rightOper, leftOper;
	string lineName;
};


int main() {

	return 0;
}