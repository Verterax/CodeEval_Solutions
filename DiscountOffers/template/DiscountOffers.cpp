// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 48
// Discount Offers

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>

#define INF 1000000
using namespace std;

vector<string> GetLines(string fileName);
vector<string> GetTokens(string line, char delim);

double GetSS(string person, string product);
int GetLetterCount(string str);
bool IsVowel(char c);
int GetVowelCount(string str);
int GetConsonantCount(string str);
int SharedFactors(int a, int b);

vector<string> GetLines(string fileName)
{
	string line;
	vector<string> lines;
	ifstream file(fileName);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			if (line.size() > 0)
				lines.push_back(line);
		}
	}
	else
	{
		std::cout << "Unable to open file.\n";
	}
	file.close();

	return lines;
}
vector<string> GetTokens(string line, char delim)
{
	vector<string> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, delim))
	{
		tokens.push_back(token);
	}

	return tokens;
}

class PeopleProductMatrix
{
public:
	PeopleProductMatrix(){}
	PeopleProductMatrix(string peopleStr, string productsStr)
	{
		Init(peopleStr, productsStr);
	}

	void PrintMatrix()
	{
		PrintMatrix(matrix);
	}
	double GetResult()
	{
		return GetMaxSum();
	}

private:
	vector<string> people;
	vector<string> products;
	vector<vector<double>> matrix;
	vector<vector<double>> tempMatrix;
	vector<vector<int>> maskMatrix;	
	vector<vector<int>> path;
	vector<bool> rowCover;
	vector<bool> colCover;
	int pathRowZero, pathColZero;
	int nRows;
	int nCols;
	bool printDebug = false;

	bool isRotated;
	double maxSS;

