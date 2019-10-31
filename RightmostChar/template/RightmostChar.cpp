// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 31
// Rightmost Char

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#pragma region Defaults

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

vector<string> GetTokens(string line)
{
	vector<string> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, ','))
	{
		tokens.push_back(token);
	}

	return tokens;
}

void TemplateFunction(string line)
{
	//Code goes here.
	vector<string> tokens = GetTokens(line);
	int size = tokens[0].size();
	int rightMost = -1;
	char c = tokens[1][0];

	for (int i = 0; i < size; ++i)
		if (tokens[0][i] == c)
			rightMost = i;

	cout << rightMost << endl;
	
}

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }
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