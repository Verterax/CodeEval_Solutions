// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 49
// Peak Traffic

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Node {
public:
	Node() {}
	Node(string userEmail)
	{
		Init(userEmail);
	}
	~Node()
	{
		Dispose();
	}

	void SendMsgTo(string reciever, Node* recieverNode)
	{
		this->sendsTo.emplace(reciever, recieverNode);
	}

	string email;
	unordered_map<string, Node*> sendsTo;

private:
	void Init(string email)
	{
		this->email = email;
	}
	void Dispose()
	{
		while (sendsTo.begin()->second != NULL)
			delete sendsTo.begin()->second;
	}
};

class ClusterReporter
{
public:
	ClusterReporter()
	{
		Init();
	}
	~ClusterReporter()
	{ 
		Dispose(); 
	}
	Node* AddUser(string userEmail)
	{
		Node* userNode = new Node(userEmail);
		this->users[userEmail] = userNode;
		return userNode;
	}
	void RegisterAction(string sender, string reciever)
	{
		//Locate or create users.
		Node* senderNode = users[sender];
		if (senderNode == NULL) senderNode = AddUser(sender);
		Node* recieverNode = users[reciever];
		if (recieverNode == NULL) recieverNode = AddUser(reciever);

		//Add the reciever to the senders hash.
		senderNode->SendMsgTo(reciever, recieverNode);
	}
	vector<string> GetClusters()
	{
		vector<string> clusters;

		unordered_map<string, Node*>::iterator iter = users.begin();
		while (iter != users.end())
		{
			//For each user in users, get this users max cluster.
			Node* user = iter->second;

			
		}

		sort(clusters.begin(), clusters.end());
		return clusters;
	}

private:
	//Data
	unordered_map<string, Node*> users;

	void Init()
	{

	}
	void Dispose()
	{
		while (users.begin()->second != NULL)
			delete users.begin()->second;
	}
	
};

#pragma region Defaults

vector<string> GetLines(string fileName)
{
	string line;
	vector<string> lines;
	ifstream file(fileName);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			lines.push_back(line);
		}
	}
	else
	{
		cout << "Unable to open file.\n";
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

vector<int> GetInts(string line, char delim)
{
	vector<int> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, delim))
	{
		tokens.push_back(atoi(token.c_str()));
	}

	return tokens;
}

void RemChars(string& str, const char chars[], int charLen)
{
	int i;
	int strLen = str.size();
	string::iterator iter = str.begin();
	bool didErase = false;
	while (iter != str.end())
	{
		didErase = false;
		for (i = 0; i < charLen; i++)
			if ((*iter) == chars[i])
			{
				str.erase(iter);
				didErase = true;
				break;
			}
		if (!didErase) iter++;
	}
}

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }
	vector<string> lines = GetLines(argv[1]);
	int lineCount = lines.size();
	if (lineCount == 0) { cout << "No lines\n"; return 0; }

	ClusterReporter reporter;

	for (int i = 0; i < lineCount; i++)
	{
		vector<string> tokens = GetTokens(lines[i], ' ');
		reporter.RegisterAction(tokens[9], tokens[13]);
	}

	return 0;
}

#pragma endregion