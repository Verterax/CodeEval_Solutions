// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 42
// Ugly Numbers

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
using namespace std;

#pragma region Ugly Num Class

// Legend
// ) == nothing
// + == Plus
// - == Minus
//enum Operator : char{ 
//	Blank = ')', 
//	Plus = '+',
//	Minus = '-',
//	Over = '/'
//};

bool* GetUglies()
{
	bool* uglies = new bool[210];

	for (int i = 0; i < 210; ++i)
		uglies[i] = (i % 2 == 0 || i % 3 == 0 || i % 5 == 0 || i % 7 == 0);

	return uglies;
}


class IterableExpression
{
private:
	bool doneIterating;
	int iterations;
	int numLen;
	int expLen;
	string expression;

	void Init(string number)
	{
		doneIterating = false;
		numLen = number.size();
		expLen = numLen + numLen - 1;
		iterations = 0;
		stringstream ss;

		for (int i = numLen-1; i >= 0; --i)
		{
			ss << number[i];
			if (i != 0) ss << ')';
		}
		expression = ss.str();
	}

	void Increment()
	{
		if (!doneIterating)
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
						doneIterating = true;
					}
				}
			}
			iterations++;
		}
	}

public:
	IterableExpression(){ Init("");};
	IterableExpression(string number){Init(number);}

	IterableExpression& operator++() {
		Increment();
		return *this;
	}

	//Get
	bool IsDone(){ return doneIterating; }
	int GetIterations(){ return iterations; }
	int GetNumLen() { return numLen; }
	int GetExpLen(){ return expLen; }
	int GetMaxIterations()
	{
		return (int)pow(3, GetNumLen() - 1);
	}
	string GetExpression()
	{
		stringstream ss;
		char c;
		for (int i = GetExpLen() - 1; i >= 0; --i)
		{
			c = expression[i];
			if (c != ')') ss << c;
		}
			
		return ss.str();
	}

	int Evaluate()
	{
		bool hasOp = false;
		bool hasVal = false;
		bool isNum = true;
		char c = ' ';
		char op = ' ';
		int sum = 0;
		int i = 0;
		int value = 0;
		int digit = 1; //*=10 to move digit over. Add to variable. char - '0' to get num from char.
		//Back an expression in.
		// multiply numbers 

		//Get initial sum (first number) in expression.
		while (i < expLen)
		{
			c = expression[i];
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
					++i;
					isNum = true;
					break;
				}
			}

			++i;
			isNum = !isNum;
		}

		digit = 1; //1's place.
		for (; i < expLen; ++i)
		{
			c = expression[i];
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

		return sum;
	}

	//Set

};

#pragma endregion

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

void UglyNums(string line, bool* uglies)
{
	//Code goes here.

	IterableExpression exp(line);
	int maxIterations = exp.GetMaxIterations();
	int uglyCount = 0;
	bool isUgly = false;
	int result = 0;

	for (int i = 0; i < maxIterations; ++i)
	{		
		cout << exp.GetExpression() << " = ";
		result = exp.Evaluate();
		cout << result;
		result = result % 210;
		isUgly = uglies[abs(result)];
		cout << ((isUgly) ? " Ugly " : "");
		if (isUgly) uglyCount++;

		cout << endl;
		exp++;
	}

	cout << "Max Iterations = " << maxIterations << endl;
	cout << "Actual = " << exp.GetIterations() << endl;
	cout << "Ugly nums = " << uglyCount << endl;

	//cout << exp.GetExpression() << endl << endl;
}

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }
	vector<string> lines = GetLines(argv[1]);
	int lineCount = lines.size();
	if (lineCount == 0) { cout << "No lines\n"; return 0; }

	//Precalc bool array of mod 210 nums as being ugly or not.
	bool* uglies = GetUglies();

	for (int i = 0; i < lineCount; i++)
	{
		//Evaluate lines.
		UglyNums(lines[i], uglies);
		system("cls");
	}

	delete uglies;

	return 0;
}

#pragma endregion