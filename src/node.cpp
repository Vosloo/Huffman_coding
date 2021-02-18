#include "node.hpp"

Node::Node(char ch, int freq, Node* left, Node* right) {
    this->ch = ch;
    this->freq = freq;
    this->left = left;
    this->right = right;
}

char Node::getChar() {
    return this->ch;
}

int Node::getFreq() {
    return this->freq;
}

Node* Node::getLeft() {
    return this->left;
}

Node* Node::getRight() {
    return this->right;
}
