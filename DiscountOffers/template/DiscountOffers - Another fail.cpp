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

#define printTable true
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

#pragma region Text Parsing
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
#pragma endregion

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
		return GetResult(GetAssignments());
	}

private:
	vector<vector<double>> matrix;
	vector<string> people;
	vector<string> products;
	double maxSS;
	int size;

	void Init(string peopleStr, string productsStr)
	{
		people = GetTokens(peopleStr, ',');
		products = GetTokens(productsStr, ',');
		size = (people.size() > products.size()) ? people.size() : products.size();

		double ss;
		maxSS = 0;

		for each (string person in people)
		{
			vector<double> personsProducts;
			for each (string product in products)
			{
				ss = GetSS(person, product);
				if (ss > maxSS) maxSS = ss;
				personsProducts.push_back(ss);
			}

			for (int i = personsProducts.size(); i < size; ++i)
				personsProducts.push_back(0);
			matrix.push_back(personsProducts);
		}
		for (int i = people.size(); i < size; ++i)
		{
			vector<double> dummy(size);
			matrix.push_back(dummy);
		}

		//Fill dummy rows with max value
		for (int row = people.size(); row < size; ++row)
			for (int col = 0; col < size; ++col)
				matrix[row][col] = 0;

		//Fill dummy cols with max value
		for (int col = products.size(); col < size; ++col)
			for (int row = 0; row < size; ++row)
				matrix[row][col] = maxSS;

		PrintMatrix(matrix);

	}

	vector<vector<double>> GetTempMatrix()
	{
		vector<vector<double>> tempMatrix;

		for each(vector<double> row in matrix)
		{
			vector<double> newRow;
			for each(double val in row)
			{
				newRow.push_back(abs(val - maxSS));
			}
			tempMatrix.push_back(newRow);
		}

		return tempMatrix;
	}
	void ReduceMatrix(vector<vector<double>> &tempMatrix)
	{
		double minSS = INF;

		//Subtract min from rows
		for (int row = 0; row < size; ++row)
		{
			minSS = INF;
			for (int col = 0; col < size; ++col)
			{
				if (tempMatrix[row][col] < minSS) minSS = tempMatrix[row][col];
			}

			if (minSS != 0)
				for (int col = 0; col < size; ++col)
				{
					tempMatrix[row][col] -= minSS;
				}
		}

		//Subtract min from cols
		for (int col = 0; col < size; ++col)
		{
			minSS = INF;
			for (int row = 0; row < size; ++row)
			{
				if (tempMatrix[row][col] < minSS) minSS = tempMatrix[row][col];
			}

			if (minSS != 0)
				for (int row = 0; row < size; ++row)
				{
					tempMatrix[row][col] -= minSS;
				}
		}
	}
	void PrintMatrix(const vector<vector<double>> &printMatrix)
	{
		for each(vector<double> row in printMatrix)
		{
			for each (double val in row)
			{
				cout << setprecision(4) << setw(5) << val;
			}
			cout << endl;
		}
		cout << endl;
	}
	double GetResult(vector<pair<int, int>> assignments)
	{
		double result = 0;
		for each(pair<int, int> assignment in assignments)
			result += matrix[assignment.first][assignment.second];
		return result;
	}
	void Crossout(vector<vector<double>> &tempMatrix, pair<int, int> assignment)
	{
		//Cross out zeros in row
		for (int col = 0; col < size; ++col)
			if (tempMatrix[assignment.first][col] == 0)
				tempMatrix[assignment.first][col] = -1;		

		//Cross out zeros in col
		for (int row = 0; row < size; ++row)
			if (tempMatrix[row][assignment.second] == 0)
				tempMatrix[row][assignment.second] = -1;

		tempMatrix[assignment.first][assignment.second] = -2;
	}
	void HungarianTransform(vector<vector<double>> &tempMatrix)
	{
		vector<double> U(size);
		vector<double> V(size);
		double current, maxSS, min = INF;

		//Get RowMins as U
		for (int row = 0; row < size; ++row)
		{
			min = INF;
			for (int col = 0; col < size; ++col)
				if (tempMatrix[row][col] < min) min = tempMatrix[row][col];

			U[row] = min; //Store row Min

			for (int col = 0; col < size; ++col)
				tempMatrix[row][col] -= U[row];
		}

		//Get ColMin as V
		for (int col = 0; col < size; ++col)
		{
			min = INF;
			for (int row = 0; row < size; ++row)
				if (tempMatrix[row][col] < min) min = tempMatrix[row][col];

			V[col] = min; //Store col min

			for (int row = 0; row < size; ++row)
				tempMatrix[row][col] -= V[col];
		}

	}
	vector<pair<int, int>> GetAssignments(vector<vector<double>> tempMatrix)
	{
		vector<pair<int, int>> assignments;
		bool didAssign = true;

		while (didAssign)
		{
			didAssign = false;

			//Assign rows.
			for (int row = 0; row < size; ++row)
			{
				int zeroCount = 0;
				int assignCol = -1;
				for (int col = 0; col < size; ++col)
				{
					if (tempMatrix[row][col] == 0)
					{
						zeroCount++;
						assignCol = col;
					}
				}

				if (zeroCount == 1)
				{
					pair<int, int> assignment(row, assignCol);
					assignments.push_back(assignment);
					didAssign = true;
					Crossout(tempMatrix, assignment);
				}
			}

			//Assign cols.
			for (int col = 0; col < size; ++col)
			{
				int zeroCount = 0;
				int assignRow = -1;
				for (int row = 0; row < size; ++row)
				{
					if (tempMatrix[row][col] == 0)
					{
						zeroCount++;
						assignRow = row;
					}
				}

				if (zeroCount == 1)
				{
					pair<int, int> assignment(assignRow, col);
					assignments.push_back(assignment);
					didAssign = true;
					Crossout(tempMatrix, assignment);
				}
			}
		}

		return assignments;
	}
	vector<pair<int, int>> GetAssignments()
	{
		//PrintMatrix(matrix);

		vector<vector<double>> tempMatrix = GetTempMatrix();
		//PrintMatrix(tempMatrix);

		ReduceMatrix(tempMatrix);
		//PrintMatrix(tempMatrix);
		
		vector<bool> coveredRows(size);
		vector<bool> coveredCols(size);
		int lineCount = 0;
		bool didHungarianTransform = false;

		PrintMatrix(tempMatrix);
		while (assignments.size() < size)
		{
			//Get covered rows.
			InitCoveredRowCols(tempMatrix, assignments, coveredRows, coveredCols);

			//Get line count.
			lineCount = GetLineCount(coveredRows, coveredCols);

			//Create more zeros.
			MakeMoreZeros(tempMatrix, coveredRows, coveredCols);
			PrintMatrix(tempMatrix);

			//Get possible assignments
			assignments = GetAssignments(tempMatrix);
		}


		return assignments;
	}
	void InitCoveredRowCols(
		const vector<vector<double>> tempMatrix,
		const vector<pair<int, int>> assignments,
		vector<bool> &coveredRows,
		vector<bool> &coveredCols)
	{
		vector<bool> rowTicks(size);
		vector<bool> colTicks(size);
		bool didTick = true;

		//Set cover markers to false.
		for (int i = 0; i < size; ++i)
		{
			coveredRows[i] = false;
			coveredCols[i] = false;
			rowTicks[i] = true;
		}

		//Untick Assigned rows. (leave only unassigned rows ticked)
		for (int i = 0; i < assignments.size(); ++i)
			rowTicks[assignments[i].first] = false;

		//PrintMatrix(tempMatrix);

		//Get tick info.
		while (didTick)
		{
			didTick = false;

			for (int row = 0; row < size; ++row)
				if (rowTicks[row]) //If a ticked row
					for (int col = 0; col < size; ++col)
						if (tempMatrix[row][col] == 0) //Has a zero
							if (!colTicks[col])
							{
								colTicks[col] = true; // Tick the corresponding column.
								didTick = true;
							}

			for (int col = 0; col < size; ++col)
				if (colTicks[col]) // If a ticked column
					for (int i = 0; i < assignments.size(); ++i)
						if (assignments[i].second == col) // Has an assignment
							if (!rowTicks[assignments[i].first])
							{
								rowTicks[assignments[i].first] = true; //Tick corresponding row
								didTick = true;
							}
		}

		//Cover unticked rows.
		for (int row = 0; row < size; ++row)
			if (!rowTicks[row])
			{
				coveredRows[row] = true;
			}

		//Cover ticked columns
		for (int col = 0; col < size; ++col)
			if (colTicks[col])
			{
				coveredCols[col] = true;
			}

	}

	void MakeMoreZeros(vector<vector<double>> &tempMatrix, vector<bool> coveredRows, vector<bool> coveredCols)
	{
		double min = INF;
			//Find theta.
		for (int row = 0; row < size; ++row)
			if (!coveredRows[row])
				for (int col = 0; col < size; ++col)
					if (!coveredCols[col])
						if (tempMatrix[row][col] < min)
							min = tempMatrix[row][col];

		//cout << "Min uncovered is: " << min << endl;

		//Add min to covered rows
		for (int row = 0; row < size; ++row)
			if (coveredRows[row])
				for (int col = 0; col < size; ++col)
					tempMatrix[row][col] += min;

		//Sub min from uncovered cols
		for (int col = 0; col < size; ++col)
			if (!coveredCols[col])
				for (int row = 0; row < size; ++row)
					tempMatrix[row][col] -= min;
		
	}
	int GetLineCount(vector<bool> coveredRows, vector<bool> coveredCols)
	{
		int count = 0;
		for (int i = 0; i < size; ++i)
		{
			if (coveredRows[i])count++;
			if (coveredCols[i])count++;
		}
		return count;
	}

#pragma region SS
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
#pragma endregion

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
		cout << matrix.GetResult() << endl;
	}


	return 0;
}
