#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <queue>

#include "node.hpp"
#include "compare.hpp"

using namespace std;


string readFile(char const *argv[]) {
    string buffer;
    ifstream infile(argv[1]);
    
    getline(infile, buffer);
    infile.close();

    return buffer;
}

string decode(Node* root, vector<bool> encoded) {
    Node* curNode = root;
    string decoded = "";
    for (int ind = 0; ind < (int)encoded.size() - 2; ind++) {
        if (encoded[ind] == 0) {
            curNode = curNode->getLeft();
        }
        else {
            curNode = curNode->getRight();
        }

        // Leaf node
        if (curNode->getChar() != '\0') {
            decoded += curNode->getChar();
            curNode = root;
        }
    }

    return decoded;
}

vector<bool> getNewCode(vector<bool> code, bool val) {
    vector<bool> newCode;
    newCode.swap(code);
    newCode.push_back(val);

    return newCode;
}


void encode(Node *root, vector<bool> code, map<char, vector<bool>> &codes) {
    if (root == nullptr) {
        return;
    }

    // Leaf node
    if (!root->getLeft() && !root->getRight()) {
        codes[root->getChar()] = code;
    }

    // DFS
    vector<bool> newCode = getNewCode(code, 0);
    encode(root->getLeft(), newCode, codes);
    
    newCode = getNewCode(code, 1);
    encode(root->getRight(), newCode, codes);
}

void binaryWrite(ofstream& fout, const vector<bool>& x)
{
    vector<bool>::size_type n = x.size();
    fout.write((const char*)&n, sizeof(vector<bool>::size_type));
    for(vector<bool>::size_type i = 0; i < n;)
    {
        unsigned char aggr = 0;
        for(unsigned char mask = 1; mask > 0 && i < n; ++i, mask <<= 1)
            if(x.at(i))
                aggr |= mask;
        fout.write((const char*)&aggr, sizeof(unsigned char));
    }
}

void create(string buffer) {
    map<char, int> frequencies;

    for (char ch : buffer) {
        frequencies[ch]++;
    }

    priority_queue<Node*, vector<Node*>, Compare> pQueue;

    for (auto const& [key, value] : frequencies) {
        pQueue.push(new Node(key, value, nullptr, nullptr));
    }

    while (pQueue.size() != 1) {
        Node* left = pQueue.top(); pQueue.pop();
        Node* right = pQueue.top(); pQueue.pop();

        int freq_sum = left->getFreq() + right->getFreq();
        pQueue.push(new Node('\0', freq_sum, left, right));
    }

    Node* root = pQueue.top();
    map<char, vector<bool>> codes;

    encode(root, vector<bool>(), codes);

    for (auto const& [key, value] : codes) {
        cout << key << " ";
        for (auto b : value) {
            cout << b;
        }
        cout << endl;
    }
    
    vector<bool> encoded;
    for (char ch: buffer) {
        encoded.insert(end(encoded), begin(codes[ch]), end(codes[ch]));
    }

    ofstream encodedFile("data/encoded.bin");
    binaryWrite(encodedFile, encoded);
    encodedFile.close();

    string decoded = decode(root, encoded);

    ofstream decodedFile("data/decoded.txt");
    decodedFile << decoded;
    decodedFile.close();
}


int main(int argc, char const *argv[])
{
    if(argc < 2) {
        cerr << "Input file must be suplied!" << endl;
        return -1;
    }
    else if(argc > 2) {
        cerr << "Too many input values!" << endl;
        return -1;
    }

    string buffer = readFile(argv);
    create(buffer);

    return 0;
}
