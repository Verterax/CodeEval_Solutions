// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 40
// Self Describing Numbers

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
		std::cout << "Unable to open file.\n";
	}
	file.close();

	return lines;
}

void SelfDescNums(string line)
{
	//Code goes here.
	int i,j, count;

	for (i = 0; i < line.size(); ++i)
	{
		count = 0;

		for (j = 0; j < line.size(); ++j)
		{
			if (line[j] - '0' == i)
			{
				++count;
			}
		}

		if (count != (line[i] - '0'))
		{
			std::cout << 0 << endl;
			return;
		}
	}


	std::cout << 1 << endl;
}

int main(int argc, char* argv[])
{
	if (argc == 1) { std::cout << "No file\n" << endl; return 0; }
	vector<string> lines = GetLines(argv[1]);
	int lineCount = lines.size();
	if (lineCount == 0) { std::cout << "No lines\n"; return 0; }

	for (int i = 0; i < lineCount; i++)
	{
		//Evaluate lines.
		SelfDescNums(lines[i]);
	}

	return 0;
}

#pragma endregion