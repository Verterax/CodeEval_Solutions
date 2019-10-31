// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 235
// Simple Or Trump

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>

//Parses tokens out of a string
//Using a specified char as the delimiter.
std::vector<std::string> GetTokens(const std::string& line, char delim)
{
	std::vector<std::string> tokens;
	std::string token;
	std::stringstream stream(line);
	while (std::getline(stream, token, delim))
	{
		if (!token.empty())
			tokens.push_back(token);
	}

	return tokens;
}

char GetValue(std::string& card, char trumpSuit)
{
	char score = (card[card.size() - 1] == trumpSuit ? 99 : 0);
	char c1 = card[0];
	if (isdigit(c1))
	{
		if (c1 == '1')
			score += 10;
		else 
			score += c1 - 48;
	}
	else
	{
		if (c1 == 'J')
			score += 11;
		else if (c1 == 'Q')
			score += 12;
		else if (c1 == 'K')
			score += 13;
		else // Implied Ace
			score += 14;
	}

	return score;
}


//Template function set to run on each
//line read from the text file.
void TemplateFunction(std::string& line)
{
	//Code goes here.
	std::vector<std::string> tokens = GetTokens(line, ' ');
	char trumpSuit = tokens[3][0];
	char c1 = GetValue(tokens[0], trumpSuit);
	char c2 = GetValue(tokens[1], trumpSuit);

	//std::cout << line << "    =     ";
	
	if (c1 == c2)
		std::cout << tokens[0] << ' ' << tokens[1] << std::endl;
	else if (c1 > c2)
		std::cout << tokens[0] << std::endl;
	else
		std::cout << tokens[1] << std::endl;
}


int main(int argc, char* argv[])
{
	if (argc == 1) { std::cout << "No file\n" << std::endl; return 0; }

	std::string line;
	std::ifstream file(argv[1]);

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			TemplateFunction(line);
		}
	}
	else
	{
		std::cout << "Unable to open file.\n";
	}
	file.close();


	return 0;
}