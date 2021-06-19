#include "huffman.h"
#include <bitset>

using namespace std;

void print_freq_table(unordered_map<char,int> table) {
    unordered_map<char, int>::iterator it;
    for (it = table.begin(); it != table.end(); ++it)
      cout << it->first << " => " << it->second << endl;
}

void make_freq_table(unordered_map<char,int> &table) {
    fstream my_file;
    my_file.open("input.txt", ios::in);

    if (!my_file)
        cout << "No such file" << endl;
    else {
        char ch;
        while (!my_file.eof()) {
            my_file >> noskipws >> ch;
            if (!my_file.eof()) //To prevent from counting the last char one extra time
                table[ch]++; 
        }
    }
    my_file.close();
}



void pre_order(Node* nd, ofstream& file) { //Print pre-order and write to file
    if (nd == nullptr)
        return;
    char c = ',';
    file << noskipws << nd->val << c << nd->freq << c;
    
    
    pre_order(nd->left, file);
    pre_order(nd->right, file);
}

void in_order(Node* nd, ofstream& file) { //Print in-order and write to file
    if (nd == nullptr)
        return;
    char c = ',';
    in_order(nd->left, file);
    file << noskipws << nd->val << c << nd ->freq << c;
    in_order(nd->right, file);
    
        
}

bool char_code(const Node *root, char x, string& code) {
    code = "";
    
    if (!root)
        return false;
      
    if (root->val == x) {   
        
        return true;
    }

    if (char_code(root->left, x, code)) { 
        
        code = '0' + code;
        return true;
    }    
    if (char_code(root->right, x, code)) {
        
        code = '1' + code;
        return true; 
    }
    return false;            
}

void get_tree_file(Node* root) {
    ofstream my_file;
    my_file.open("arvhuf.txt");
    in_order(root, my_file);
    pre_order(root, my_file);
    my_file.close();
}


void get_encoded_file(Node *root, string input_file) { // Creates texto.hfm file representing original text
    fstream my_file;
    fstream output_file;
    string aux, aux2;
    
    my_file.open(input_file, ios::in);
    
    if (!my_file)
        cout << "No such file" << endl;
    else {
        char ch;
        aux = "";
        while (!my_file.eof()) {
                aux2 = "";
                my_file >> noskipws >> ch;
                char_code(root, ch, aux2);
                aux = aux + aux2;
                cout << (int)ch << "-> " <<aux2<< endl; 
    }
        my_file.close();
        output_file.open("texto.hfm", ios::out);
        output_file << noskipws << aux;
        output_file.close();
    }
}

string TextToBinaryString(string words) {
    string binaryString = "";
    for (char& _char : words) {
        binaryString +=bitset<8>(_char).to_string();
    }
    return binaryString;
}




int main() {
    
    unordered_map<char,int> table;
    make_freq_table(table);
   

    Tree t (table);
    get_tree_file(t.root);
    get_encoded_file(t.root, "input.txt");
    

}

