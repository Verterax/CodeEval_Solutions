// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 11
// Lowest Common Ancestor

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

vector<string> GetLines(string fileName);
vector<string> GetTokens(string line);


#pragma region Binary Tree

template <class T>
struct Node
{
	T data;
	int balance;
	Node *left;
	Node *right;
};

#pragma region Prototypes

template<class T>
class BinaryTree
{
public:
	BinaryTree<T>();
	~BinaryTree();

	virtual void insert(T data);
	virtual bool remove(T data);
	T findMin();
	T findMax();
	T findLCA(T val1, T val2);
	Node<T> *contains(T data);
	void destroyTree();
	void printTree();
	int height();
	int count();
	bool isEmpty();

protected:
	Node<T> *root;

private:
	void insert(T data, Node<T> *&node);
	bool remove(T data, Node<T> *&node);
	T findMin(Node<T> *&node);
	T findMax(Node<T> *&node);
	Node<T> *findLCA(Node<T> *&node, T val1, T val2);
	Node<T> *contains(T data, Node<T> *&node);
	void destroyTree(Node<T> *&node);
	void printTree(Node<T> *node, int atDepth, int currentDepth, int space);
	int height(Node<T> *&node);
	int count(Node<T> *&node);
};

#pragma endregion

#pragma region Constructors

template <class T>
BinaryTree<T>::BinaryTree()
{
	this->root = NULL;
}


#pragma endregion

#pragma region Destructors / Destroy Tree

template <class T>
BinaryTree<T>::~BinaryTree()
{
	this->destroyTree();
}

template <class T>
void BinaryTree<T>::destroyTree(Node<T> *&node)
{
	if (node != NULL)
	{
		this->destroyTree(node->left);
		this->destroyTree(node->right);
	}
	delete node;
}

template <class T>
void BinaryTree<T>::destroyTree()
{
	if (this->root != NULL)
		this->destroyTree(this->root);

	this->root = NULL;
}

#pragma endregion

#pragma region Utility
template <class T>
bool BinaryTree<T>::isEmpty()
{
	return this->root == NULL;
}

template <class T>
int BinaryTree<T>::height(Node<T> *&node)
{
	if (node == NULL)
		return 0;
	else
	{
		int lHeight = height(node->left);
		int rHeight = height(node->right);

		return (rHeight > lHeight)
			? rHeight + 1
			: lHeight + 1;
	}
}

template <class T>
int BinaryTree<T>::height()
{
	return height(this->root);
}

template <class T>
int BinaryTree<T>::count()
{
	return this->count(this->root);
}

template <class T>
int BinaryTree<T>::count(Node<T> *&node)
{
	if (node != NULL)
	{
		return count(node->left)
			+ count(node->right) + 1;
	}
	else
		return 0;
}

#pragma endregion

#pragma region Insert

template <class T>
void BinaryTree<T>::insert(T data, Node<T> *&node)
{
	if (node == NULL)
	{
		node = new Node<T>;
		//node->balance = EQUAL;
		node->data = data;
		node->left = NULL;
		node->right = NULL;
	}
	else if (data < node->data)
	{
		insert(data, node->left);
	}
	else if (data > node->data)
	{
		insert(data, node->right);
	}

	return;
}

template <class T>
void BinaryTree<T>::insert(T data)
{
	this->insert(data, this->root);
}


#pragma endregion

#pragma region Remove

template <class T>
bool BinaryTree<T>::remove(T data, Node<T> *&node)
{
	if (this->root == NULL)
		return false;
	if (data < node->data)
		this->remove(data, node->left);
	else if (data > node->data)
		this->remove(data, node->right);
	else if (node->left != NULL && node->right != NULL)
	{
		node->data = findMin(node->right);
		remove(node->data, node->right);
	}
	else
	{
		Node<T> *oldNode = node;

		node = (node->left != NULL)
			? node = node->left
			: node = node->right;

		delete oldNode;
		return true;
	}
	return false;
}

template <class T>
bool BinaryTree<T>::remove(T data)
{
	return this->remove(data, this->root);
}

#pragma endregion

#pragma region Find Min/Max

template <class T>
T BinaryTree<T>::findMin(Node<T> *&node)
{
	if (node->left == NULL)
		return node->data;
	else
		return findMin(node->left);
}

template <class T>
T BinaryTree<T>::findMin()
{
	return this->findMin(this->root);
}

template <class T>
T BinaryTree<T>::findMax(Node<T> *&node)
{
	if (node->right == NULL)
		return node->data;
	else
		return findMax(node->right);
}

