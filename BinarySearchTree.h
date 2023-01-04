
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include "Node.h"

class BinarySearchTree {
protected:
    Node *root;
    int size;
public:
    BinarySearchTree();

    Node *getRoot() const;

    void rightRotation(Node *subRoot);

    void leftRotation(Node *subRoot);

    void setParentsChild(Node *subRoot, Node *replacement);

    void setChildhoodNull(Node *subRoot);

    void copyNodes(Node *source, Node *path);

    void copyNodesInOrder(Node *source, Node *path);

    void displayTree(Node *subRoot, ostream &output1);

    Node *findInOrderSuccessor(Node *neededInOrder);

    Node *findMinimum(Node *subRoot);

    Node *getInOrderAncestor(Node *subRoot);

    Node *findNode(const string& value, Node *subRoot);

    void insertNode(Node *insertedNode, Node *root1);

    Node *deleteNode(const string& deletedValue, Node *subRoot);
};


#endif
