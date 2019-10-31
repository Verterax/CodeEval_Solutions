// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 42
// Ugly Numbers

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
using namespace std;

#pragma region Ugly Num Class

// Legend
// ) == nothing
// + == Plus
// - == Minus

#pragma endregion

bool IsUgly(int i)
{
	return (i % 2 == 0 || i % 3 == 0 || i % 5 == 0 || i % 7 == 0);
}
void Iterate(string& expression, const int expLen)
{
		expression[1] += 2;
		for (int i = 1; i < expLen; i += 2)
		{
			if (expression[i] == '/')
			{
				expression[i] = ')';
				if (i + 2 < expLen)
				{
					expression[i + 2] += 2;
				}
				else
				{
					break;
				}
			}
		}
	
}

void UglyNums(string& line)
{
	int numLen = line.size();
	int expLen = numLen + numLen - 1;
	stringstream ss;

	bool isNum = true;
	char c = ' ';
	char op = ' ';
	int sum = 0;
	int i = 0;
	int j = 0;
	int value = 0;
	int digit = 1;


	for (i = numLen - 1; i >= 0; --i)
	{
		ss << line[i];
		if (i != 0) ss << ')';
	}
	string expression = ss.str();
	int maxIterations = (int)pow(3,numLen - 1);
	int uglyCount = 0;

	for (int i = 0; i < maxIterations; ++i)
	{
		isNum = true;
		sum = 0;
		value = 0;
		digit = 1;
		j = 0;

		while (j < expLen)
		{
			c = expression[j];
			if (isNum)
			{	// Reached first real operator + or -
				sum += (c - '0') * digit;
				digit *= 10;
			}
			else
			{
				if (c != ')')
				{
					op = c;
					++j;
					isNum = true;
					break;
				}
			}

			++j;
			isNum = !isNum;
		}

		digit = 1; //1's place.
		for (; j < expLen; ++j)
		{
			c = expression[j];
			if (isNum)
			{
				value += (c - '0') * digit;
				digit *= 10;
			}
			else // Is Operator
			{
				if (c != ')') //Encountered the next operator. (End of num)
				{
					if (op == '+') //Perform evaluation with previous op.
						sum += value;
					else
						sum -= value;

					op = c;
					value = 0;
					digit = 1;
				}
			}

			isNum = !isNum;
		}

		//Perform final operation.
		if (op == '+')
			sum += value;
		else
			sum -= value;

		if (IsUgly(abs(sum))) ++uglyCount;
		Iterate(expression, expLen);
	}

	cout << uglyCount << endl;
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
			UglyNums(line);
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