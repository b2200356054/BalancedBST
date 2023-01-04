
#include "Node.h"


//Defines the Node attributes.
Node::Node(string name1, int price1, string color1, string categoryName1) {
    this->primaryTreeParent = nullptr;
    this->categoryName = categoryName1;
    this->secondaryTreeRoot = nullptr;
    this->color = color1;
    this->name = name1;
    this->price = price1;
    this->leftNode = nullptr;
    this->rightNode = nullptr;
    this->parentNode = nullptr;
}

Node *Node::getParentNode() const {
    return parentNode;
}

void Node::setParentNode(Node *parentNode1) {
    this->parentNode = parentNode1;
}
Node *Node::getLeftNode() const {
    return leftNode;
}

void Node::setLeftNode(Node *leftNode1) {
    this->leftNode = leftNode1;
}

Node *Node::getRightNode() const {
    return rightNode;
}

void Node::setRightNode(Node *rightNode1) {
    this->rightNode = rightNode1;
}

const string &Node::getColor() const {
    return color;
}

void Node::setColor(const string &color1) {
    this->color = color1;
}

bool Node::isPrimary() const {
    return primary;
}

void Node::setPrimary(bool primary1) {
    this->primary = primary1;
}

Node *Node::getSecondaryTreeRoot() const {
    return secondaryTreeRoot;
}

void Node::setSecondaryTreeRoot(Node *secondaryTreeRoot1) {
    this->secondaryTreeRoot = secondaryTreeRoot1;
}

Node *Node::getPrimaryTreeParent() const {
    return primaryTreeParent;
}

void Node::setPrimaryTreeParent(Node *primaryTreeParent1) {
    this->primaryTreeParent = primaryTreeParent1;
}

const string &Node::getName() const {
    return name;
}

void Node::setName(const string &name1) {
    Node::name = name1;
}

int Node::getPrice() const {
    return price;
}

void Node::setPrice(int price1) {
    this->price = price1;
}

const string &Node::getCategoryName() const {
    return categoryName;
}

void Node::setCategoryName(const string &categoryName1) {
    this->categoryName = categoryName1;
}



