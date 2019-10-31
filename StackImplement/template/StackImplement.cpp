// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 9
// Stack Implementation

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
using namespace std;

vector<string> GetLines(string fileName);
vector<string> GetTokens(string line);
void EveryOther(string line);

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
		EveryOther(lines[i]);
	}

	return 0;
}

void EveryOther(string line)
{
	//Code goes here.
	vector<string> tokens = GetTokens(line);
	stack<int> intStack;
	int tokenCount = tokens.size();

	for (int i = 0; i < tokenCount; i++)
		intStack.push(atoi(tokens[i].c_str()));

	bool doPrint = true;
	while (!intStack.empty())
	{
		if (doPrint)
		{
			cout << intStack.top();
			intStack.pop();

			if (!intStack.empty())
				cout << " ";				
		}
		else
		{
			intStack.pop();
		}
		
		doPrint = !doPrint;
	}

	cout << endl;
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