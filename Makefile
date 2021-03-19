TARGETS = Test_AVL avl
CC = g++
CCFLAGS = -std=c++11 -g
avl: main.cpp AVLInterface.h NodeInterface.h AVL.h AVL.cpp Node.h Node.cpp
	$(CC) $(CCFLAGS) -o avl main.cpp AVL.cpp Node.cpp
AVL: Test_AVL.cpp AVL.h AVL.h BTNode.h pre_order_traversal.h
	$(CC) $(CCFLAGS) -o AVL AVL.cpp