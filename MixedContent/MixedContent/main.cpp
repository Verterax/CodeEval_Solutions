// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 115
// Mixed Content

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
using namespace std;


//Parses tokens out of a string
//Using a specified char as the delimiter.
vector<string> GetTokens(string line, char delim)
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
void TemplateFunction(string line)
{
	//Code goes here.
	vector<string> tokens = GetTokens(line, ',');
	int numberCount = 0;
	int fruitCount = 0;
	

	for (int i = 0; i < tokens.size(); i++)
	{
		if (isdigit(tokens[i][0]))
		{
			numberCount++;
		}
	}
	fruitCount = tokens.size() - numberCount;

	bool printSeparator = (numberCount == 0 || fruitCount == 0 ? false : true);

	if (fruitCount > 0)
	{
		for (int i = 0; i < tokens.size(); i++)
		{
			if (!isdigit(tokens[i][0]))
			{
				cout << tokens[i];
				fruitCount--;
				if (fruitCount != 0) cout << ',';
			}
		}
	}

	if (printSeparator)
		cout << '|';

	if (numberCount > 0)
	{
		for (int i = 0; i < tokens.size(); i++)
		{
			if (isdigit(tokens[i][0]))
			{
				cout << tokens[i];
				numberCount--;
				if (numberCount != 0) cout << ',';
			}
		}
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