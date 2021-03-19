#pragma once
#include "NodeInterface.h"
#include <iostream>

class Node : public NodeInterface {
public:
	int data;
	Node* left;
	Node* right;
	int height;
	
	
	Node(const int &theData, Node* leftVal = NULL, Node* rightVal =  NULL) :
		data(theData), left(leftVal), right(rightVal){height = 1;}

	virtual ~Node() {}

	int getData() const;

	Node* getLeftChild() const;

	Node* getRightChild() const;

	Node* getLeft();

	Node* getRight();

	int getHeight();
};