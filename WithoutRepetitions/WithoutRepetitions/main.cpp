// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 173
// Without Repititions

#include <iostream>
#include <fstream> //fileStream
#include <string>
using namespace std;


int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	string line;
	ifstream file(argv[1]);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			string::iterator iter = line.begin();

			for (; iter < line.end() - 1; iter++)
			{
				if (*(iter + 1) == *iter)
				{
					line.erase(iter);

					if (iter != line.begin())
						iter--;
				}

			}

			cout << line << endl;
		}
	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();


	return 0;
}

//
////Console Input Main
//int main()
//{
//	cout << "Enter input, and press enter." << endl;
//	cout << "Type 'X' to exit." << endl;
//	string line;
//	int enterCount = 0;
//
//		while (getline(cin, line))
//		{
//			if (line.empty()) enterCount++;
//			if (line == "X" || line == "x" || enterCount > 1)
//				return 0;
//
//			TemplateFunction(line);
//		}
//
//	return 0;
//}

//
//////Alternate Main Function for challenges which reads
//////All lines from the text file before proceeding.
//int main(int argc, char* argv[])
//{
//	if (argc == 1) { cout << "No file\n" << endl; return 0; }
//
//	//Reads text-file lines into vector of strings.
//	vector<string> lines = GetLines(argv[1]); 
//
//	int lineCount = lines.size();
//	if (lineCount == 0) { cout << "No lines\n"; return 0; }
//
//	for (int i = 0; i < lineCount; i++)
//	{
//		//Evaluate lines.
//		TemplateFunction(lines[i]);
//	}
//
//	return 0;
//}
//

#pragma endregion