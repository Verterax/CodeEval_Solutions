// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 19
// Bit Positions

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
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
string BitPositions(string line)
{
	//Code goes here.
    vector<string> tokens = GetTokens(line);
	int n = atoi(tokens[0].c_str());
	return (((n & (1 << (atoi(tokens[1].c_str()) - 1))) != 0) == ((n & (1 << (atoi(tokens[2].c_str()) - 1))) != 0)) ? "true" : "false";
}

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }
	vector<string> lines = GetLines(argv[1]);
	int lineCount = lines.size();
	if (lineCount == 0) { cout << "No lines\n"; return 0; }

	for (int i = 0; i < lineCount; i++)
		cout << BitPositions(lines[i]) << endl;

	return 0;
}

#pragma endregion