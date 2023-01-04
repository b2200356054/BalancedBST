#include <iostream>
#include "RedBlackTree.h"

RedBlackTree::RedBlackTree() {
    this->root = nullptr;
    this->size = 0;
}

void RedBlackTree::insertNodeRedBlack(Node *insertedNode, Node *root1) {
    Node *categoryNode = this->findNode(insertedNode->getCategoryName(), root1);
    if (categoryNode == nullptr) {
        Node *categoryNode1 = new Node(insertedNode->getCategoryName(), 0, "Red", "");
        this->insertNode(categoryNode1, root1);
        categoryNode1->setSecondaryTreeRoot(insertedNode);
        insertedNode->setPrimaryTreeParent(categoryNode1);
        this->size++;
        insertBalance(root1);
    } else {
        this->insertNode(insertedNode, categoryNode->getSecondaryTreeRoot());
        insertBalance(categoryNode->getSecondaryTreeRoot());
    }
}

void RedBlackTree::deleteNodeRedBlack(string deletedValue, Node *subRoot) {
    Node* deletedNode = findNode(deletedValue, subRoot);
    string deletedColor = deletedNode->getColor();
    Node* replacedNode = deleteNode(deletedValue, subRoot);
    insertBalance(replacedNode);
}

void RedBlackTree::insertBalance(Node *subRoot){
    if (subRoot == nullptr){
        return;
    }
    if (subRoot == this->root){
        subRoot->setColor("Black");
    }
    string rightColor = "Black";
    Node *leftLeft = nullptr;
    string leftLeftColor = "Black";
    string leftColor = "Black";
    if (subRoot->getRightNode() != nullptr){
        rightColor = subRoot->getRightNode()->getColor();
    }
    if (subRoot->getLeftNode() != nullptr){
        leftColor = subRoot->getLeftNode()->getColor();
        leftLeft = subRoot->getLeftNode()->getLeftNode();
        if (leftLeft != nullptr){
            leftLeftColor = leftLeft->getColor();
        }
    }
    if (rightColor == "Red" && leftColor == "Black"){ //CASE 1 RIGHT RED CHILD AND BLACK LEFT CHILD
        leftRotation(subRoot);
        swapColors(subRoot, subRoot->getParentNode());
        insertBalance(subRoot);
    } else if (leftLeftColor == "Red" && leftColor == "Red"){ //CASE 2 RED LEFT AND LEFT-LEFT GRANDCHILD
        rightRotation(subRoot);
        swapColors(subRoot, subRoot->getParentNode());
        insertBalance(subRoot);
    } else if (leftColor == "Red" && rightColor == "Red"){ //CASE 3
        flipColors(subRoot);
        insertBalance(subRoot);
    } else {
        insertBalance(subRoot->getParentNode());
    }

}

void RedBlackTree::swapColors(Node *node1, Node *node2){
    if (node2 == nullptr || node1 == nullptr){
        return;
    }
    string temp = node1->getColor();
    node1->setColor(node2->getColor());
    node2->setColor(temp);
}

void RedBlackTree::flipColors(Node *subRoot){
    Node *left = subRoot->getLeftNode();
    Node *right = subRoot->getRightNode();
    string rightColor;
    string leftColor;
    if (left != nullptr){
        leftColor = left->getColor();
    } else {
        return;
    }
    if (right != nullptr){
        rightColor = right->getColor();
    } else {
        return;
    }
    if (leftColor == "Red" && rightColor == "Red"){
        left->setColor("Black");
        right->setColor("Black");
    }else {
        return;
    }
    if (subRoot->getColor() == "Black"){
        subRoot->setColor("Red");
    }else if (subRoot->getColor() == "Red"){
        subRoot->setColor("Black");
    }
}