
#include "AVLTree.h"

void AVLTree::insertNodeAVL(Node *insertedNode, Node *root1){
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

void AVLTree::deleteNodeAVL(string deletedValue, Node *subRoot){
    Node *deletedNode = this->findNode(deletedValue, subRoot);
    if (deletedNode == nullptr){
        return;
    }
    Node *deletedParent = deletedNode->getParentNode();
    this->deleteNode(deletedValue, subRoot);

    insertBalance(deletedParent);
}

void AVLTree::insertBalance(Node *subRoot) {
    if (subRoot == nullptr){
        return;
    }
    Node *z = findFirstUnbalanced(subRoot);
    if (z == nullptr){
        return;
    }
    int maxLengthZRight = 0; int maxLengthZLeft = 0;
    Node *zLeftNode = z->getLeftNode(); Node *zRightNode = z->getRightNode();
    int zRightLength = findMaxBranchLength(zRightNode, 1, maxLengthZRight);
    int zLeftLength = findMaxBranchLength(zLeftNode, 1, maxLengthZLeft);
    if (zRightLength < zLeftLength) {
        Node *y = z->getLeftNode();
        if (y == nullptr){
            return;
        }
        int maxLengthYRight = 0; int maxLengthYLeft = 0;
        int yRightLength = findMaxBranchLength(y->getRightNode(), 1, maxLengthYRight);
        int yLeftLength = findMaxBranchLength(y->getLeftNode(), 1, maxLengthYLeft);
        if (yRightLength > yLeftLength) {
            //CASE 2 LEFT-RIGHT
            this->leftRotation(y);
            this->rightRotation(z);
        } else  {
            //CASE 1 LEFT-LEFT
            this->rightRotation(z);
        }
    } else if (zRightLength > zLeftLength){
        Node *y = z->getRightNode();
        int maxLengthYRight = 0; int maxLengthYLeft = 0;
        int yRightLength = findMaxBranchLength(y->getRightNode(), 1, maxLengthYRight);
        int yLeftLength = findMaxBranchLength(y->getLeftNode(), 1, maxLengthYLeft);
        if (yLeftLength > yRightLength) {
            //CASE 4 RIGHT-LEFT
            this->rightRotation(y);
            this->leftRotation(z);

        } else {
            //CASE 3 RIGHT-RIGHT
            this->leftRotation(z);
        }
    }
}

Node *AVLTree::findFirstUnbalanced(Node *subRoot) {
    if (subRoot == nullptr){
        return nullptr;
    }
    int rightMax = 0; int leftMax = 0;
    int currentLengthRight = 1; int currentLengthLeft = 1;
    int maxLengthRight = 0; int maxLengthLeft = 0;
    if (subRoot->getRightNode() != nullptr){
        rightMax = findMaxBranchLength(subRoot->getRightNode(), currentLengthRight, maxLengthRight);
    }
    if (subRoot->getLeftNode() != nullptr){
        leftMax = findMaxBranchLength(subRoot->getLeftNode(), currentLengthLeft, maxLengthLeft);
    }

    if (rightMax - leftMax > 1 || rightMax - leftMax < -1){
        return subRoot;
    } else {
        return findFirstUnbalanced(subRoot->getParentNode());
    }
}
AVLTree::AVLTree() {
    this->root = nullptr;
    this->size = 0;

}

int AVLTree::findMaxBranchLength(Node *subRoot, int currentLength, int &maxLength){
    if (subRoot == nullptr){
        return 0;
    }
    int leftMax = 0;
    int rightMax = 0;
    if (currentLength > maxLength){
        maxLength = currentLength;
    }
    if (subRoot->getRightNode() == nullptr && subRoot->getLeftNode() == nullptr){
        return maxLength;
    }
    if (subRoot->getLeftNode() != nullptr){
        leftMax = findMaxBranchLength(subRoot->getLeftNode(), currentLength+1, maxLength);
    }
    if (subRoot->getRightNode() != nullptr){
        rightMax = findMaxBranchLength(subRoot->getRightNode(), currentLength+1, maxLength);
    }
    if (leftMax < rightMax){
        return rightMax;
    } else {
        return leftMax;
    }

}

