#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <queue>
using namespace std;

class Node {
    public:
        Node(int frequency, char value) {
            freq = frequency;
            val = value;
            left = nullptr;
            right = nullptr;
        }
        Node(int freq, char val, Node* left, Node* right): freq(freq), val(val), left(left), right(right) {}

    public:
        int freq;
        char val;
        Node* left;
        Node* right;
};

class FreqComparator {
public:
    bool operator() (const Node *n1, const Node *n2) {
        
        return ( (n1 -> freq) > (n2 -> freq) );
    }
};


class Tree {
    public:
        Tree() {
            root = nullptr;
        }
        Tree(unordered_map<char,int> freq_table) {
            
            //Min heap for frequencies
            priority_queue<Node*, vector<Node*>, FreqComparator> pq;
            
            /*
            for (auto it = freq_table.begin(); it != freq_table.end(); ++it) {
                cout << "Char: " <<  it -> first << " Freq: " << it -> second << endl;
            }
            cout << "end" << endl;
            */

            for (auto it = freq_table.begin(); it != freq_table.end(); ++it) {
                Node* aux = new Node(it -> second, it -> first);
                pq.push(aux);
            }
            
            
            // Variable to encode non-leaf nodes to be off the ASCII table
            int not_leaf = 256; 
            
            //Iterate over heap
            while (pq.size() > 1) { 
                Node *n1, *n2; 
                n1 = pq.top();
                pq.pop();
                n2 = pq.top();
                pq.pop();

                Node *aux = new Node(n1 -> freq + n2 -> freq, not_leaf);
                not_leaf++;
                aux -> left = n1;
                aux -> right = n2;
                pq.push(aux);
            }
            //The last one remaining must be the root
            root = pq.top();
            pq.pop();
        }
    public:
        Node* root;
};

#endif
