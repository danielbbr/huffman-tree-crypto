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
        Node() {
            freq = 0;
            val = '$';
            left = nullptr;
            right = nullptr;
        }
    
    public:
        int freq;
        char val;
        Node* left;
        Node* right;
};

class FreqComparator
{
public:
    bool operator() (const Node *n1, const Node *n2)
    {
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
            
            //Iterate over heap
            while (pq.size() > 1) { 
                Node *n1, *n2; 
                n1 = pq.top();
                pq.pop();
                n2 = pq.top();
                pq.pop();

                Node *aux = new Node(n1 -> freq + n2 -> freq, '$');
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

void print_freq_table(unordered_map<char,int> table) {
    unordered_map<char, int>::iterator it;
    for (it = table.begin(); it != table.end(); ++it)
      cout << it -> first << " => " << it -> second << endl;
}

void make_freq_table(unordered_map<char,int> &table) {
    fstream my_file;
    my_file.open("input.txt", ios::in);

    if (!my_file)
        cout << "No such file" << endl;
    else {
        char ch;
        while (!my_file.eof()) {
            my_file >> ch;
            if (!my_file.eof()) //To prevent from counting the last char one extra time
                table[ch]++; 
        }
    }
    my_file.close();
}



void dfs(Node* nd) { //Print pre-order
    if (nd == nullptr)
        return;
    
    //if (nd -> val != '$')
        cout << "Char: " << nd -> val << " Freq: " << nd ->freq << endl;
    
    dfs(nd -> left);
    dfs(nd -> right);
}

void sim(Node* nd) { //Print in-order
    if (nd == nullptr)
        return;
    sim(nd -> left);
    sim(nd -> right);
    //if (nd -> val != '$')
    cout << "Char: " << nd -> val << " Freq: " << nd ->freq << endl;    
}


int main(){
    
    unordered_map<char,int> table;
    make_freq_table(table);
    print_freq_table(table);

    Tree t (table);
    sim(t.root);
    
}

