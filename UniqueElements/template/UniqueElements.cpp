// By Christopher Caldwell
// chris@codehadouken.com
// Challenge N
// Name

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
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

vector<string> GetTokens(string line)
{
	vector<string> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, ','))
	{
		tokens.push_back(token);
	}

	return tokens;
}

void UniqueElems(string line)
{
	//Code goes here.
	vector<string> tokens = GetTokens(line);
	queue<int> elems;
	int num = 0;
	int count = tokens.size();
	
	for (int i = 0; i < count; ++i)
	{
		num = atoi(tokens[i].c_str());

		if (elems.size() > 0)
		{
			if (elems.back() != num)
				elems.emplace(num);
		}
		else
		{
			elems.emplace(num);
		}
		
	}

	count = elems.size();

	for (int i = 0; i < count; ++i)
	{
		cout << elems.front();
		elems.pop();
		if (i != count - 1) cout << ',';
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
		UniqueElems(lines[i]);
	}

	return 0;
}

#pragma endregion