template <class T>
T BinaryTree<T>::findMax()
{
	return this->findMax(this->root);
}

template <class T>
T BinaryTree<T>::findLCA(T val1, T val2)
{
	Node<T>* LCANode = this->findLCA(this->root, val1, val2);	
	return (LCANode != NULL) ? LCANode->data : NULL;
}

template <class T>
Node<T> *BinaryTree<T>::findLCA(Node<T> *&node, T val1, T val2)
{
	if (node == NULL) return NULL;
	if (node->data == val1 || node->data == val2)
		return node;

	Node<T>* left_LCA = findLCA(node->left, val1, val2);
	Node<T>* right_LCA = findLCA(node->right, val1, val2);

	if (left_LCA != NULL && right_LCA != NULL) return node;
	return (left_LCA != NULL) ? left_LCA : right_LCA;
}

#pragma endregion

#pragma region Contains

template <class T>
Node<T> *BinaryTree<T>::contains(T data, Node<T> *&node)
{
	if (node == NULL)
		return NULL;
	else if (data < node->data)
		return contains(data, node->left);
	else if (data > node->data)
		return contains(data, node->right);
	else
		return node;
}

template <class T>
Node<T> *BinaryTree<T>::contains(T data)
{
	return contains(data, this->root);
}

#pragma endregion

#pragma region Print Tree

template <class T>
void BinaryTree<T>::printTree()
{
	int height = this->height(this->root);
	int space = 32;

	for (int i = 0; i < height; i++)
	{
		space /= 2;
		if (space == 0)
			cout << ' ';
		else
			for (int j = 0; j < space; j++)
				cout << ' ';

		this->printTree(this->root, i, 0, space);
		cout << endl;
	}

	if (height > 6)
		cout << "Note: This tree will not draw accurately past a height of 6." << endl;

}

template <class T>
void BinaryTree<T>::printTree(Node<T> *node, int atDepth, int currentDepth, int space)
{
	if (currentDepth == atDepth)
	{
		if (node != NULL)
		{
			for (int j = 0; j < space; j++)
				if (j == 0)
					cout << (char)218;
				else
					cout << (char)196;

			if (node->data < 10 && node->data >-1)
				cout << '0';

			cout << node->data;

			for (int j = 0; j < space; j++)
				if (j == space - 1)
					cout << (char)191;
				else
					cout << (char)196;
			return;
		}
		else
		{
			int spc = space * 2 + 2;
			spc = (spc == 0) ? 1 : spc;

			for (int i = 0; i < spc; i++)
				cout << ' ';
		}
	}
	else
	{
		if (node != NULL)
			this->printTree(node->left, atDepth, currentDepth + 1, space);
		else
			this->printTree(NULL, atDepth, currentDepth + 1, space);

		for (int j = 0; j < space * 2 - 2; j++)
			cout << ' ';

		if (node != NULL)
			this->printTree(node->right, atDepth, currentDepth + 1, space);
		else
			this->printTree(NULL, atDepth, currentDepth + 1, space);
	}
}

#pragma endregion


#pragma endregion

#pragma region Main Program

int LCA(string line, BinaryTree<int>& tree)
{
	//Code goes here.
	//cout << line << endl;
	vector<string> tokens = GetTokens(line);
	int val1 = atoi(tokens[0].c_str());
	int val2 = atoi(tokens[1].c_str());

	return tree.findLCA(val1, val2);
}

void InitTree(BinaryTree<int> &tree)
{
	tree.insert(30);
	tree.insert(8);
	tree.insert(52);
	tree.insert(3);
	tree.insert(20);
	tree.insert(10);
	tree.insert(29);
}

vector<string> GetLines(string fileName)
{
	string line;
	vector<string> lines;
	ifstream file(fileName);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			if (line.size() >= 2)
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

vector<string> GetTokens(string line)
{
	vector<string> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, ' '))
	{
		tokens.push_back(token);
	}

	return tokens;
}

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }
	string fileName = argv[1];
	BinaryTree<int> tree;
	string line;
	vector<string> lines = GetLines(fileName);
	int lineCount = lines.size();
	if (lineCount == 0) { cout << "No lines\n"; return 0; }
	InitTree(tree);
	//tree.printTree();

	for (int i = 0; i < lineCount; i++)
	{
		//Evaluate lines.
		cout << LCA(lines[i], tree) << endl;
	}

	return 0;
}


#pragma endregion 

