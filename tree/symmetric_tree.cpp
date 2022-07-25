#include <iostream>
using namespace std; 

// Given a binary tree, check whether it is a mirror of itself
// (ie, symmetric around its center).

// Compare two nodes R and L
// If R == L, compare the two outer (L->L + R->R) and two inner (L->R to R->L)
// Repeat until null is reached

struct TreeNode {
 int val;
 TreeNode* left;
 TreeNode* right;
 TreeNode(int val): val(val), left(nullptr), right(nullptr) {}
};

bool nodes_symmetrical(TreeNode* r, TreeNode * l) {
    if(r == nullptr || l == nullptr)
        return (r == l); 

    if(r->val == l->val) {
        return nodes_symmetrical(l->right, r->left) && nodes_symmetrical(l->left, r->right);
    } else {
        return false;
    }
}

bool is_symmetrical(TreeNode* root) {
    return (root == nullptr) || nodes_symmetrical(root->right, root->left);
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2); 
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(3); 

    bool symmetric = is_symmetrical(root);

    if(symmetric) {
        cout << "tree is symmetric" << endl;
    } else {
        cout << "tree is not symmetric" << endl; 
    }

    return 0;
}