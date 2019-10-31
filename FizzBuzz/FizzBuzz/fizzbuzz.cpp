// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 1
// FizzBuzz

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

void Say(int x, int y, int input)
{
	if (input % x == 0 && input % y == 0)
		cout << "FB";
	else if (input % x == 0)
		cout << "F";
	else if (input % y == 0)
		cout << "B";
	else
		cout << input;
}

void FizzBuzz(int x, int y, int n)
{
	//Code goes here.
	//cout << line << endl;
	n++;
	for (int i = 1; i < n; i++)
	{
		Say(x, y, i);
		if (i != n - 1) cout << " ";
	}

}

vector<int> GetInts(const string& line, char delim)
{
	vector<int> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, delim))
	{
		if (!token.empty())
			tokens.push_back(atoi(token.c_str()));
	}

	return tokens;
}

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	string line;
	ifstream file(argv[1]);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			vector<int> t = GetInts(line, ' ');

			FizzBuzz(t[0], t[1], t[2]);
			cout << endl;
		}
	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();


	return 0;
}

