// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 217
// One Zeros, Two Zeros

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	string line;
	ifstream file(argv[1]);
	string token;

	int zeros = 0;
	int maxRange = 0;
	int total = 0;

	if (file.is_open())
	{
		while (getline(file, line))
		{
			stringstream stream(line);
			std::getline(stream, token, ' ');
			zeros = atoi(token.c_str());
			std::getline(stream, token, ' ');
			maxRange = atoi(token.c_str());
			total = 0;

			for (int i = 1; i <= maxRange; i++)
			{
				int zCount = 0;
				int n = i;
				for (int j = 1; j < i; j *= 2)
				{
					if (n % 2 == 0)
						zCount++;

					n /= 2;
				}

				if (zCount == zeros)
					total++;
			}

			cout << total << endl;
		}
	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();


	return 0;
}