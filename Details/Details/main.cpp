// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 183
// Details

#include <iostream>
#include <fstream> //fileStream
#include <string>
//#include <vector>
//#include <sstream>
using namespace std;

//Parses tokens out of a string
//Using a specified char as the delimiter.
//vector<string> GetTokens(const string& line, char delim)
//{
//	vector<string> tokens;
//	string token;
//	stringstream stream(line);
//	while (std::getline(stream, token, delim))
//	{
//		if (!token.empty())
//			tokens.push_back(token);
//	}
//
//	return tokens;
//}

//void TemplateFunction(string& line)
//{

//}
//
//void PrintGrid(string& line)
//{
//	vector<string> t = GetTokens(line, ',');
//	
//	for (int i = 0; i < t.size(); i++)
//		cout << t[i] << endl;
//}

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	string line;
	ifstream file(argv[1]);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			//PrintGrid(line);
			//TemplateFunction(line);
			int min = line.size();
			int current = 0;
			for (unsigned int i = 0; i < line.size(); i++)
			{
				if (line[i] == 'X' && line[i + 1] == '.')
				{
					for (unsigned int j = i + 1; line[j] != 'Y'; j++)
						current++;
				}

				if (line[i] == ',' || i == line.size() - 1)
				{
					if (current < min)
						min = current;
					current = 0;
				}
			}

			cout << min << endl;
		}
	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();


	return 0;
}


