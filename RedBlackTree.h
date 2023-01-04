
#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <string>

using namespace std;

#include "BinarySearchTree.h"

class RedBlackTree: public BinarySearchTree {
private:
public:
    RedBlackTree();

    void insertNodeRedBlack(Node *insertedNode, Node *root1);

    void deleteNodeRedBlack(string deletedValue, Node *subRoot);

    void insertBalance(Node *subRoot);

    void swapColors(Node *node1, Node *node2);

    void flipColors(Node *subRoot);

};


#endif
