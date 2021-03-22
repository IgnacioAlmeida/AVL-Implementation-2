#include "AVL.h"

bool AVL::add(int data) {
	return recursiveAdd(root, data);
}

bool AVL::recursiveAdd(Node*& node, int data) {
		//If Tree is empty
	if (node == NULL){
		node = new Node(data);
		cout << "Insert new node " << node->data << endl;
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


void AVL::rebalance(Node*& node){
	int treeBalance = getBalance(node);
	cout << "treeBalance: " << treeBalance << " on node " << node->data << endl;
 		//LL or LR tree
	if (treeBalance < -1){
		//int localLeftBalance = getBalance(node->left);
			//LL
		if(getBalance(node->left) == -1 || getBalance(node->left) == 0){
			cout << "LL" << endl;
			rotateRight(node);
		}
			//LR
		else if(getBalance(node->left) == 1){
			cout << "LR" << endl;
			rotateLeft(node->left);
			rotateRight(node);
		}
	}
		//RR or RL
	else if(treeBalance > 1){
		//int localRightBalance = getBalance(node->right);
			//RR
		if(getBalance(node->right) == 1 || getBalance(node->right) == 0){
			cout << "RR" << endl;
			rotateLeft(node);
		}
			//RL
		else if(getBalance(node->right) == - 1){
			cout << "RL" << endl;
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

int AVL::get_height(Node* node){
	if (node == nullptr)
		return(0);
	else
		return node->getHeight();
}
//return an integer and update in add function
int AVL::calculateHeight(Node* node){
	if(node == NULL){
		return 0;
	}
	int max = 0;
	if(get_height(node->left) > max){
		max = get_height(node->left);
	}
	if(get_height(node->right) > max){
		max = get_height(node->right);
	}
	// node->height = max + 1;
	return max + 1;
	// cout << "node " << node->data << " with height " << node->height << endl;
}

void AVL::rotateRight(Node*& node){
	cout << "In ---> rotateRight for: " << node->data << endl;
	Node* temp = node->left;
  node->left = temp->right;
  temp->right = node;
  node = temp;

	node->height = calculateHeight(node);

}

void AVL::rotateLeft(Node*& node){
	cout << "In rotateLeft<---- for: " << node-> data << endl;
	Node* temp = node;
	node = node->right;
	temp->right = node->left;
	node->left = temp;

	node->height = calculateHeight(node);

}

int AVL::max(int x, int y){
	return (x > y)? x : y;
}

void AVL::printTree(Node*& node){
	if(node == NULL)
		return;
	cout << "Value: " << node->data << " - Height: " << node->getHeight() << endl;
	printTree(node->left);
	printTree(node->right);
}

void AVL::clear(){
		while(root != NULL){
		remove(root->data);
	}
}

bool AVL::remove(int data){
	return recursiveRemove(root, data);
}

bool AVL::recursiveRemove(Node*& node, int data){
	bool rval;
		//1. Base Condition - If node is empty
	if(node == NULL){
		return false;
	}
	else{
			//2. Going to the left
		if(data < node->data){
			return recursiveRemove(node->left, data);
		}
			//3. Going to the right
		else if (data > node->data){
			return recursiveRemove(node->right, data);
		}
			//4. Node to be deleted found
		else if (node->data == data){
			cout << "deleting node " << node->data << endl;
			Node* temp = node;

				//If the node doesn't have a lesser child
			if(node->left == NULL){
				cout << "If node doesn't have lesser child " << endl;
				node = node->right;
			}
				//If the node doesn't have a higher child
			else if(node->right == NULL){
				cout << "If node doesn't have a higher child "<< endl;
				node = node->left;
			}
				//If node has both children	
			else {
				cout << "if node has both children" << endl;
				replaceParent(temp, temp->left);
			}
				cout << endl << "------> rebalance <------" << endl;
				rebalance(node);
				cout << "before updating height " << endl;
				node->height = calculateHeight(node);	
			delete temp;
			return true;

			}
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