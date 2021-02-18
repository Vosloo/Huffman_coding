#ifndef NODE_H
#define NODE_H

#include <memory>

class Node {
private:
    char ch;
    int freq;
    Node* left;
    Node* right;

public:
    Node(char ch, int freq, Node *left, Node *right);

    Node* getLeft();
    Node* getRight();
    char getChar();
    int getFreq();
};

#endif