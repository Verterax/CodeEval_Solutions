// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 46
// Prime Numbers

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

bool IsPrime(int number)
{
	if (number % 3 == 0)
		return false;
	else
		for (int i = 5; i * i <= number; i += 6)
			if (number % i == 0 || number % (i + 2) == 0)
				return false;

	return true;
}

void PrimeNumbers(string line)
{
	//Code goes here.
	int under = atoi(line.c_str());
	bool first = true;
	int num = 3;
	int lastNum = 2;

	if (under > 5)
		cout << "2,3,";

	if (under <= 4)
	{
		if (under == 4)
			cout << "2,3";
		else if (under == 3)
			cout << "2";
		cout << endl;
		return;
	}

	while (num < under)
	{
		if (IsPrime(num))
		{
			if (!first)
				cout << lastNum << ',';
			else
				first = false;

			lastNum = num;
		}

		num += 2;
	}

	cout << lastNum << endl;

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
		PrimeNumbers(lines[i]);
	}

	return 0;
}

#pragma endregion