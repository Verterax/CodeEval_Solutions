// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 149
// Juggling With Zeros

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

//Parses tokens out of a string
//Using a specified char as the delimiter.
vector<string> GetTokens(const string& line, char delim)
{
	vector<string> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, delim))
	{
		if (!token.empty())
			tokens.push_back(token);
	}

	return tokens;
}



//Template function set to run on each
//line read from the text file.
void TemplateFunction(string& line)
{
	stringstream ss;
	vector<string> number = GetTokens(line, ' ');
	bool ones = false;

	for (unsigned int i = 0; i < number.size(); i++)
	{
		if (i % 2 == 0)
		{
			if (number[i].size() == 2)
				ones = true;
			else
				ones = false;
		}
		else
		{
			for (unsigned int j = 0; j < number[i].size(); j++)
			{
				if (ones) 
					ss << '1';
				else 
					ss << '0';
			}

		}
	}

	string str = ss.str();
	//cout << str << endl;
	long long sum = 0;

	//for (int i = str.size() - 1; i >= 0; i--)
	for (unsigned int i = 0; i < str.size(); i++)
	{
		if (str[i] != '0')
			sum += (int)(pow(2.0, (double)((str.size()-1)-i)));
	}

	cout << sum << endl;
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
			TemplateFunction(line);
		}
	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();


	return 0;
}
