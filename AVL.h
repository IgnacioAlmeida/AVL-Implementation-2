#pragma once
#include "AVLInterface.h"
#include "Node.h"
using namespace std;

class AVL : public AVLInterface {
protected:

public:
	Node *root, *left, *right;
	
	AVL() {root = NULL;}
	virtual ~AVL() {clear();}

	Node* getRootNode() const{ return root;}

	int getBalance(Node*& node);
	
	bool add(int data);

	bool recursiveAdd(Node*& node, int data);

	void replaceParent(Node*& temp, Node*& node);

	bool remove(int data);

	bool recursiveRemove(Node*& node, int data);

	void clear();

	void rotateRight(Node*& node);

	void rotateLeft(Node*& node);

	void rebalance(Node*& node);

	void printTree(Node*& node);

	int calculateHeight(Node* node);
};