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
	
	else if(node->data == data){
		return false;
	}
		//Creating Node to the left of the tree	
	else if (data < node->data){
			bool rval =  recursiveAdd(node->left, data);
			// if(rval)
			// 	rebalance(node);
			calculateHeight(node);
			return rval;
		}
		//Creating node to the right of the tree
	else if (data > node->data){
		bool rval = recursiveAdd(node->right, data);
		// if(rval)
		// 	rebalance(node);
		calculateHeight(node);
		return rval;
		
	}
		//If data already exists
	else{ 
		bool rval = recursiveAdd(node->right, data);
		// if(rval)
		// 	rebalance(node);
		calculateHeight(node);
		return rval;
	}		
}

bool AVL::remove(int data){
		return recursiveRemove(root, data);
	}

bool AVL::recursiveRemove(Node*& node, int data){
		//If tree is empty
	if(node == NULL)
		return false;
	else{
			//Going to the left
		if(data < node->data){
			return recursiveRemove(node->left, data);
		}
			//Going to the right
		else if (data > node->data){
			return recursiveRemove(node->right, data);
		}
			//The item is in the local root
		else {
			Node* temp = node;
				//If the node doesn't have a lesser child
			if(node->left == NULL)
				node = node->right;
				//If the node doesn't have a higher child
			else if(node->right == NULL)
				node = node->left;
				//If node has both children	
			else 
				replaceParent(temp, temp->left);	
			delete temp;
			return true;			
		}
	}
}

void AVL::rebalance(Node*& node){
	int treeBalance = getBalance(node);

 		//LL or LR tree
	if (treeBalance == -2){
		int localLeftBalance = getBalance(node->left);
			//LL
		if(localLeftBalance == -1 || localLeftBalance == 0){
			cout << "LL" << endl;
			rotateRight(node);
		}
			//LR
		if(localLeftBalance == 1){
			cout << "LR" << endl;
			rotateLeft(node->left);
			rotateRight(node);
		}
	}
		//RR or RL
	if(treeBalance == 2){
		int localRightBalance = getBalance(node->right);
			//RR
		if(localRightBalance == 1 || localRightBalance == 0){
			cout << "RR" << endl;
			rotateLeft(node);
		}
			//LR
		if(localRightBalance == - 1){
			cout << "LR" << endl;
			rotateRight(node->right);
			rotateLeft(node);
		}
	}
	else
		return;
}	



int AVL::get_height(Node *node){
	if (node == nullptr)
		return(0);
	else
		return node->getHeight();
}
void AVL::calculateHeight(Node* node){
	if(node == NULL){
		return;
	}
	int max = 0;
	if(get_height(node->left) > max){
		max = get_height(node->left);
	}
	if(get_height(node->right) > max){
		max = get_height(node->right);
	}
	node->height = max + 1;
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

int AVL::getBalance(Node*& node){
	if(node == NULL)
		return 0;
	if(node->right == NULL)
		return node->left->getHeight();
	if(node->left == NULL)
		return node->right->getHeight();
	else	
		return (node->right->getHeight() - node->left->getHeight());
}

void AVL::rotateRight(Node*& node){
	Node* temp = node->left;
	node->left = temp->right;
	temp->right = node;

	if(node == root) //FIXME:: we may not need this
		root = temp;

	node = temp; 
}

void AVL::rotateLeft(Node*& node){
	Node* temp = node->right;
	node->right = temp->left;

	temp->left = node;

	if(node == root)
		root = temp;

	node = temp;
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