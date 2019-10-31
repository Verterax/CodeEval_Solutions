// By Christopher Caldwell
// chris@codehadouken.com
// Challenge N
// Challenge Name

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
#include <algorithm> //Sort
#include <iomanip> //printf
//#include <ctype.h> //tolower, toUpper
using namespace std;

#pragma region Defaults

//Parses numeric tokens out of a string
//using the specified char as the delimiter.
//Returns a vector of ints
vector<double> GetDoubles(string line, char delim)
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


//Template function set to run on each
//line read from the text file.
void TemplateFunction(string line)
{
	//Code goes here.
	vector<double> tokens = GetDoubles(line, ' ');
	sort(tokens.begin(), tokens.end());

	for (int i = 0; i < tokens.size(); i++)
	{
		printf("%5.3f", tokens[i]);
		if (i != tokens.size() - 1) cout << ' ';
	}

	cout << endl;
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

#pragma endregion