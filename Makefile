CC = g++ --std=c++11

CFLAGS = -Wall -g

webstore: main.o AVLTree.o RedBlackTree.o BinarySearchTree.o Node.o
	$(CC) $(CFLAGS) -o webstore main.o AVLTree.o RedBlackTree.o BinarySearchTree.o Node.o

main.o: main.cpp RedBlackTree.h AVLTree.h
	$(CC) $(CFLAGS) -c main.cpp

AVLTree.o: AVLTree.cpp BinarySearchTree.h
	$(CC) $(CFLAGS) -c AVLTree.cpp

RedBlackTree.o: RedBlackTree.cpp BinarySearchTree.h
	$(CC) $(CFLAGS) -c RedBlackTree.cpp

BinarySearchTree.o: BinarySearchTree.cpp Node.h
	$(CC) $(CFLAGS) -c BinarySearchTree.cpp

Node.o: Node.cpp RedBlackTree.h AVLTree.h
	$(CC) $(CFLAGS) -c Node.cpp

clean:
	$(RM) *.o webstore

.PHONY: clean