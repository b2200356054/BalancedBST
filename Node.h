#ifndef NODE_H
#define NODE_H

#include <string>

using namespace std;

class Node {
private:
    string categoryName;
    bool primary = false;
    Node *parentNode;
    Node *secondaryTreeRoot;
    Node *primaryTreeParent;
    string name;
    string color;
    int price;
    Node *leftNode;
    Node *rightNode;

public:
    const string &getCategoryName() const;

    void setCategoryName(const string &categoryName);

    int getPrice() const;

    void setPrice(int price);

    Node *getSecondaryTreeRoot() const;

    void setSecondaryTreeRoot(Node *secondaryTreeRoot);

    Node *getPrimaryTreeParent() const;

    void setPrimaryTreeParent(Node *primaryTreeParent);

    const string &getName() const;

    void setName(const string &name);

    bool isPrimary() const;

    void setPrimary(bool primary);

    const string &getColor() const;

    void setColor(const string &color);

    Node(string name, int price, string color, string categoryName);

    Node *getParentNode() const;

    void setParentNode(Node *parentNode);

    Node *getLeftNode() const;

    void setLeftNode(Node *leftNode);

    Node *getRightNode() const;

    void setRightNode(Node *rightNode);

};


#endif
