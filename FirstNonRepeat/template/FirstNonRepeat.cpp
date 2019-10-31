// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 12
// First Non-Repeated Character

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

struct repeat_tracker
{
public:
	repeat_tracker(char c)
	{
		this->character = c;
		this->wasRepeated = false;
	}

	char character;
	bool wasRepeated;
};

#pragma region Gets

char GetFirstNonRepeatChar(string line)
{
	queue<char> charQueue;
	unordered_map<char, repeat_tracker> trackerMap;
	unordered_map<char, repeat_tracker>::iterator iter;	
	char currentChar;

	//Scan once.
	int charCount = line.size();
	for (int i = 0; i < charCount; i++)
	{
		currentChar = line[i];
		iter = trackerMap.find(currentChar);
		if (iter == trackerMap.end()) 
		{
			//Not repeated.
			repeat_tracker charTrack(currentChar);
			trackerMap.emplace(currentChar, charTrack); // Add to map.
			charQueue.push(currentChar); //Add to queue;
		}
		else 
			(*iter).second.wasRepeated = true; //Repeated.
	}
	
	charCount = charQueue.size();
	for (int i = 0; i < charCount; i++)
	{
		currentChar = charQueue.front();

		if ((*trackerMap.find(currentChar)).second.wasRepeated)			
			charQueue.pop(); //Repeated, next...
		else
			return currentChar; //Return first non-repeat.
	}

	return NULL;
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

vector<string> GetTokens(string line)
{
	vector<string> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, ' '))
	{
		tokens.push_back(token);
	}

	return tokens;
}

#pragma endregion

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }
	string fileName = argv[1];

	string line;
	vector<string> lines = GetLines(fileName);
	int lineCount = lines.size();
	if (lineCount == 0) { cout << "No lines\n"; return 0; }

	for (int i = 0; i < lineCount; i++)
	{
		//Evaluate lines.
		cout << GetFirstNonRepeatChar(lines[i]) << endl;
	}

	return 0;
}