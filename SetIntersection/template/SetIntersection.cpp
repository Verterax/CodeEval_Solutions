// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 30
// Set Intersection

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

void SetIntersection(string line)
{
	//Code goes here.
	vector<string> tokens = GetTokens(line, ';');
	vector<string> list0 = GetTokens(tokens[0], ',');
	vector<string> list1 = GetTokens(tokens[1], ',');
	tokens.clear();
	int list0Len, list1Len, i;
	int intersectsAt = -1;
	bool found = false;

	for (int round = 0; round < 2; ++round)
	{
		i = 0;
		int list0Len = list0.size();
		int list1Len = list1.size();

		for (i = 0; i < list0Len; ++i)
		{
			if (list0[i] == list1[0])
			{
				intersectsAt = i;
				tokens.push_back(list0[i]);
				i = 1;

				while (i < list1Len && (i + intersectsAt) < list0Len)
				{
					if (list0[intersectsAt + i] == list1[i])
						tokens.push_back(list1[i]);
					i++;
				}
				found = true;
				break;
			}
		}

		if (round == 0)
		{
			swap(list0, list1);
		}
	}

	list0Len = tokens.size();
	for (i = 0; i < list0Len; ++i)
		cout << ((i != list0Len - 1) ? tokens[i] + ',' : tokens[i]);
	cout << endl;
	
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
		SetIntersection(lines[i]);
	}

	return 0;
}

#pragma endregion