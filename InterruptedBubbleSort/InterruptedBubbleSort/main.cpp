// By Christopher Caldwell
// chris@codehadouken.com
// Challenge N158
// Interrupted Bubble Sort

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

void BubbleIteration(vector<int>& list)
{
	for (unsigned int i = 0; i < list.size()-3; i++)
	{
		if (list[i] > list[i + 1])
		{
			int temp = list[i];
			list[i] = list[i + 1];
			list[i + 1] = temp;
		}
	}
}


//Template function set to run on each
//line read from the text file.
void TemplateFunction(string& line)
{
	//Code goes here.
	vector<int> t = GetInts(line, ' ');

	int n = t[t.size() - 1];
	for (int i = 0; i < n; i++)
		BubbleIteration(t);

	for (unsigned int i = 0; i < t.size() - 2; i++)
	{
		cout << t[i];
		if (i != t.size() - 3) cout << ' ';
	}
	cout << endl;
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
			TemplateFunction(line);
		}
	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();


	return 0;
}

//
////Console Input Main
//int main()
//{
//	cout << "Enter input, and press enter." << endl;
//	cout << "Type 'X' to exit." << endl;
//	string line;
//	int enterCount = 0;
//
//		while (getline(cin, line))
//		{
//			if (line.empty()) enterCount++;
//			if (line == "X" || line == "x" || enterCount > 1)
//				return 0;
//
//			TemplateFunction(line);
//		}
//
//	return 0;
//}

//
//////Alternate Main Function for challenges which reads
//////All lines from the text file before proceeding.
//int main(int argc, char* argv[])
//{
//	if (argc == 1) { cout << "No file\n" << endl; return 0; }
//
//	//Reads text-file lines into vector of strings.
//	vector<string> lines = GetLines(argv[1]); 
//
//	int lineCount = lines.size();
//	if (lineCount == 0) { cout << "No lines\n"; return 0; }
//
//	for (int i = 0; i < lineCount; i++)
//	{
//		//Evaluate lines.
//		TemplateFunction(lines[i]);
//	}
//
//	return 0;
//}
//

#pragma endregion