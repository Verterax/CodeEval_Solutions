// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 131
// Split The Number

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
using namespace std;
using std::cout;
using std::endl;

#pragma region Defaults


//Parses tokens out of a string
//Using a specified char as the delimiter.
vector<string> GetTokens(const string& line, char delim)
{
	vector<string> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, delim))
	{
		if (!token.empty())
			tokens.push_back(token);
	}

	return tokens;
}


//Template function set to run on each
//line read from the text file.
void TemplateFunction(string& line)
{
	vector<string> tokens = GetTokens(line, ' ');
	stringstream n1, n2;
	bool foundOp = false;
	char op = ' ';

	for (unsigned int i = 0; i < tokens[1].size(); i++)
	{
		if (!foundOp)
			if (tokens[1][i] == '-' || tokens[1][i] == '+')
			{
				op = tokens[1][i];
				foundOp = true;
				continue;
			}

		if (!foundOp)
		{
			n1 << tokens[0][i];
		}
		else
		{
			n2 << tokens[0][i-1];
		}
	}

	int num1, num2;
	num1 = atoi(n1.str().c_str());
	num2 = atoi(n2.str().c_str());
	if (op == ' ')
		cout << num1;
	else if (op == '+')
		cout << (num1 + num2);
	else
		cout << (num1 - num2);

	cout << endl;
}


int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	string line;
	ifstream file(argv[1]);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			TemplateFunction(line);
		}
	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();


	return 0;
}

#pragma endregion