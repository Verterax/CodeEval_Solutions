// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 36
// Message Decoding

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
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
	while (std::getline(stream, token, ' '))
	{
		tokens.push_back(token);
	}

	return tokens;
}

void RemChars(string& str, const char chars[], int charLen)
{
	int i;
	int strLen = str.size();
	string::iterator iter = str.begin();
	bool didErase = false;
	while (iter != str.end())
	{
		didErase = false;
		for (i = 0; i < charLen; i++)
			if ((*iter) == chars[i])
			{
				str.erase(iter);
				didErase = true;
				break;
			}
		if (!didErase) iter++;
	}
}

void IncrementKey(string &key)
{
	int len = key.size();
	for (int i = len - 1; i >= 0; --i)
	{
		if (key[i] == '1')
		{
			key[i] = '0';
		}
		else
		{
			key[i] = '1'; // turn 0 into 1.
			break; //String incremented.
		}
	}

	//Check for all ones.
	bool allOnes = true;
	for (int i = 0; i < len; ++i)
	{
		if (key[i] != '1')
		{
			allOnes = false;
			break;
		}
	}

	//All ones, needs turnover to 0*len+1
	if (allOnes)
	{
		++len;
		key = "";
		for (int i = 0; i < len; ++i)
			key += '0';
	}
}

void DecodeMessage(string line)
{
	//Code goes here.
	unordered_map<string, char> decode;
	bool allOnes = true;
	char tempChar = ' ';
	int keyLen = 0;
	int lineSize = line.size();
	int phase = 0;
	int i = 0;
	string key = "0";

	while (i < lineSize)
	{
		//Phase 0, map chars to keys
		if (phase == 0)
		{
			if (line[i] == '1' || line[i] == '0') //Detect for end of header.
			{
				if (line[i + 1] == '1' || line[i + 1] == '0' &&
					line[i + 2] == '1' || line[i + 2] == '0')
				{
					phase = 1; //Goto phase 1 (Get Segment length)
				}
			}
			else //Emplace new key, value pair.
			{
				tempChar = line[i];
				
				if (tempChar != '\n')
				{
					decode.emplace(key, tempChar);
					//cout << key << endl;
					IncrementKey(key);
				}

				i++;
			}
		}

		//Phase 1, get segment (key) length
		if (phase == 1)
		{
			keyLen = 0;
			char wordLen[3]{line[i], line[i + 1], line[i + 2]};
			keyLen |= (wordLen[0] == '1') ? 4 : 0;
			keyLen |= (wordLen[1] == '1') ? 2 : 0;
			keyLen |= (wordLen[2] == '1') ? 1 : 0;
			i += 3; //Skip to sequence start.
			phase = 2; //Move to phase 2.

			if (keyLen == 0) //000 = length zero.
				break; //end of message.
		}

		//Phase 2, read each char in segment, and detect for end of segment.
		if (phase == 2)
		{
			allOnes = true;
			key = "";

			for (int j = 0; j < keyLen; ++j)
			{
				tempChar = line[i + j];

				if (tempChar == '\n')
				{
					--i;
					--j; //Ignore newlines
					continue;	
				}

				if (tempChar == '0')
					allOnes = false; //We can be sure this isn't an end sequence code.

				key += line[i + j]; // Add binary symbol to key.
			}

			//Increment i for current keylength.
			i += keyLen;

			if (allOnes)
			{
				phase = 1; // Return to phase 1 (get segment length)			
			}
			else
			{
				cout << decode[key]; //Print out decoded symbol.
			}
		}
	}

	cout << endl; //End of message.
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
		DecodeMessage(lines[i]);
	}

	return 0;
}

#pragma endregion