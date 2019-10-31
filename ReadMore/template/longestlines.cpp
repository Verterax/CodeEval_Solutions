// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 2
// Longest Lines

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> GetLines(string fileName);
void LongLines(vector<string> lines);

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }
	vector<string> lines = GetLines(argv[1]);
	LongLines(lines);
	return 0;
}


bool pairCompare(const pair<int, string>& a, const pair<int, string>& b)
{
	return a.first > b.first;
}

void LongLines(vector<string> lines)
{
	int lineCount = lines.size();
	int printLines = atoi(lines[0].c_str());
	vector<pair<int, string>> pairs;

	for (int i = 1; i < lineCount; i++)
	{
		//Evaluate lines.
		pair<int, string> item(lines[i].size(), lines[i]);
		pairs.push_back(item);
	}

	sort(pairs.begin(), pairs.end(), pairCompare);
	printLines = (printLines <= lineCount) ? printLines : lineCount-1;
	for (int i = 0; i < printLines; i++)
	{
		cout << pairs[i].second << endl;
	}

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
