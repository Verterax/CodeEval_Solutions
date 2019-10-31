// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 161
// Game of Life

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <vector>

void PrintGrid(std::vector<std::string>& grid)
{
	for (unsigned int i = 0; i < grid.size(); i++)
	{
		for (unsigned int j = 0; j < grid[i].size(); j++)
		{
			std::cout << grid[i][j];
		}
		std::cout << std::endl;
	}
}

const char ALIVE = '*';
const char DEAD = '.';

int GetNeighborCount(std::vector<std::string>& grid, unsigned int x, unsigned int y)
{
	int count = 0;
	bool up = y > 0;
	bool down = y < grid.size()-1;
	bool left = x > 0;
	bool right = x < grid[0].size()-1;
	
	if (up)
	{
		if (left) if (grid[y-1][x - 1] == ALIVE) count++;
		if (right) if (grid[y-1][x + 1] == ALIVE) count++;
		if (grid[y-1][x] == ALIVE) count++;
	}

	if (down)
	{
		if (left) if (grid[y + 1][x - 1] == ALIVE) count++;
		if (right) if (grid[y + 1][x + 1] == ALIVE) count++;
		if (grid[y + 1][x] == ALIVE) count++;
	}

	if (left)
	{
		if (grid[y][x - 1] == ALIVE) count++;
	}

	if (right)
	{
		if (grid[y][x + 1] == ALIVE) count++;
	}

	return count;
}

void CalcIteration(std::vector<std::string>& grid, char temp[100][100], bool copyFirst)
{
	int count = 0;
	for (unsigned int i = 0; i < grid.size(); i++)
	{
		for (unsigned int j = 0; j < grid[0].size(); j++)
		{
			count = GetNeighborCount(grid, j, i);

			if (copyFirst)
				temp[i][j] = grid[i][j];

			if (grid[i][j] == DEAD)
			{
				if (count == 3)
					temp[i][j] = ALIVE;
			}
			else
			{
				if (count < 2 || count > 3)
					temp[i][j] = DEAD;
			}
		}
	}

	for (unsigned int i = 0; i < grid.size(); i++)
	{
		for (unsigned int j = 0; j < grid[0].size(); j++)
		{
			grid[i][j] = temp[i][j];
		}
	}
}


int main(int argc, char* argv[])
{
	if (argc == 1) { std::cout << "No file\n" << std::endl; return 0; }

	std::string line;
	std::ifstream file(argv[1]);
	std::vector<std::string> grid;

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			grid.push_back(line);
		}

		char temp[100][100];
		
		//PrintGrid(grid); 
		//cout << "Before\n" << endl;
		bool copyFirst = true;

		for (int i = 0; i < 10; i++)
		{
			CalcIteration(grid, temp, copyFirst);
			//PrintGrid(grid);
			//cout << "#" << (i + 1) << endl;
			copyFirst = false;
		}
		//cout << "Done" << endl;
		PrintGrid(grid); 

	}
	else
	{
		std::cout << "Unable to open file.\n";
	}
	file.close();


	return 0;
}

