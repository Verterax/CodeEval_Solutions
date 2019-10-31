// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 163
// Big Digits

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#pragma region Defaults

void PrintDigit(vector<string>& digits, int d, int lineN)
{
	for (int i = d * 5; i < d * 5 + 5; i++)
		cout << digits[lineN][i];
}


//Template function set to run on each
//line read from the text file.
void TemplateFunction(vector<string>& digits, string& line)
{
	for (int l = 0; l < 6; l++)
	{
		for (unsigned int i = 0; i < line.size(); i++)
		{
			if (isdigit(line[i]))
				PrintDigit(digits, (line[i] - 48), l);
		}
		cout << endl;
	}

}


int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	string line;
	ifstream file(argv[1]);
	vector<string> digits;
	digits.push_back("-**----*--***--***---*---****--**--****--**---**--");
	digits.push_back("*--*--**-----*----*-*--*-*----*-------*-*--*-*--*-");
	digits.push_back("*--*---*---**---**--****-***--***----*---**---***-");
	digits.push_back("*--*---*--*-------*----*----*-*--*--*---*--*----*-");
	digits.push_back("-**---***-****-***-----*-***---**---*----**---**--");
	digits.push_back("--------------------------------------------------");


	if (file.is_open())
	{
		while (getline(file, line))
		{
			TemplateFunction(digits, line);
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