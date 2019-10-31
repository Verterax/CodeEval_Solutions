// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 5
// Detecting Cycles

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

vector<string> GetLines(string fileName);
vector<int> GetNums(string line);
void PrintCycle(string line);

#pragma region Get

void PrintCycle(string line)
{
	vector<int> nums = GetNums(line);
	int numCount = nums.size();
	int num;
	unordered_map<int, bool> numMap;
	unordered_map<int, bool>::iterator found;
	stack<int> loop;
	int mu;

	for (int i = 0; i < numCount; i++)
	{
		num = nums[i];
		found = numMap.find(num);
		numMap.emplace(num, false);
		
		if (found != numMap.end()) //Found loop start.
		{
			mu = num;

			//trace back to find first instance.		
			for (int j = i-1; j >= 0; j--)
			{
				num = nums[j];
				loop.push(num);
				
				if (num == mu)
					break;
			}

			//We have our loop.
			int lamda = loop.size() -1;
			for (int i = 0; i < lamda; i++)
			{
				cout << loop.top() << ' ';
				loop.pop();
			}
			cout << loop.top() << endl;
			break;
		}
	}

}


vector<int> GetNums(string line)
{
	vector<int> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, ' '))
		tokens.push_back(atoi(token.c_str()));

	return tokens;
}

vector<string> GetLines(string fileName)
{
	string line;
	vector<string> lines;
	ifstream file(fileName);

	if (file.is_open())
		while (getline(file, line))
			lines.push_back(line);
	else
		cout << "Unable to open file.\n";

	file.close();
	return lines;
}

#pragma endregion

#pragma region Main

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }
	vector<string> lines = GetLines(argv[1]);
	int lineCount = lines.size();
	if (lineCount == 0) { cout << "No lines\n"; return 0; }

	for (int i = 0; i < lineCount; i++)
	{
		//Evaluate lines.
		PrintCycle(lines[i]);
	}

	return 0;
}

#pragma endregion