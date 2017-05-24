#include <iostream>
#include <map>
#include <string>
#include <stack>
#include <fstream>
#include <iomanip>

using namespace std;

const int BIN_BASE = 2;
const int BIN_SIZE = 8;
const int BCD_BASE = 10;
const int BCD_SIZE = 3;
const int MAX_VAL = 256;
const int HEX_BASE = 16;
const int HEX_SIZE = 2;

void dec2Bin(int num, int arr[BIN_SIZE]);
void printBin(int arr[BIN_SIZE], ofstream& out);
void dec2Hex(int num, char arr[HEX_SIZE]);
char hexLibr(int num);
void printHex(char arr[HEX_SIZE], ofstream& out);
void dec2BCD(int num, string arr[BCD_SIZE]);
void convBCD(int num, int& count, string arr[BCD_SIZE]);
void printBCD(string arr[BCD_SIZE], ofstream& out);

int main() {

	ofstream out;
	out.open("outfile.txt");

	int arrBin[BIN_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	char arrHex[HEX_SIZE] = { '0', '0' };
	string arrBCD[BCD_SIZE] = { "0000", "0000", "0000" };

	out << "Decimal\t\tBinary\t\t\tHexadecimal"
		<< "\tBCD";
	for (int i = 0; i < MAX_VAL; i++) {
		out << endl;
		out << i << "\t\t";
		dec2Bin(i, arrBin);
		printBin(arrBin, out);

		out << "\t\t";
		dec2Hex(i, arrHex);
		printHex(arrHex, out);

		out << "\t\t";
		dec2BCD(i, arrBCD);
		printBCD(arrBCD, out);



	}
	return 0;
}

void dec2Bin(int num, int arr[BIN_SIZE]) {

	int mod, value = BIN_SIZE - 1;

	while (num != 0) {

		mod = num % BIN_BASE;
		num = num / BIN_BASE;
		arr[value--] = mod;
	}
}

void printBin(int arr[BIN_SIZE], ofstream& out) {

	for (int i = 0; i < BIN_SIZE; i++) {
		out << arr[i];
	}
}

void dec2Hex(int num, char arr[HEX_SIZE]) {

	int mod, value = HEX_SIZE - 1;

	char res;

	while (num != 0) {

		mod = num % HEX_BASE;
		if (mod > 9) {
			res = hexLibr(mod);
		}
		else {
			res = static_cast<char>(mod + '0');
		}
		arr[value--] = res;
		num = num / HEX_BASE;
	}
}

char hexLibr(int num) {

	switch (num) {
	case 10: return 'A';
	case 11: return 'B';
	case 12: return 'C';
	case 13: return 'D';
	case 14: return 'E';
	case 15: return 'F';
	}
}

void printHex(char arr[HEX_SIZE], ofstream& out) {

	for (int i = 0; i < HEX_SIZE; i++) {
		out << arr[i];
	}
}

void dec2BCD(int num, string arr[BCD_SIZE]) {

	int mod, res, count = 0;

	stack<int> val;

	while (num != 0) {

		mod = num % BCD_BASE;
		val.push(mod);
		num = num / BCD_BASE;
	}

	while (!val.empty()) {

		res = val.top();
		convBCD(res, count, arr);
		val.pop();
	}
}

void convBCD(int num, int& count, string arr[BCD_SIZE]) {

	map<int, string> m{ { 0, "0000" },{ 1, "0001" },{ 2, "0010" },{ 3, "0011" },{ 4, "0100" },
	{ 5, "0101" },{ 6, "0110" },{ 7, "0111" },{ 8, "1000" },{ 9, "1001" } };

	arr[count++] = m[num];

}

void printBCD(string arr[BCD_SIZE], ofstream& out) {

	for (int i = 0; i < BCD_SIZE; i++) {
		out << arr[i] << " ";
	}
}