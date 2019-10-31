// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 22
// Fibonacci Series

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

class Fibb
{
	int nums;
	vector<long> fibList;

private:
	void PopulateToN(int n)
	{
		++n;
		for (int i = nums; i < n; ++i)
			fibList.push_back(fibList[i - 1] + fibList[i - 2]);
		nums = n;
	}

	void Init(int n)
	{
		fibList.push_back(0);
		fibList.push_back(1);
		nums = 2;
		PopulateToN(n);
	}

public:
	Fibb(int n)
	{
		Init(n);
	}

	long GetFibN(int n)
	{
		if (n <= nums)
			return fibList[n];
		else
		{
			PopulateToN(n);
			return fibList[n];
		}
	}

};

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }
	vector<string> lines = GetLines(argv[1]);
	int lineCount = lines.size();
	if (lineCount == 0) { cout << "No lines\n"; return 0; }
	Fibb fib(20);

	//cout << fib.GetFibN(19) << endl;

	for (int i = 0; i < lineCount; ++i)
	{
		//Evaluate lines.
		cout << fib.GetFibN(atol(lines[i].c_str())) << endl;
	}

	return 0;
}

#pragma endregion