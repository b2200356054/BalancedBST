#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include "RedBlackTree.h"
#include "AVLTree.h"


vector<string> stringSplitterToArray(const string& stringToSplit, const char *delimiter) {
    vector<string> vectr;
    char *stringToSplit1 = const_cast<char *>(stringToSplit.c_str());
    char *ptr = strtok(stringToSplit1, delimiter);
    while (ptr != nullptr) {
        vectr.emplace_back(ptr);
        ptr = strtok(nullptr, delimiter);
    }
    return vectr;
}


int main(int argc, char *argv[]) {
    AVLTree *avlTree = new AVLTree();
    RedBlackTree *redBlackTree = new RedBlackTree();


    vector<string> allArgs(argv, argv+argc);
    string inputFileName = allArgs[1];
    ifstream inputFile(inputFileName);
    ofstream output1(allArgs[2]);
    ofstream output2(allArgs[3]);
    string commandRows;

    while (getline(inputFile, commandRows)){
        vector<string> inputRowVector = stringSplitterToArray(commandRows, "\t");
        if (inputRowVector[0] == "insert"){
            //INSERT COMMAND HERE
            Node *avlNode = new Node(inputRowVector[2], stoi(inputRowVector[3]),"Red", inputRowVector[1]);
            Node *redBlackNode = new Node(inputRowVector[2], stoi(inputRowVector[3]),"Red", inputRowVector[1]);
            avlTree->insertNodeAVL(avlNode, avlTree->getRoot());
            redBlackTree->insertNodeRedBlack(redBlackNode, redBlackTree->getRoot());
        } else if (inputRowVector[0] == "remove"){
            //REMOVE COMMAND HERE
            avlTree->deleteNodeAVL(inputRowVector[2], avlTree->findNode(inputRowVector[1], avlTree->getRoot())->getSecondaryTreeRoot());

            //MY RED BLACK TREE REMOVE COMMAND DOES NOT WORK! (I TRIED BUT COULDN'T IMPLEMENT IT)

            //redBlackTree->deleteNodeRedBlack(inputRowVector[2], redBlackTree->findNode(inputRowVector[1], redBlackTree->getRoot()));
        } else if (inputRowVector[0] == "printAllItems"){
            //DISPLAY COMMAND HERE
            output1 << "command:" << inputRowVector[0] << endl;
            output2 << "command:" << inputRowVector[0] << endl;
            output1 << "{";
            output2 << "{";
            avlTree->displayTree(avlTree->getRoot(), output1);
            redBlackTree->displayTree(redBlackTree->getRoot(), output2);
            output1 << "\n}\n";
            output2 << "\n}\n";
        } else if (inputRowVector[0] == "printAllItemsInCategory"){
            //DISPLAY CATEGORY HERE
            output1 << "command:" << inputRowVector[0] << "\t" << inputRowVector[1] << endl;
            output2 << "command:" << inputRowVector[0] << "\t" << inputRowVector[1] << endl;
            Node *avlRoot = avlTree->findNode(inputRowVector[1], avlTree->getRoot());
            Node *redBlackRoot = redBlackTree->findNode(inputRowVector[1], redBlackTree->getRoot());
            if (avlRoot->getSecondaryTreeRoot() == nullptr){
                output1 << "{\n\"" << avlRoot->getName() << "\":{}\n}\n";
            } else {
                output1 << "{\n\"" << avlRoot->getName() << "\":";
            }
            avlTree->displayTree(avlRoot->getSecondaryTreeRoot(), output1);
            if (avlRoot->getSecondaryTreeRoot() != nullptr){
                output1 << "\n}\n";
            }


            if (redBlackRoot->getSecondaryTreeRoot() == nullptr){
                output2 << "{\n\"" << redBlackRoot->getName() << "\":{}\n}\n";
            } else {
                output2 << "{\n\"" << redBlackRoot->getName() << "\":";
            }
            redBlackTree->displayTree(redBlackRoot->getSecondaryTreeRoot(), output2);
            if (redBlackRoot->getSecondaryTreeRoot() != nullptr){
                output2 << "\n}\n";
            }

        } else if (inputRowVector[0] == "printItem"){
            //DISPLAY ITEM HERE
            output1 << "command:" << inputRowVector[0] << "\t" << inputRowVector[1] << "\t" << inputRowVector[2] << endl;
            output2 << "command:" << inputRowVector[0] << "\t" << inputRowVector[1] << "\t" << inputRowVector[2] << endl;
            Node *avlNode = avlTree->findNode(inputRowVector[2], avlTree->findNode(inputRowVector[1],
                                                                                   avlTree->getRoot())->getSecondaryTreeRoot());
            Node *redBlackNode = redBlackTree->findNode(inputRowVector[2], redBlackTree->findNode(inputRowVector[1],
                                                                                   redBlackTree->getRoot())->getSecondaryTreeRoot());
            if (avlNode != nullptr){
                output1 << "{\n\"" + avlNode->getCategoryName() + "\":\n" + "\t\"" + avlNode->getName() +"\":\""
                           + to_string(avlNode->getPrice()) + "\"\n}\n";
            } else {
                output1 << "{}\n";
            }
            if (redBlackNode != nullptr){
                output2 << "{\n\"" + redBlackNode->getCategoryName() + "\":\n" + "\t\"" + redBlackNode->getName() +"\":\""
                           + to_string(redBlackNode->getPrice()) + "\"\n}\n";
            }else {
                output2 << "{}\n";
            }
        } else if (inputRowVector[0] == "find"){
            //FIND COMMAND HERE
            output1 << "command:" << inputRowVector[0] << "\t" << inputRowVector[1] << "\t" << inputRowVector[2] << endl;
            output2 << "command:" << inputRowVector[0] << "\t" << inputRowVector[1] << "\t" << inputRowVector[2] << endl;
            Node *avlNode = avlTree->findNode(inputRowVector[2], avlTree->findNode(inputRowVector[1],
                                                                                   avlTree->getRoot())->getSecondaryTreeRoot());
            Node *redBlackNode = redBlackTree->findNode(inputRowVector[2], redBlackTree->findNode(inputRowVector[1],
                                                                                                  redBlackTree->getRoot())->getSecondaryTreeRoot());
            if (avlNode != nullptr){
                output1 << "{\n\"" + avlNode->getCategoryName() + "\":\n" + "\t\"" + avlNode->getName() +"\":\""
                           + to_string(avlNode->getPrice()) + "\"\n}";
            }else {
                output1 << "{}\n";
            }
            if (redBlackNode!= nullptr){
                output2 << "{\n\"" + redBlackNode->getCategoryName() + "\":\n" + "\t\"" + redBlackNode->getName() +"\":\""
                           + to_string(redBlackNode->getPrice()) + "\"\n}";
            }else {
                output2 << "{}\n";
            }

        } else if (inputRowVector[0] == "updateData"){
            //UPDATE DATA HERE
            Node *avlNode = avlTree->findNode(inputRowVector[2],avlTree->findNode(inputRowVector[1], avlTree->getRoot())->getSecondaryTreeRoot());
            avlNode->setPrice(stoi(inputRowVector[3]));
        }
    }

    output1.close();
    output2.close();
    return 0;
}

