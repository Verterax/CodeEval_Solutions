// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 7
// Prefix Expressions

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include<math.h>
using namespace std;



#pragma region File Helper
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

#pragma endregion

bool IsNum(const string str)
{
	return (str[0] >= '0' && str[0] <= '9');
}

bool IsOp(const string str)
{
	return (str[0] == '+' || str[0] == '*' || str[0] == '/');
}

void PrefixExpression(string line)
{
	vector<string> tokens = GetTokens(line);
	int len = tokens.size();
	stack<double> nums;
	double x, y;
	char op;

	for (int i = len - 1; i >= 0; --i)
	{
		if (IsNum(tokens[i]))
			nums.push(atoi(tokens[i].c_str()));
		else
		{
			op = tokens[i][0];			
			x = nums.top(); nums.pop();
			y = nums.top(); nums.pop();
			

			switch (op)
			{
			case '+':
				nums.push((x + y));
				break;
			case '*':
				nums.push((x * y));
				break;
			case '/':
				nums.push((x / y));
				break;
			case '-':
				nums.push((x-y));
				break;
			default:
				throw "Unknown operator: " + op;
			}

		}
	}

	cout << nums.top() << endl;
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
		PrefixExpression(lines[i]);
	}

	return 0;
}





