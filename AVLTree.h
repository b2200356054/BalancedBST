#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include "BinarySearchTree.h"
#include "Node.h"
using namespace std;


class AVLTree: public BinarySearchTree {
private:
public:
    AVLTree();
    Node *findFirstUnbalanced(Node *subRoot);
    int findMaxBranchLength(Node *subRoot, int currentLength, int &maxLength);

    void insertBalance(Node *subRoot);

    void insertNodeAVL(Node *insertedNode, Node *root1);

    void deleteNodeAVL(string deletedValue, Node *subRoot);
};


#endif
