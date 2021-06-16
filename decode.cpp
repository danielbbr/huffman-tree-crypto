#include "huffman.h"
#include <vector>

using namespace std;

class recoverTopology {
    public:
        int t = 0;
        Node* build(vector<Node*>pre, vector<Node*>in, int l, int r){
            if(l > r)
                return nullptr;
            
            int ind = l;
            for(int i = l; i <= r; i++){
                if(pre[t]->val == in[i]->val){
                    ind = i;
                    break;
                }
            }
            t++;
            Node* p = new Node(in[ind]->freq, in[ind]->val);
            p->left = build(pre, in, l, ind-1);
            p->right = build(pre, in, ind+1, r);
            return p;
        }
        
        Node* build_tree(vector<Node*>& preorder, vector<Node*>& inorder) {
            return build(preorder, inorder, 0, preorder.size() - 1);
        }
};



void print_preorder(Node *nd) { //Print pre-order
    if (nd == nullptr)
        return;
    cout << "Char: " << nd->val << " Freq: " << nd->freq << endl;
    print_preorder(nd->left);
    print_preorder(nd->right);
}

void print_inorder(Node* nd) { //Print in-order
    if (nd == nullptr)
        return;
    print_inorder(nd->left);
    cout << "Char: " << nd->val << " Freq: " << nd->freq << endl;    
    print_inorder(nd->right);
}

bool get_tree_input(vector<Node*> &pre, vector<Node*> &in) {
    ifstream my_file("arvhuf.txt");
    if (!my_file.is_open()) {
        cerr << "Could not open the file" << endl;
        return false;
    }
    int freq;
    char val, astk;
    vector<Node*> tree_input;

    while (my_file >> val >> astk >> freq >> astk) {
        Node* aux = new Node(freq, val);
        tree_input.push_back(aux);
    }
    my_file.close();

    //First half of input file is in-order
    for (auto it = tree_input.begin(); it < tree_input.begin() + tree_input.size()/2; ++it)
        in.push_back(*it);
    //Second half of input file is pre-order
    for (auto it = tree_input.begin() + tree_input.size()/2; it != tree_input.end(); ++it)
        pre.push_back(*it);

    return true;
}

bool get_text_file(Node* root) {
    ifstream input_file("texto.hfm");
    if (!input_file.is_open()) {
        cerr << "Could not open the file" << endl;
        return false;
    }
    
    ofstream output_file("saida.txt");
    if (!output_file.is_open()) {
        cerr << "Could not open the file" << endl;
        return false;
    }

    char c;
    Node* ptr = root;

    while (input_file >> c) {
        if (ptr->left == nullptr && ptr->right == nullptr) {
            output_file << ptr->val;
            ptr = root;
        }
        if (c == '0')
            ptr = ptr->left;
        if (c == '1')
            ptr = ptr->right;
    }
    
    input_file.close();
    output_file.close();
    return true;
}


int main() {
    
    vector<Node*> pre;
    vector<Node*> in;
    get_tree_input(pre, in);
    
    Tree t;
    t.root = recoverTopology().build_tree(pre, in);
    
    get_text_file(t.root);
    
}


