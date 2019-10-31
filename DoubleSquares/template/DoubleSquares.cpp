// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 33
// Double Squares

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
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

int SquaresForDiff(int x)
{
	if (x == 0) return 1;
	if (x == 1) return 1;

	int bigSquare = (int)sqrt(x);
	int littleSquare = 0;
	int bigSquareEvaluated = bigSquare * bigSquare;	
	int littleSquareEvaluated = littleSquare * littleSquare;
	int result = 0;

	int doubleSquareCount = 0;

	while (bigSquare > littleSquare)
	{
		result = bigSquareEvaluated + littleSquareEvaluated;

		if (result > x)
		{
			bigSquare--;
			bigSquareEvaluated = bigSquare * bigSquare;
		}
		else if (result < x)
		{
			littleSquare++;
			littleSquareEvaluated = littleSquare * littleSquare;
		}
		else
		{
			//cout << bigSquare << "^2 + " << littleSquare << "^2" << endl;
			doubleSquareCount++;
			littleSquare++;
			bigSquare--;	

			littleSquareEvaluated = littleSquare * littleSquare;
			bigSquareEvaluated = bigSquare * bigSquare;

		}
	}

	return doubleSquareCount;

}

void DoubleSquares(string line)
{
	//Code goes here.
	int x = atoi(line.c_str());
	int ways = SquaresForDiff(x);

	cout << ways << endl;
}

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }
	vector<string> lines = GetLines(argv[1]);
	int lineCount = lines.size();
	if (lineCount == 0) { cout << "No lines\n"; return 0; }
	int nLines = atoi(lines[0].c_str());

	for (int i = 1; i < lineCount; ++i)
	{
		//Evaluate lines.
		DoubleSquares(lines[i]);
	}

	return 0;
}

#pragma endregion