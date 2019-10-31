// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 147
// Lettercase Percentage Ratio

#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
using namespace std;
void TemplateFunction(string line)
{
	double uppers = 0;
	double lowers = 0;

	for (int i = 0; i < line.size(); i++)
	{
		if (isupper(line[i]))
			uppers+=1.0;
		else
			lowers+=1.0;
	}

	printf("lowercase: %.2f uppercase: %.2f",
		(lowers / (uppers + lowers)) * 100,
		(uppers / (uppers + lowers)) * 100);

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
		cout << "Unable to open file.\n";
	file.close();
	return 0;
}
