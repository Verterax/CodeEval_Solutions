// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 87
// Query Board

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#pragma region Defaults

//Parses tokens out of a string
//Using a specified char as the delimiter.
vector<string> GetTokens(const string& line, char delim)
{
	vector<string> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, delim))
	{
		if (!token.empty())
			tokens.push_back(token);
	}

	return tokens;
}

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	string line;
	ifstream file(argv[1]);

	int board[256][256] = { 0 };

	if (file.is_open())
	{
		while (getline(file, line))
		{
			vector<string> tokens = GetTokens(line, ' ');

			if (tokens.size() == 3) // Set row col
			{
				if (tokens[0] == "SetRow")
				{
					int i = atoi(tokens[1].c_str());
					int x = atoi(tokens[2].c_str());

					for (int j = 0; j < 256; j++)
						board[i][j] = x;

				}
				else // Set Col
				{
					int j = atoi(tokens[1].c_str());
					int x = atoi(tokens[2].c_str());

					for (int i = 0; i < 256; i++)
						board[i][j] = x;
				}
			}
			else //Query row col
			{
				int sum = 0;
				if (tokens[0] == "QueryRow")
				{
					int i = atoi(tokens[1].c_str());
					for (int j = 0; j < 256; j++)
						sum += board[i][j];
				}
				else //Query Col
				{
					int j = atoi(tokens[1].c_str());
					for (int i = 0; i < 256; i++)
						sum += board[i][j];
				}

				cout << sum << endl;
			}
		}
	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();


	return 0;
}

#pragma endregion