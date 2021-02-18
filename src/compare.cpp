#include "compare.hpp"

bool Compare::operator()(Node *left, Node *right) {
    return left->getFreq() > right->getFreq();
}