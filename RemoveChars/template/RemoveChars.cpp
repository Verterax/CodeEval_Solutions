// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 13
// Remove Characters

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

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
	char remChars[]{','};
	while (std::getline(stream, token, ','))
	{
		tokens.push_back(token);
	}

	return tokens;
}


int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }
	string fileName = argv[1];

	string line;
	vector<string> lines = GetLines(fileName);
	int lineCount = lines.size();
	if (lineCount == 0) { cout << "No lines\n"; return 0; }
	char aux[1]{' '};

	for (int i = 0; i < lineCount; i++)
	{
		vector<string> tokens = GetTokens(lines[i]);
		RemChars(tokens[1], aux, 1);
		RemChars(tokens[0], tokens[1].c_str(), tokens[1].size());
		cout << tokens[0] << endl;
	}

	return 0;
}