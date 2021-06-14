#include "huffman.h"
using namespace std;

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



void dfs(Node* nd, ofstream& file) { //Print pre-order
    if (nd == nullptr)
        return;
      file << nd -> val << "*" << nd ->freq << "*";
    //if (nd -> val != '$')
        cout << "Char: " << nd -> val << " Freq: " << nd ->freq << endl;
    
    dfs(nd -> left, file);
    dfs(nd -> right, file);
}

void sim(Node* nd, ofstream& file) { //Print in-order
    if (nd == nullptr)
        return;
    sim(nd -> left, file);
    sim(nd -> right, file);
    
    file << nd -> val << "*" << nd ->freq << "*";
    //if (nd -> val != '$')
        cout << "Char: " << nd -> val << " Freq: " << nd ->freq << endl;    
}


int main(){
    
    unordered_map<char,int> table;
    make_freq_table(table);
    print_freq_table(table);

    Tree t (table);
    ofstream my_file;
    my_file.open("arvhuf.txt");
    sim(t.root, my_file);
    dfs(t.root, my_file);
    my_file.close();
    
}


