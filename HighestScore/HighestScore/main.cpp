// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 208
// Find The Highest Score

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>

using namespace std;

#pragma region Defaults

//Reads a file, and returns the 
//contents as a vector of strings
vector<string> GetLines(string fileName)
{
	string line;
	vector<string> lines;
	ifstream file(fileName);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			lines.push_back(line);
		}
	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();

	return lines;
}

//Parses tokens out of a string
//Using a specified char as the delimiter.
vector<string> GetTokens(string line, char delim)
{
	vector<string> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, delim))
	{
		tokens.push_back(token);
	}

	return tokens;
}

//Parses numeric tokens out of a string
//using the specified char as the delimiter.
//Returns a vector of ints
vector<int> GetInts(string line, char delim)
{
	vector<int> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, delim))
	{
		if (token != "")
			tokens.push_back(atoi(token.c_str()));
	}

	return tokens;
}



//Template function set to run on each
//line read from the text file.
void TemplateFunction(string line)
{
	//Code goes here.
	vector<string> tokens = GetTokens(line, '|'); //Columns
	vector<vector<int>> table;

	for (int i = 0; i < tokens.size(); i++)
		table.push_back(GetInts(tokens[i], ' '));

	for (int r = 0; r < table[0].size(); r++)
	{
		int max = -1001;
		for (int c = 0; c < table.size(); c++)
		{
			if (table[c][r] > max)
			{
				max = table[c][r];
			}
		}

		cout << max;

		if (r != table[0].size() - 1)
			cout << ' ';
	}


	cout << endl;
}

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	//Reads text-file lines into vector of strings.
	vector<string> lines = GetLines(argv[1]);

	int lineCount = lines.size();
	if (lineCount == 0) { cout << "No lines\n"; return 0; }

	for (int i = 0; i < lineCount; i++)
	{
		//Evaluate lines.
		TemplateFunction(lines[i]);
	}

	return 0;
}

#pragma endregion