	void Init(string peopleStr, string productsStr)
	{
		people = GetTokens(peopleStr, ',');
		products = GetTokens(productsStr, ',');
		isRotated = people.size() > products.size();
		double ss, minSS = INF;
		maxSS = 0;

		if (isRotated) //Swap people and product axes
		{
			vector<string> temp = people;
			people = products;
			products = temp;
		}

		//Set row col sizes
		nRows = people.size();
		nCols = products.size();
		int size = (nRows > nCols) ? nRows : nCols;

		//Set cover sizes.
		rowCover.resize(nRows);
		colCover.resize(nCols);


		for (int row = 0; row < people.size(); ++row)
		{
			vector<double> personsProducts;
			for (int col = 0; col < products.size(); ++col)
			{
				if (!isRotated)
					ss = GetSS(people[row], products[col]);
				else
					ss = GetSS(products[col], people[row]);

				if (ss > maxSS) maxSS = ss;
				personsProducts.push_back(ss);
			}
			//for (int i = personsProducts.size(); i < size; ++i)
			//	personsProducts.push_back(0);
			matrix.push_back(personsProducts);
		}
		//for (int i = people.size(); i < size; ++i)
		//{
		//	vector<double> dummy(size);
		//	matrix.push_back(dummy);
		//}

		if (printDebug)
		{
			cout << "Primary Matrix" << endl;
			if (isRotated) cout << "The table is rotated." << endl;
			PrintMatrix(matrix);
		}

		InitTempMatrix();

		if (printDebug)
		{
			cout << "Temp Matrix" << endl;
			PrintMatrix(tempMatrix);
		}

		InitMaskMatrix();
		InitPathTracker();
		
	}
	void InitTempMatrix()
	{
		for (int row = 0; row < nRows; ++row)
		{
			vector<double> newRow(nCols);
			for (int col = 0; col < nCols; ++col)
				newRow[col] = maxSS - matrix[row][col];
			tempMatrix.push_back(newRow);
		}
	}
	void InitMaskMatrix()
	{
		for (int row = 0; row < nRows; ++row)
		{
			vector<int> maskRow(nCols);
			for (int col = 0; col < nCols; ++col)
				maskRow[col] = 0;
			maskMatrix.push_back(maskRow);
		}
	}
	void InitPathTracker()
	{
		int size = nRows + nCols + 1;
		for (int i = 0; i < size; ++i)
		{
			vector<int> row(2);
			path.push_back(row);
		}

	}
	void PrintMatrix(const vector<vector<double>> &printMatrix)
	{
		for (int row = 0; row < nRows; ++row)
		{
			for (int col = 0; col < nCols; ++col)
			{
				cout << setprecision(4) << setw(6) << printMatrix[row][col];
			}
			cout << endl;
		}
		cout << endl;
	}
	void PrintMaskMatrix()
	{
		for (int row = 0; row < nRows; ++row)
		{
			for (int col = 0; col < nCols; ++col)
			{
				cout << setw(3) << maskMatrix[row][col];
			}
			cout << endl;
		}
		cout << endl;
	}
	double GetMaxSum()
	{
		bool done = false;
		int step = 1;

		//PrintMatrix(tempMatrix);
		//PrintMaskMatrix();

		while (!done)
		{
			switch (step)
			{
			case 1:
				StepOne(step);
				break;
			case 2:
				StepTwo(step);
				break;
			case 3:
				StepThree(step);
				break;
			case 4:
				StepFour(step);
				break;
			case 5:
				StepFive(step);
				break;
			case 6:
				StepSix(step);
				break;
			case 7:
				done = true;
				break;
			}
		}

		//PrintMatrix(matrix);
		//PrintMaskMatrix();
		return SumAssignments();
	}
	double SumAssignments()
	{
		double sum = 0;

		for (int row = 0; row < nRows; ++row)
			for (int col = 0; col < nCols; ++col)
				if (maskMatrix[row][col] == 1)
					sum += matrix[row][col];

		return sum;
	}
	void StepOne(int &step)
	{
		double min;
		for (int row = 0; row < nRows; ++row)
		{
			min = tempMatrix[row][0]; //Start first position as min.
			for (int col = 0; col < nCols; ++col)
				if (tempMatrix[row][col] < min)
					min = tempMatrix[row][col];

			for (int col = 0; col < nCols; ++col)
				tempMatrix[row][col] -= min;

		}
		step = 2;
	}
	void StepTwo(int &step)
	{
		for (int row = 0; row < nRows; ++row)
			for (int col = 0; col < nCols; ++col)
			{
				if (tempMatrix[row][col] == 0 && rowCover[row] == 0 && colCover[col] == 0)
				{
					maskMatrix[row][col] = 1;
					rowCover[row] = 1;
					colCover[col] = 1;
				}
			}

		for (int row = 0; row < nRows; ++row)
			rowCover[row] = 0;

		for (int col = 0; col < nCols; ++col)
			colCover[col] = 0;

		step = 3; //Goto step 3 after starring zeros.

	}
	void StepThree(int &step)
	{
		int colCount = 0;

		//Get column covers.
		for (int row = 0; row < nRows; ++row)
			for (int col = 0; col < nCols; ++col)
				if (maskMatrix[row][col] == 1)
					colCover[col] = 1;

		//Count column covers
		for (int col = 0; col < nCols; ++col)
			if (colCover[col] == 1)
				colCount++;

		if (colCount >= nCols || colCount >= nRows)
			step = 7;
		else
			step = 4;

	}
	void StepFour(int &step)
	{
		int row = -1;
		int col = -1;
		bool done = false;

		while (!done)
		{
			FindZero(row, col);
			if (row == -1)
			{
				step = 6;
				done = true;
			}
			else
			{
				maskMatrix[row][col] = 2; //Prime uncovered zero.
				if (StarInRow(row))
				{
					FindStarInRow(row, col);
					rowCover[row] = 1;
					colCover[col] = 0;
				}
				else
				{
					step = 5;
					pathRowZero = row;
					pathColZero = col;
					done = true;
				}
			}
		}

	}
	void StepFive(int &step)
	{
		int row = -1;
		int col = -1;
		bool done = false;
		int pathCount = 1;
		path[pathCount - 1][0] = pathRowZero;
		path[pathCount - 1][1] = pathColZero;

		while (!done)
		{
			FindStarInCol(path[pathCount - 1][1], row);
			if (row > -1)
			{
				pathCount++;
				path[pathCount - 1][0] = row;
				path[pathCount - 1][1] = path[pathCount - 2][1];
			}
			else
				done = true;

			if (!done)
			{
				FindPrimeInRow(path[pathCount - 1][0], col);
				pathCount++;
				path[pathCount - 1][0] = path[pathCount - 2][0];
				path[pathCount - 1][1] = col;
			}
		}
		AugmentPath(pathCount);
		ClearCovers();
		RemovePrimes();
		step = 3;


	}
	void StepSix(int &step)
	{
		double min = INF;
		FindMin(min);

		for (int row = 0; row < nRows; ++row)
			for (int col = 0; col < nCols; ++col)
			{
				if (rowCover[row] == 1)
					tempMatrix[row][col] += min;

				if (colCover[col] == 0)
					tempMatrix[row][col] -= min;
			}

		step = 4;
	}

