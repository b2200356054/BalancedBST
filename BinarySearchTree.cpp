
#include "BinarySearchTree.h"
#include <iostream>
using namespace std;

void BinarySearchTree::insertNode(Node *insertedNode, Node *root1) {
    if (this->size == 0){ //INSERT ROOT
        if (insertedNode != nullptr){
            insertedNode->setColor("Black");
            this->root = insertedNode;
            if (!insertedNode->getCategoryName().empty()){
                this->size++;
            }
        } else {
            return;
        }
    } else {
        if (insertedNode->getName() < root1->getName()){//SMALLER THAN ROOT
            if (root1->getLeftNode() == nullptr){
                //THERE'S NO LEFT NODE FOR ROOT THEN INSERT IMMEDIATELY
                insertedNode->setParentNode(root1);
                root1->setLeftNode(insertedNode);
                if (!insertedNode->getCategoryName().empty()){
                    this->size++;
                }
            }else {
                //THERE'S ANOTHER NODE ON THE LEFT SO GO 1 LEVEL DOWN
                insertNode(insertedNode, root1->getLeftNode());
            }
        } else if (insertedNode->getName() > root1->getName()){ //BIGGER THAN ROOT
            if (root1->getRightNode() == nullptr){
                //THERE'S NO RIGHT NODE FOR ROOT THEN INSERT IMMEDIATELY
                insertedNode->setParentNode(root1);
                root1->setRightNode(insertedNode);
                this->size++;
            } else {
                //THERE'S ANOTHER NODE ON THE RIGHT SO GO 1 LEVEL DOWN
                insertNode(insertedNode, root1->getRightNode());
            }
        }
    }

}
Node  *BinarySearchTree::deleteNode(const string& deletedValue, Node *subRoot) {
    if (subRoot == nullptr){
        //IF SUBROOT IS NULL RETURN
        return nullptr;
    }
    if (subRoot->getName() == deletedValue){
        //FOUND THE NODE TO DELETE
        Node *primaryParent = subRoot->getPrimaryTreeParent();
        if (primaryParent != nullptr){
            primaryParent->setSecondaryTreeRoot(nullptr);
        }
        if (subRoot->getRightNode() == nullptr && subRoot->getLeftNode() == nullptr){
            //HAS NO CHILD
            setChildhoodNull(subRoot);
            delete subRoot;
            this->size--;
            return nullptr;

        } else if (subRoot->getRightNode() == nullptr && subRoot->getLeftNode() != nullptr){
            //ONLY HAS LEFT CHILD
            Node *returnValue = subRoot->getLeftNode();
            this->copyNodes(subRoot->getLeftNode(), subRoot);
            setParentsChild(subRoot, subRoot->getLeftNode());
            Node *to_delete = subRoot->getLeftNode();
            subRoot->setLeftNode(nullptr);
            delete to_delete;
            this->size--;
            return returnValue;


        } else if (subRoot->getRightNode() != nullptr && subRoot->getLeftNode() == nullptr){
            //ONLY HAS RIGHT CHILD
            Node *returnValue = subRoot->getRightNode();
            this->copyNodes(subRoot->getRightNode(), subRoot);
            setParentsChild(subRoot, subRoot->getRightNode());
            Node *to_delete = subRoot->getRightNode();
            subRoot->setRightNode(nullptr);
            delete to_delete;
            this->size--;
            return returnValue;

        }  else if (subRoot->getLeftNode() != nullptr && subRoot->getRightNode() != nullptr){
            // HAS 2 CHILDREN (THE WORST NIGHTMARE EVER)
            Node *inOrderSuccessor = findInOrderSuccessor(subRoot); //FIND IN ORDER SUCCESSOR
            Node *inOrderSuccessorParent = inOrderSuccessor->getParentNode();//AND ITS PARENT
            this->copyNodesInOrder(inOrderSuccessor, subRoot);
            if (inOrderSuccessorParent != nullptr) { //IN ORDER SUCCESSOR'S PARENT'S PROPERTIES
                if (inOrderSuccessor == inOrderSuccessorParent->getLeftNode()) {
                    inOrderSuccessorParent->setLeftNode(nullptr);
                } else if (inOrderSuccessor == inOrderSuccessorParent->getRightNode()) {
                    inOrderSuccessorParent->setRightNode(nullptr);
                }
            }
            delete inOrderSuccessor;//DELETE IN ORDER SUCCESSOR AFTER COPY
            this->size--;
            return subRoot;
        }

    } else if (subRoot->getName() < deletedValue){
        //THE VALUE IS LESSER THAN ROOT TURN RIGHT AND GO 1 LEVEL DOWN
        deleteNode(deletedValue, subRoot->getRightNode());
    } else {
        // THE VALUE IS BIGGER THAN ROOT TURN LEFT AND GO 1 LEVEL DOWN
        deleteNode(deletedValue, subRoot->getLeftNode());
    }
    return nullptr;
}
Node *BinarySearchTree::findInOrderSuccessor(Node *neededInOrder){ //FIND THE IN ORDER SUCCESSOR OF A NODE
    if (neededInOrder == nullptr){
        return nullptr;
    }
    if (neededInOrder->getRightNode() != nullptr){ //IF RIGHT CHILD EXIST MINIMUM OF THE RIGHT SUBTREE
        return findMinimum(neededInOrder->getRightNode());
    } else { //THEN SUBROOT IS THE SUCCESSOR
        return getInOrderAncestor(neededInOrder);
    }
}
void BinarySearchTree::rightRotation(Node* subRoot){
    if (subRoot == nullptr){
        return;
    }
    Node *left = subRoot->getLeftNode();
    if (left == nullptr){
        return;
    } else {
        Node *leftRight = left->getRightNode();
        subRoot->setLeftNode(leftRight);
    }
    left->setRightNode(subRoot);
    setParentsChild(subRoot, left);
    if (this->root == subRoot){
        this->root = left;

    }
    if (subRoot->getPrimaryTreeParent() != nullptr){
        Node *parent = subRoot->getPrimaryTreeParent();
        left->setPrimaryTreeParent(parent);
        subRoot->setPrimaryTreeParent(nullptr);
        parent->setSecondaryTreeRoot(left);
    }
    left->setParentNode(subRoot->getParentNode());
    subRoot->setParentNode(left);
}
void BinarySearchTree::leftRotation(Node *subRoot){
    if (subRoot == nullptr){
        return;
    }
    Node *right = subRoot->getRightNode();
    if (right == nullptr){
        return;
    }else {
        Node *rightLeft = right->getLeftNode();
        subRoot->setRightNode(rightLeft);
    }
    right->setLeftNode(subRoot);
    setParentsChild(subRoot, right);
    if (this->root == subRoot){
        this->root = right;

    }
    if (subRoot->getPrimaryTreeParent() != nullptr){
        Node *parent = subRoot->getPrimaryTreeParent();
        right->setPrimaryTreeParent(parent);
        subRoot->setPrimaryTreeParent(nullptr);
        parent->setSecondaryTreeRoot(right);
    }
    right->setParentNode(subRoot->getParentNode());
    subRoot->setParentNode(right);
}
void BinarySearchTree::setParentsChild(Node *subRoot, Node *replacement){
    //CHANGES A NODES CHILD WITH ANOTHER NODE
    Node *the_parent = subRoot->getParentNode();
    if (the_parent == nullptr || replacement == nullptr) {
        return;
    }
    if (subRoot == the_parent->getRightNode()){ //IF SUBROOT IS A RIGHT CHILD
        the_parent->setRightNode(replacement);
    } else if (subRoot == the_parent->getLeftNode()){ //IF SUBROOT IS A LEFT CHILD
        the_parent->setLeftNode(replacement);
    }
}
void BinarySearchTree::setChildhoodNull(Node *subRoot){
    if (subRoot == nullptr){
        return;
    }
    if (subRoot->getParentNode() != nullptr){ //SET RELATION BETWEEN PARENT OF NODE AND THE CHILD OF THE NODE
        if (subRoot->getParentNode()->getLeftNode() == subRoot){
            subRoot->getParentNode()->setLeftNode(nullptr);
        } else if (subRoot->getParentNode()->getRightNode() == subRoot){
            subRoot->getParentNode()->setRightNode(nullptr);
        }
    }
}
void BinarySearchTree::copyNodes(Node *source, Node *path) {
    path->setPrimary(source->isPrimary());
    path->setSecondaryTreeRoot(source->getSecondaryTreeRoot());
    path->setPrimaryTreeParent(source->getPrimaryTreeParent());
    path->setName(source->getName());
    path->setPrice(source->getPrice());
    path->setParentNode(source->getParentNode());
    path->setColor(source->getColor());
    path->setRightNode(source->getRightNode());
    path->setLeftNode(source->getLeftNode());


}
void BinarySearchTree::copyNodesInOrder(Node *source, Node *path){
    path->setColor(source->getColor());
    path->setName(source->getName());
    path->setPrice(source->getPrice());
}
void BinarySearchTree::displayTree(Node *subRoot, ostream &output1) {
    //DISPLAYING TREE WITH PREORDER TRAVERSAL
    if (subRoot == nullptr){
        return;
    } else {
        if (subRoot->getCategoryName() == ""){
            output1 << "\n\"" + subRoot->getName() + "\":";
            if (subRoot->getSecondaryTreeRoot() == nullptr){
                output1 << "{}\n";
            }
        }else {
            output1 << "\n\t" + subRoot->getName() + "\":" + "\"" + to_string(subRoot->getPrice()) + "\"";
        }
        displayTree(subRoot->getSecondaryTreeRoot(), output1);
        displayTree(subRoot->getLeftNode(), output1);
        displayTree(subRoot->getRightNode(), output1);
    }
}
Node *BinarySearchTree::findNode(const string& value, Node *subRoot){
    if (subRoot == nullptr){
        return nullptr;
    } else {
        if (subRoot->getName() == value){
            return subRoot;
        } else if (subRoot->getName() > value){
            return findNode(value, subRoot->getLeftNode());
        } else {
            return findNode(value, subRoot->getRightNode());
        }
    }
}
Node *BinarySearchTree::findMinimum(Node *subRoot){
    //FINDS MINIMUM IN THE CURRENT TREE
    if (subRoot == nullptr){ //IF NULL RETURN
        return nullptr;
    }else {
        if (subRoot->getLeftNode() == nullptr){
            //IF NO LEFT CHILD THEN MINIMUM RETURN.
            return subRoot;
        } else { //THEN GO 1 LEVEL DOWN
            return findMinimum(subRoot->getLeftNode());
        }
    }
}
Node *BinarySearchTree::getInOrderAncestor(Node *subRoot){
    //IF ONE OF THE LEAFS' IN ORDER SUCCESSOR IS NEEDED
    if (subRoot == nullptr){
        return nullptr;
    }else {
        if (subRoot->getParentNode()->getLeftNode() == subRoot){
            //IF SUBROOT IS THE LEFT CHILD OF ITS PARENT RETURN PARENT
            return subRoot->getParentNode();
        } else {
            return getInOrderAncestor(subRoot->getParentNode());
            //ELSE GO 1 LEVEL UP
        }
    }
}
Node *BinarySearchTree::getRoot() const {
    return root;
}
BinarySearchTree::BinarySearchTree() {
    this->root = nullptr;
    this->size = 0;
}
