// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 106
// Roman Numerals

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#pragma region Defaults


bool ReplaceStr(string& str, const string& findOld, const string& replaceNew) {
	size_t start_pos = str.find(findOld);
	if (start_pos == string::npos)
		return false;
	str.replace(start_pos, findOld.length(), replaceNew);
	return true;
}



int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	string line;
	ifstream file(argv[1]);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			const char THOUSAND = 'M';
			const char FIVEHUNDRED = 'D';
			const char HUNDRED = 'C';
			const char FIFTY = 'L';
			const char TEN = 'X';
			const char FIVE = 'V';
			const char ONE = 'I';

			int ones = atoi(line.c_str());

			int thousands = ones / 1000;
			ones -= thousands * 1000;
			int fiveHundreds = ones / 500;
			ones -= fiveHundreds * 500;
			int hundreds = ones / 100;
			ones -= hundreds * 100;
			int fifties = ones / 50;
			ones -= fifties * 50;
			int tens = ones / 10;
			ones -= tens * 10;
			int fives = ones / 5;
			ones -= fives * 5;

			stringstream ss;

			for (int i = 0; i < thousands; i++) ss << THOUSAND;
			for (int i = 0; i < fiveHundreds; i++) ss << FIVEHUNDRED;
			for (int i = 0; i < hundreds; i++) ss << HUNDRED;
			for (int i = 0; i < fifties; i++) ss << FIFTY;
			for (int i = 0; i < tens; i++) ss << TEN;
			for (int i = 0; i < fives; i++) ss << FIVE;
			for (int i = 0; i < ones; i++) ss << ONE;

			string output = ss.str();

			ReplaceStr(output, "DCCCC", "CM");	// 900
			ReplaceStr(output, "CCCC", "CD");	// 400
			ReplaceStr(output, "LXXXX", "XC");	// 90
			ReplaceStr(output, "XXXX", "XL");	// 40
			ReplaceStr(output, "VIIII", "IX");	// 9
			ReplaceStr(output, "IIII", "IV");	// 4

			cout << output << endl;
		}
	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();


	return 0;
}


#pragma endregion