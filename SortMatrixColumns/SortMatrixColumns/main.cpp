// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 200
// Sort Matrix Columns

#include <iostream>
#include <fstream> 
#include <string>
#include <sstream>
#include <vector>

using namespace std;

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

//Parses numeric tokens out of a string
//using the specified char as the delimiter.
//Returns a vector of ints
vector<int> GetInts(const string& line, char delim)
{
	vector<int> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, delim))
	{
		if (!token.empty())
			tokens.push_back(atoi(token.c_str()));
	}

	return tokens;
}

void PrintMatrix(vector<vector<int>>& matrix)
{
	int size = matrix.size();
	for (int i = 0; i < size; i++)
	{
		cout << "| ";
		for (int j = 0; j < size; j++)
		{			
			cout << matrix[j][i] << '\t';
		}
		cout << "|" << endl;
	}
}

void SortMatrix(vector<vector<int>>& matrix)
{
	int size = matrix.size();
	bool isSorted = false;
	int tier = 0;
	while (!isSorted)
	{
		isSorted = true;
		for (int i = 0; i < size - 1; i++)
		{		
			while (matrix[i][tier] == matrix[i + 1][tier]) tier++;

			if (matrix[i][tier] > matrix[i+1][tier])
			{
				vector<int> temp = matrix[i];
				matrix[i] = matrix[i + 1];
				matrix[i + 1] = temp;
				isSorted = false;
			}
			tier = 0;
		}
	}
}

void MatrixToString(vector<vector<int>>& matrix)
{
	int size = matrix.size();
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << matrix[j][i];
			if (j != size - 1) cout << ' ';
		}
		if (i != size - 1) cout << " | ";
	}
}


//Template function set to run on each
//line read from the text file.
void TemplateFunction(string& line)
{
	//Code goes here.
	vector<string> tokens = GetTokens(line, '|');
	int size = tokens.size();
	vector<vector<int>> matrix(size);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			matrix[j].push_back(0);

	for (int i = 0; i < size; i++)
	{
		vector<int> row = GetInts(tokens[i], ' ');
		for (int j = 0; j < size; j++)
		{
			matrix[j][i] = row[j];
		}
	}

	SortMatrix(matrix);
	MatrixToString(matrix);
	//PrintMatrix(matrix);

}


int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	string line;
	ifstream file(argv[1]);
	bool problem = true;

	if (file.is_open())
	{
		while (getline(file, line))
		{
			TemplateFunction(line);
			cout << endl;
		}
	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();


	return 0;
}

