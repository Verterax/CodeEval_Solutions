// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 6
// Longest Common Subsequence

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
using namespace std;

#pragma region Get

string RemoveSpace(string str)
{
	stringstream ss;
	int len = str.size();
	for (int i = 0; i < len; ++i)
		if (str[i] != ' ') ss << str[i];
	return ss.str();
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
			if (line.size() >= 1)
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
	while (std::getline(stream, token, ';'))
		tokens.push_back(token);

	return tokens;
}

#pragma endregion

string LCS(string line)
{
	//Get tokens
	vector<string> tokens = GetTokens(line);
	string strX, strY;
	stringstream ss;
	stack<char> result;
	
	//Get and pad strings.
	ss << ' ' << tokens[0];
	strX = ss.str();
	ss.str(string());
	ss.clear();
	ss << ' ' << tokens[1];
	strY = ss.str();
	ss.str(string());
	ss.clear();

	//Get string lengths.
	int xLen = strX.size();
	int yLen = strY.size();
	int j, i;

	//Create table.
	int** rowCols = new int*[yLen];
	for (i = 0; i < yLen; ++i)
		rowCols[i] = new int[xLen];

	//Set top and left cells to 0.
	for (j = 0; j < yLen; ++j) //Init rows
		rowCols[j][0] = 0;
	for (i = 0; i < xLen; ++i) //Init columns
		rowCols[0][i] = 0;

	for (j = 1; j < yLen; ++j) //Rows
		for (i = 1; i < xLen; ++i) // Cols
			if (strY[j] == strX[i])
				rowCols[j][i] = rowCols[j - 1][i - 1] + 1;
			else
				rowCols[j][i] = (rowCols[j - 1][i] > rowCols[j][i - 1]) ? rowCols[j - 1][i] : rowCols[j][i - 1];

	i = xLen - 1;
	j = yLen - 1;

	//Up and right.
	while (j > 0 && i > 0)
	{
		if (rowCols[j - 1][i] == rowCols[j][i]) // Up in a col
			--j;
		else if (rowCols[j][i - 1] == rowCols[j][i]) // Left in a row
			--i;
		else
		{
			result.push(strX[i]);
			--i;
			--j;
		}
	}
	
	//Free up table.
	for (; i < yLen; ++i)
		delete rowCols[i];
	delete rowCols;

	//Output result.
	while (result.size() > 0)
	{
		ss << result.top();
		result.pop();
	}
	return ss.str();
}

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }
	vector<string> lines = GetLines(argv[1]);
	int lineCount = lines.size();
	if (lineCount == 0) { cout << "No lines\n"; return 0; }
	string result;
	
	for (int i = 0; i < lineCount; i++)
	{
		cout << LCS(lines[i]) << endl;
	}

	return 0;
}



