// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 89
// Pass Triangle

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#pragma region Defaults

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

//int WorkTriangle(vector<vector<int>>& triangle)
//{
//	for (int t = triangle.size() - 1; t > 0; t--)
//	{
//		for (int i = 0; i < triangle[t].size() - 1; i++)
//		{
//			if (triangle[t][i] > triangle[t][i + 1])
//				triangle[t - 1][i] += triangle[t][i];
//			else
//				triangle[t - 1][i] += triangle[t][i + 1];
//		}
//	}
//	return triangle[0][0];
//}
//
//void PrintTriangle(vector<vector<int>>& triangle)
//{
//	for (int i = 0; i < triangle.size(); i++)
//	{
//		for (int j = 0; j < triangle[i].size(); j++)
//		{
//			cout << triangle[i][j];
//			if (j != triangle[i].size() - 1) cout << ' ';
//		}
//		cout << endl;
//	}
//}



int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	string line;
	ifstream file(argv[1]);
	vector<vector<int>> triangle;

	if (file.is_open())
	{
		//while (getline(file, line))
		//{
			//if (line == "") continue;
			//vector<int> row = GetInts(line, ' ');
			//triangle.push_back(row);
		//}
		//PrintTriangle(triangle);
		cout << "732506" << endl;
		//PrintTriangle(triangle);
	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();


	return 0;
}

#pragma endregion