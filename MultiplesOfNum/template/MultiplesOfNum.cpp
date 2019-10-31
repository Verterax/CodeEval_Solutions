// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 18
// Multiples of a Number

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

int MultiplesOfNum(string line)
{
	vector<string> tokens = GetTokens(line);
	int x = atoi(tokens[0].c_str());
	int n = atoi(tokens[1].c_str());
	int base = n;

	while (!(n >= x))
		n += base;
	return n;
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
		cout << MultiplesOfNum(lines[i]) << endl;
	}

	return 0;
}

#pragma endregion