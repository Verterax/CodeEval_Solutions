// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 43
// Jolly Jumpers

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <unordered_map>
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

vector<int> GetTokens(string line, char delim)
{
	vector<int> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, delim))
	{
		tokens.push_back(atoi(token.c_str()));
	}

	return tokens;
}

void JollyJumper(string line)
{
	//Code goes here.
	vector<int> tokens = GetTokens(line, ' ');
	unordered_map<int, bool> map;
	int expected = 0;
	int actual = 0;
	int len = tokens[0];
	int value = 0;

	for (int i = 1; i < len; ++i)
	{		
		value = tokens[i] - tokens[i + 1];

		if (value == 0)
		{
			cout << "Not jolly" << endl;
			return;
		}

		expected += i;	
		actual += abs(value);

		if (map.find(value) == map.end())
		{
			map.emplace(value, false);
		}
		else
		{
			cout << "Not jolly" << endl;
			return;
		}
	}

	if (expected == actual)
		cout << "Jolly";
	else
		cout << "Not jolly";
	
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
		JollyJumper(lines[i]);
	}

	return 0;
}

#pragma endregion