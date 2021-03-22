#include "AVL.h"

bool AVL::add(int data) {
	return recursiveAdd(root, data);
}

bool AVL::recursiveAdd(Node*& node, int data) {
		//If Tree is empty
	if (node == NULL){
		node = new Node(data);
		return true;
	} 
		//If data already exists
	if(node->data == data){
		return false;
	}
		//Creating Node to the left of the tree	
	if (data < node->data){
			bool rval =  recursiveAdd(node->left, data);
			rebalance(node);
			node->height = calculateHeight(node);
			return rval;
		}
		//Creating node to the right of the tree
	else if (data > node->data){
		bool rval = recursiveAdd(node->right, data);
		rebalance(node);
		node->height = calculateHeight(node);
		return rval;
	}
}

void AVL::replaceParent(Node*& temp, Node*& root){
	if(root->right != NULL)
		replaceParent(temp, root->right);
	else {
		temp->data = root->data;
		temp = root;
		root = root->left;
	}
}

bool AVL::remove(int data){
	return recursiveRemove(root, data);
}

bool AVL::recursiveRemove(Node*& node, int data){
	bool rval;
		//Base Condition - If node is empty
	if(node == NULL){
		return false;
	}
	else{
			//Going to the left
		if(data < node->data){
			rval = recursiveRemove(node->left, data);
			if(rval)
				rebalance(node);
			node->height = calculateHeight(node);
			return rval;
		}
			//Going to the right
		else if (data > node->data){
			rval = recursiveRemove(node->right, data);
			if(rval)
				rebalance(node);
			node->height = calculateHeight(node);
			return rval;
		}
			//Node to be deleted found
		else{
			Node* temp = node;

				//If the node doesn't have a lesser child
			if(node->left == NULL){
				node = node->right;
			}
				//If the node doesn't have a higher child
			else if(node->right == NULL){
				node = node->left;
			}
				//If node has both children	
			else {
				replaceParent(temp, temp->left);
				rebalance(node);
			}
			delete temp;
			return true;
		}
	}	
}

void AVL::rebalance(Node*& node){
	int treeBalance = getBalance(node);
 		//LL or LR tree
	if (treeBalance < -1){
			//LL
		if(getBalance(node->left) == -1 || getBalance(node->left) == 0){
			rotateRight(node);
		}
			//LR
		else if(getBalance(node->left) == 1){
			rotateLeft(node->left);
			rotateRight(node);
		}
	}
		//RR or RL
	else if(treeBalance > 1){
			//RR
		if(getBalance(node->right) == 1 || getBalance(node->right) == 0){
			rotateLeft(node);
		}
			//RL
		else if(getBalance(node->right) == - 1){
			rotateRight(node->right);
			rotateLeft(node);
		}
	}
}	


int AVL::getBalance(Node*& node){
	if(node == NULL)
		return 0;
	if(node->right == NULL && node->left == NULL){
		return 0;
	}
	if(node->right == NULL){
		return (0 - calculateHeight(node->left));
		}
	if(node->left == NULL){
		return calculateHeight(node->right);
		}
	else{
		return (calculateHeight(node->right) - calculateHeight(node->left));
	}
}

int AVL::calculateHeight(Node* node){
	if(node == NULL){
		return 0;
	}
	int max = 0;
	if(calculateHeight(node->left) > max){
		max = calculateHeight(node->left);
	}
	if(calculateHeight(node->right) > max){
		max = calculateHeight(node->right);
	}
	return max + 1;
}

void AVL::rotateRight(Node*& node){
	Node* temp = node->left;
  node->left = temp->right;
  temp->right = node;
  node = temp;

	node->height = calculateHeight(node);
}

void AVL::rotateLeft(Node*& node){
	Node* temp = node;
	node = node->right;
	temp->right = node->left;
	node->left = temp;

	node->height = calculateHeight(node);
}

void AVL::printTree(Node*& node){
	if(node == NULL)
		return;
	printTree(node->left);
	printTree(node->right);
}

void AVL::clear(){
		while(root != NULL){
		remove(root->data);
	}
}