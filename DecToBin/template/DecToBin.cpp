// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 27
// DecToBin

#include <iostream>
#include <fstream>
#include <stack>
#include <string>
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
			if (line.size() != 0)
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

void DecToBin(string line)
{
	int num = atoi(line.c_str());
	if (num == 0)
	{
		cout << 0 << endl;
		return;
	}

	stack<int> binStack;
	int count = 0;
	int i = 1;
	

	while (i <= num)
	{
		//cout << ((num & i) != 0) ? 1 : 0;
		binStack.push(((num & i) != 0) ? 1 : 0);
		i = i << 1;
		++count;
	}
	
	for (int i = 0; i < count; ++i)
	{
		cout << binStack.top();
		binStack.pop();
	}
	cout << endl;

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
		DecToBin(lines[i]);
	}

	return 0;
}

#pragma endregion