// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 196
// Swap Numbers

#include <iostream>
#include <fstream> 
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void TemplateFunction(string line)
{
	string token;
	stringstream stream(line);
	bool first = true;
	while (std::getline(stream, token, ' '))
	{
		if (!first)
			cout << ' ';
		else
			first = false;

		char temp = token[0];
		token[0] = token[token.size() - 1];
		token[token.size() - 1] = temp;

		cout << token;
	}

	cout << endl;
}


int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	string line;
	ifstream file(argv[1]);

	if (file.is_open())
	{
		while (getline(file, line))
			TemplateFunction(line);
	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();


	return 0;
}
