// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 28
// String Search

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

bool Contains(const char* searchStr, int searchLen, const char* subStr, int subLen )
{
	//Scan main string.
	bool contains = false;
	int escapes = 0;

	for (int i = 0; i < searchLen - subLen + 1; ++i)
	{
		for (int j = 0; j < subLen; ++j)
		{
			if (subStr[j] == '\\') //Ignore escape chars.
			{
				continue;
			}
			else if (subStr[j] == '*') // Wildcard case.
			{
				if (j == 0 || subStr[j - 1] != '\\') // Is not escaped.
				{
					contains = Contains(&searchStr[i + j], searchLen - i - 1, &subStr[j + 1], subLen - j - 1);
					if (contains)
						return true;
				}
				else if (j != 0) // Was escaped
				{
					if (searchStr[i - 1 + j] == subStr[j])
						escapes++;
					else
						break;
				}
			}
			else
				if (searchStr[i + j- escapes] != subStr[j])
					break; // Mismatch.

			if (j == subLen - 1)
				return true;
		}
	}

	return false;
}

bool Contains(string line)
{
	vector<string> tokens = GetTokens(line);
	//cout <<  "(" <<line<<")" << endl;
	return Contains(tokens[0].c_str(), tokens[0].size(), tokens[1].c_str(), tokens[1].size());

	
}

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }
	vector<string> lines = GetLines(argv[1]);
	int lineCount = lines.size();
	if (lineCount == 0) { cout << "No lines\n"; return 0; }
	
	for (int i = 0; i < lineCount; i++)
		cout << ((Contains(lines[i])) ? "true" : "false") << endl;

	return 0;
}

#pragma endregion