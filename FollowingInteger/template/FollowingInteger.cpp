// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 44
// Following Integer

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

void Promote(string& str, int len)
{
	int compareSmall = len - 1;
	int compareLarge = compareSmall - 1;

	if (len == 1) return;

	while (true)
	{
		if (str[compareLarge] < str[compareSmall])
		{
			swap(str[compareLarge], str[compareSmall]);
			sort(str.begin() + (compareLarge + 1), str.begin() + len);
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

int GetValue(const string str)
{
	return atoi(str.c_str());
}

void PrintNext(string line)
{
	//Code goes here.
	int value;
	int original = atoi(line.c_str());
	int len = line.size();

	Promote(line, len);
	value = GetValue(line);

	if (value <= original)
	{
		sort(line.begin(), line.end());
		stringstream ss;
		ss << 0 << line;
		line = ss.str();
		
		for (int i = 1; i < len + 1; ++i)
		{
			if (line[i] != '0')
			{
				swap(line[0], line[i]);
				break;
			}
		}

		cout << line << endl;
	}
	else
	{
		cout << value << endl;
	}

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
		//cout << '.' << lines[i] << endl;
		PrintNext(lines[i]);
	}

	return 0;
}

#pragma endregion