	//Helper Functions
	void FindZero(int &row, int &col)
	{
		bool done = false;
		int c, r = 0;
		col = -1;
		row = -1;
		
		while (!done)
		{
			c = 0;
			while (true)
			{
				if (tempMatrix[r][c] == 0 && rowCover[r] == 0 && colCover[c] == 0)
				{
					done = true;
					row = r;
					col = c;
				}
				c++;
				if (c >= nCols || done)
					break;
			}
			r++;
			if (r >= nRows)
				done = true;
		}
	}
	bool StarInRow(int row)
	{
		bool found = false;
		for (int col = 0; col < nCols; ++col)
			if (maskMatrix[row][col] == 1)
				found = true;
		return found;
	}
	void FindStarInRow(int row, int &c)
	{
		c = -1;
		for (int col = 0; col < nCols; ++col)
			if (maskMatrix[row][col] == 1)
				c = col;
	}
	void FindStarInCol(int col, int &r)
	{
		r = -1;
		for (int row = 0; row < nRows; ++row)
			if (maskMatrix[row][col] == 1)
				r = row;
	}
	void FindPrimeInRow(int row, int &c)
	{
		for (int col = 0; col < nCols; ++col)
			if (maskMatrix[row][col] == 2)
				c = col;
	}
	void AugmentPath(int pathCount)
	{
		for (int p = 0; p < pathCount; p++)
			if (maskMatrix[path[p][0]][path[p][1]] == 1)
				maskMatrix[path[p][0]][path[p][1]] = 0;
			else
				maskMatrix[path[p][0]][path[p][1]] = 1;
	}
	void ClearCovers()
	{
		for (int row = 0; row < nRows; ++row)
			rowCover[row] = 0;
		for (int col = 0; col < nCols; ++col)
			colCover[col] = 0;
	}
	void RemovePrimes()
	{
		for (int row = 0; row < nRows; ++row)
			for (int col = 0; col < nCols; ++col)
				if (maskMatrix[row][col] == 2)
					maskMatrix[row][col] = 0;
	}
	void FindMin(double &min)
	{
		for (int row = 0; row < nRows; ++row)
			for (int col = 0; col < nCols; ++col)
				if (rowCover[row] == 0 && colCover[col] == 0)
					if (min > tempMatrix[row][col])
						min = tempMatrix[row][col];
	}

	int GetLetterCount(string str)
	{
		int count = 0;
		for (int i = 0; i < str.size(); ++i)
			if (isalpha(str[i]))
			{
				++count;
			}

		return count;

	}
	bool IsVowel(char c)
	{
		if (c < 'a')
			c += 32;
		if (c == 'a')
			return true;
		else if (c == 'e')
			return true;
		else if (c == 'i')
			return true;
		else if (c == 'o')
			return true;
		else if (c == 'u')
			return true;
		else if (c == 'y')
			return true;
		else
			return false;
	}
	int GetVowelCount(string str)
	{
		int count = 0;
		for (int i = 0; i < str.size(); ++i)
		{
			if (IsVowel(str[i]))
			{
				count++;
			}
		}

		return count;
	}
	int GetConsonantCount(string str)
	{
		int count = 0;
		for (int i = 0; i < str.size(); ++i)
			if (isalpha(str[i]) && !IsVowel(str[i]))
			{
				++count;
			}

		return count;
	}
	int SharedFactors(int a, int b)
	{
		int max = (a > b) ? a : b;
		if (a % 2 == 0 && b % 2 == 0)
			return 2;

		for (int i = 3; i <= max; i += 2)
			if (a % i == 0 && b % i == 0)
				return i;

		return 1;
	}
	double GetSS(string person, string product)
	{
		double ss = 0.0;

		int lettersInProduct = GetLetterCount(product);
		int lettersInPerson = GetLetterCount(person);

		if (lettersInProduct % 2 == 0) // Even letters in
		{
			ss = (double)GetVowelCount(person);
			ss *= 1.5;
		}
		else
		{
			ss = (double)GetConsonantCount(person);
		}

		if (SharedFactors(lettersInPerson, lettersInProduct) != 1)
		{
			ss *= 1.5;
		}

		return ss;
	}

};

int main(int argc, char* argv[])
{
	if (argc == 1) { std::cout << "No file\n" << endl; return 0; }
	vector<string> lines = GetLines(argv[1]);
	int lineCount = lines.size();
	if (lineCount == 0) { std::cout << "No lines\n"; return 0; }

	for (int i = 0; i < lineCount; i++)
	{
		//Evaluate lines.
		vector<string> tokens = GetTokens(lines[i], ';');
		if (tokens.size() != 2 || tokens[0].size() < 2 || tokens[1].size() < 2)
		{
			cout << "0.00" << endl;
			continue;
		}

		PeopleProductMatrix matrix(tokens[0], tokens[1]);
		cout << fixed << setprecision(2) << matrix.GetResult() << endl;
	}


	return 0;
}
