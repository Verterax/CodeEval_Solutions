// By Christopher Caldwell
// chris@codehadouken.com
// Challenge N
// Name

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


void TemplateFunction(string line)
{
	//Code goes here.
	int sum = 0;
	int len = line.size();
	for (int i = 0; i < len; ++i)
		sum += line[i] - 48;

	cout << sum << endl;
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
		TemplateFunction(lines[i]);
	}

	return 0;
}

#pragma endregion