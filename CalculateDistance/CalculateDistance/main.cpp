// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 99
// Calculate Distance

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
//#include <algorithm> //Sort
//#include <iomanip> //printf
//#include <ctype.h> //tolower, toUpper
using namespace std;

#pragma region Defaults

//Parses numeric tokens out of a string
//using the specified char as the delimiter.
//Returns a vector of ints
vector<double> GetFloats(string line, char delim)
{
	vector<double> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, delim))
	{
		tokens.push_back(atof(token.c_str()));
	}

	return tokens;
}


//Takes a string by reference and removes
//matching chars found in the chars[] array.
void RemChars(string& str, const char chars[], int charLen)
{
	string::iterator iter = str.begin();
	bool didErase = false;
	while (iter != str.end())
	{
		didErase = false;
		for (int i = 0; i < charLen; i++)
			if ((*iter) == chars[i])
			{
				str.erase(iter);
				didErase = true;
				break;
			}
		if (!didErase) iter++;
	}
}


//Template function set to run on each
//line read from the text file.
void TemplateFunction(string& line)
{
	//Code goes here.
	const char chars[] = {'(',')',','};
	RemChars(line, chars, line.size());
	vector<double> c = GetFloats(line, ' ');

	if (c.size() != 4)
		cout << "err";

	//printf("sqrt(%.0f - %.0f + %.0f - %.0f)", c[3], c[1], c[2], c[0]);

	int result = (int)sqrt
		((c[3] - c[1]) * (c[3] - c[1]) +
		 (c[2] - c[0]) * (c[2] - c[0])
		);
	cout << result << endl;
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
			//cout << line << endl;
			TemplateFunction(line);
			//cout << line << endl;
			//system("CLS");
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