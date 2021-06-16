#include "huffman.h"
#include <vector>

using namespace std;

class recoverTopology {
    public:
        Node* build_tree(vector<Node*>& preorder, vector<Node*>& inorder) {
            Node *root;
            root = build(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
            return root;
        }

        Node* build(vector<Node*> &preorder, vector<Node*> &inorder, int l1, int r1, int l2, int r2){
            if(l1 > r1 || l2 > r2) 
                return nullptr;
            
            char value = preorder[l1] -> val;
            int frequency = preorder[l1] -> freq;
            
            Node *root = new Node(frequency, value);
            root -> val = value;

            int i = l2;
            while(i <= r2){
                if(inorder[i] -> val == value) 
                    break;
                    i++;
            }
            
            int j = l1 + i - l2;
            
            root -> left = build(preorder, inorder, l1 + 1, j, l2, i - 1);
            root -> right = build(preorder, inorder, j + 1, r1, i + 1, r2);
            
            return root;
        }
};

void dfs(Node *nd) { //Print pre-order
    if (nd == nullptr)
        return;
    cout << "Char: " << nd -> val << " Freq: " << nd -> freq << endl;
    dfs(nd -> left);
    dfs(nd -> right);
}

void sim(Node* nd) { //Print in-order
    if (nd == nullptr)
        return;
    sim(nd -> left);
    sim(nd -> right);
    cout << "Char: " << nd -> val << " Freq: " << nd -> freq << endl;    
}



int main() {
    
    vector<Node*> tree_input;
    vector<Node*> pre;
    vector<Node*> in;
        
    ifstream my_file("arvhuf.txt");
    if (!my_file.is_open()) {
        cerr << "Could not open the file - '"
              << "'" << endl;
        return EXIT_FAILURE;
    }
    int freq;
    char val, astk;
    
    while (my_file >> val >> astk >> freq >> astk) {
        Node* aux = new Node(freq, val);
        tree_input.push_back(aux);
    }
    my_file.close();

    
    //First half of input file is in-order
    for (auto it = tree_input.begin(); it < tree_input.begin() + tree_input.size()/2; ++it)
        in.push_back(*it);
    
    //Second half of input fike is pre-order
    for (auto it = tree_input.begin() + tree_input.size()/2; it != tree_input.end(); ++it)
        pre.push_back(*it);
    
    /*
    cout << "PRE: " << endl;
    for (auto x : pre){ 
        cout << "val: " << x -> val << endl;
        cout << "freq: " << x -> freq << endl;
    }
    cout << endl << "IN: " << endl;
    for (auto x : in){
        cout << "val: " << x -> val << endl;
        cout << "freq: "<< x -> freq << endl;
    }
    */

    Tree t;
    t.root = recoverTopology().build_tree(pre, in);
    
    dfs(t.root);

}
