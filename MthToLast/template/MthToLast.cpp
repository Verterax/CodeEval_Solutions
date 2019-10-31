// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 10
// Mth to last element

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

vector<string> GetLines(string fileName);
vector<string> GetTokens(string line);
void PrintMth(string line);

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }
	string fileName = argv[1];

	string line;
	vector<string> lines = GetLines(fileName);
	int lineCount = lines.size();
	if (lineCount == 0) { cout << "No lines\n"; return 0; }
	
	for (int i = 0; i < lineCount; i++)
	{
		//Evaluate lines.
		PrintMth(lines[i]);
	}

	return 0;
}

void PrintMth(string line)
{
	vector<string> tokens = GetTokens(line);
	int index = atoi(tokens.back().c_str());
	tokens.pop_back();
	int tokenCount = tokens.size();
	if (index > tokenCount) return;
	cout << tokens[tokenCount - index] << endl;
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
	while (std::getline(stream, token, ' '))
	{
		tokens.push_back(token);
	}

	return tokens;
}