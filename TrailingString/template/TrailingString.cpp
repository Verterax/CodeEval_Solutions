// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 32
// Trailing String

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
		std::cout << "Unable to open file.\n";
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

void RemChars(string& str, const char chars[], int charLen)
{
	int i;
	int strLen = str.size();
	string::iterator iter = str.begin();
	bool didErase = false;
	while (iter != str.end())
	{
		didErase = false;
		for (i = 0; i < charLen; i++)
			if ((*iter) == chars[i])
			{
				str.erase(iter);
				didErase = true;
				break;
			}
		if (!didErase) iter++;
	}
}

void TemplateFunction(string line)
{
	//Code goes here.
	vector<string> tokens = GetTokens(line);
	int len0 = tokens[0].size();
	int len1 = tokens[1].size();
	int j = 0;

	for (int i = (len0 - len1); i < len0; ++i)
	{
		if (tokens[0][i] != tokens[1][j])
		{
			std::cout << 0 << endl;
			return;
		}
		j++;
	}
	
	std::cout << 1 << endl;
}

int main(int argc, char* argv[])
{
	if (argc == 1) { std::cout << "No file\n" << endl; return 0; }
	vector<string> lines = GetLines(argv[1]);
	int lineCount = lines.size();
	if (lineCount == 0) { std::cout << "No lines\n"; return 0; }

	for (int i = 0; i < lineCount; i++)
	{
		//Evaluate lines.
		TemplateFunction(lines[i]);
	}

	return 0;
}

#pragma endregion