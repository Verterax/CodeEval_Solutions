// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 8
// Reverse Words

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

vector<string> GetLines(string fileName);
vector<string> GetTokens(string line);
string ReverseWords(string line);

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
		if (lines[i].size() == 0) continue;
		cout << ReverseWords(lines[i]) << endl;
	}

	return 0;
}

string ReverseWords(string line)
{
	//Code goes here.
	vector<string> tokens = GetTokens(line);
	string output;

	while (!tokens.empty())
	{
		output.append(tokens.back());
		tokens.pop_back();
		if (!tokens.empty()) output.append(" ");
	}

	return output;
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