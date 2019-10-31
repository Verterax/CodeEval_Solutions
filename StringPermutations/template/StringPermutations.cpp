// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 14
// String Permutations

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
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

int Factorial(int n)
{
	return (n == 1 || n == 0) ? 1 : Factorial(n - 1) * n;
}

void Promote(int*& indexArr, int len)
{
	int compareSmall = len - 1;
	int compareLarge = compareSmall - 1;

	while (true)
	{
		if (indexArr[compareLarge] < indexArr[compareSmall])
		{
			swap(indexArr[compareLarge], indexArr[compareSmall]);
			sort(&indexArr[compareLarge+1], &indexArr[len]);
			return;
		}
		
		if (compareLarge == 0 && compareSmall == 1)
			return; // Base case.
		else if (compareSmall == compareLarge + 1) //if compare small is next to compare large.
		{
			compareLarge--; // Move compare large left.
			compareSmall = len - 1; //Set compare small back to small digit.
		}
		else
			compareSmall--;				
	}
}

void PrintArr(int*& indexArr, int len)
{
	for (int i = 0; i < len; ++i)
		cout << indexArr[i];
}

void PrintSequence(string line, int*& indexArr, int len)
{
	for (int i = 0; i < len; ++i)
		cout << line[indexArr[i]];
}

void PrintPermutations(string line)
{
	//Code goes here.
	int i;
	int len = line.size();
	if (len == 1)
	{
		cout << line;
		return;
	}

	int permutations = Factorial(len);
	sort(line.begin(), line.end());
	int* indexArr = new int[permutations];

	for (i = 0; i < len; ++i)
		indexArr[i] = i;

	for (i = 0; i < permutations; ++i)
	{
		//PrintArr(indexArr, len);
		PrintSequence(line, indexArr, len);
		Promote(indexArr, len);
		if (i != permutations - 1) cout << ',';
	}

	delete indexArr;
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
		PrintPermutations(lines[i]);
		cout << endl;
	}

	return 0;
}

#pragma endregion