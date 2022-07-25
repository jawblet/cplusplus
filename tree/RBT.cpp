/* Rules followed: 
    - Nodes are always red or black. 
    - The root node is always black. 
    - A red node cannot have a red child. 
    - The amount of black nodes from the root to all leaf nodes is always the same.
*/

#include <iostream>
#include <math.h> 
#include <queue>

using namespace std;

#define RED 0
#define BLACK 1

template <class T>
class RBT;

template <class T>
class RBTNode {
    RBTNode<T> *parent, *left, *right;
    T data;
    int color;

public:
    RBTNode(T data)
            : data(data),
              color(RED),
              parent(nullptr),
              left(nullptr),
              right(nullptr) {}
    friend class RBT<T>;
    void prettyPrint(int indent) const;

    template <class T1>
    friend void swapColor(RBTNode<T1> *);
    template <class T1>
    friend int getColor(RBTNode<T1> *);

    int height() const;
};

template <class T>
class RBT {
    RBTNode<T> *root;
    void left_rotation(RBTNode<T> *&point);
    void right_rotation(RBTNode<T> *&point);
    void right_left_rotation(RBTNode<T> *&point);
    void left_right_rotation(RBTNode<T> *&point);

public:
    RBT() : root(nullptr) {}

    void insert(const T &);
    void insert(const T &, RBTNode<T> *&point, RBTNode<T> *parent);
    void rebalance(RBTNode<T> *point);                          // added to rebalance tree
    void check_red_children(RBTNode<T> *&point);                // added to avoid red uncle problem 
    void prettyPrint() const { root->prettyPrint(0); }

    int height() const { return root->height(); }
};

template <class T>
void RBT<T>::right_rotation(RBTNode<T> *&point) {
    RBTNode<T> *new_r_subchild = point;
    RBTNode<T> *new_parent = point->left;

    new_r_subchild->left = new_parent->right;

    if (new_parent->right != nullptr) 
        new_parent->right->parent = new_r_subchild;

    new_parent->parent = new_r_subchild->parent;

    if (new_r_subchild->parent == nullptr) {
        root = new_parent;
    } else {
        RBTNode<T>* great_grandparent = new_r_subchild->parent; 
        if(great_grandparent->right == new_r_subchild) {
            great_grandparent->right = new_parent;
        } else {
            great_grandparent->left = new_parent;
        }
    }

    new_parent->right = new_r_subchild;
    new_r_subchild->parent = new_parent;
}

template <class T>
void RBT<T>::left_rotation(RBTNode<T> *&point) {
    RBTNode<T>* new_l_subchild = point;        
    RBTNode<T>* new_parent = point->right;

    new_l_subchild->right = new_parent->left;

    // move P's left child to G if it exists 
    if (new_parent->left != nullptr) 
        new_parent->left->parent = new_l_subchild;

    // replace G with P in the tree 
    new_parent->parent = new_l_subchild->parent;

    // point G's parent at P 
    if (new_l_subchild->parent == nullptr) {
        root = new_parent;
    } else {
        RBTNode<T>* great_grandparent = new_l_subchild->parent; 
        if(great_grandparent->right == new_l_subchild) {  
            great_grandparent->right = new_parent;
        } else {
            great_grandparent->left = new_parent;
        }
    }

    // point P <> G 
    new_parent->left = new_l_subchild;
    new_l_subchild->parent = new_parent;
}

template <class T>
void RBT<T>::right_left_rotation(RBTNode<T> *&point) {
    right_rotation(point->right);
    left_rotation(point);
}

template <class T>
void RBT<T>::left_right_rotation(RBTNode<T> *&point) {
    left_rotation(point->left);
    right_rotation(point);
}

template <class T>
void RBT<T>::insert(const T &toInsert, RBTNode<T> *&point, RBTNode<T> *parent) {
    if (point == nullptr) {                 // leaf location is found so insert node
        point = new RBTNode<T>(toInsert);   // modifies the pointer itself since *point
                                            // is passed by reference

        point->parent = parent;
        RBTNode<T> *curr_node = point; 

        // TODO: ADD RBT RULES HERE
        // if root's subtrees differ in height by > 1, balance 
        if(curr_node->parent != nullptr && curr_node->parent->parent != nullptr)
            rebalance(curr_node);
     
        root->color = BLACK;           
    } else if (toInsert < point->data) { 
        check_red_children(point);
        insert(toInsert, point->left, point);
    } else { 
        check_red_children(point);
        insert(toInsert, point->right, point);
    }
}

template <class T>
void RBT<T>::insert(const T &toInsert) {
    insert(toInsert, root, nullptr);
}

template <class T>
void RBT<T>::rebalance(RBTNode<T> *point) {
    RBTNode<T>* p_parent = point->parent; 
    RBTNode<T>* grandparent = p_parent->parent; 

    // while parent is red 
    while (getColor(p_parent) == RED) {
        // check if parent is R or L 
        RBTNode<T>* uncle = grandparent->right; 

        if(grandparent->right == p_parent)
            uncle = grandparent->left; 
       
        if(getColor(uncle) == RED) {
            cout << "ERROR! Impossible to continue balancing. Ending program." << endl;
            exit(1);
        }

        // if parent is an L or R child
        if (p_parent == grandparent->left) {
            // L -> R
            if (point == p_parent->right) {
                left_right_rotation(point);
                point->color = BLACK;
                grandparent->color = RED;
            } else {
            // L -> L
                right_rotation(grandparent);
                p_parent->color = BLACK;    // make parent black
                grandparent->color = RED;
            }
           
        } else {
            // R -> L
            if (point == p_parent->left) {
                right_left_rotation(point);
                point->color = BLACK;
                grandparent->color = RED;
            } else {
            // R -> R 
                left_rotation(grandparent);
                p_parent->color = BLACK;    // make parent black
                grandparent->color = RED;
            }   
        }
    }
}

template <class T> 
void RBT<T>::check_red_children(RBTNode<T> *&point) {
    // if node is black + has 2 red children -> swap colors to avoid red uncle 
    if(getColor(point) == BLACK) {
        if(getColor(point->right) == RED && getColor(point->left) == RED) {
            // if grandparent is also red, rebalance 
            if(getColor(point->parent) == RED) {
                rebalance(point);
            }
            swapColor(point);
            swapColor(point->right);
            swapColor(point->left); 
        }
    }
}

// NOTE: DO NOT MODIFY THE MAIN FUNCTION BELOW
int main() {
    RBT<int> b;
    int count = 10;
    for (int i = 0; i < count; i++) {
        b.insert(i);
    }

    b.prettyPrint();
    /* EXPECTED OUTPUT:
                                                                    Data: 9
                                                                    COLOR: RED
                                                    Data: 8
                                                    COLOR: BLACK
                                    Data: 7
                                    COLOR: RED
                                                    Data: 6
                                                    COLOR: BLACK
                    Data: 5
                    COLOR: BLACK
                                    Data: 4
                                    COLOR: BLACK
    Data: 3
    COLOR: BLACK
                                    Data: 2
                                    COLOR: BLACK
                    Data: 1
                    COLOR: BLACK
                                    Data: 0
                                    COLOR: BLACK
    */

    // TEST
    // the below tests the validity of the height of the RBT
    // if the assertion fails, then your tree does not properly self-balance
    int height = b.height();
    assert(height <= 2 * log2(count));
}

template <class T>
int RBTNode<T>::height() const {
    int left_h = 0;
    if (left != nullptr) {
        left_h = left->height();
    }
    int right_h = 0;
    if (right != nullptr) {
        right_h = right->height();
    }
    return 1 + max(left_h, right_h);
}

template <class T>
void RBTNode<T>::prettyPrint(int indent) const {
    if (right != nullptr) {
        right->prettyPrint(indent + 1);
    }
    int margin = indent * 2;
    for (int i = 0; i < margin; ++i) {
        cout << '\t';
    }
    cout << "DATA: " << data << endl;
    for (int i = 0; i < margin; ++i) {
        cout << '\t';
    }
    cout << "COLOR: " << (color == RED ? "RED" : "BLACK") << endl;
    if (left != nullptr) {
        left->prettyPrint(indent + 1);
    }
}

// swapColor swaps the color from red to black and vice versa
int swapColor(int c) {
    return (c==0)?1:0;
}

template <class T>
void swapColor(RBTNode<T> *node) {
    if (node != nullptr) {
        node->color = swapColor(node->color);
    }
}

template <class T>
int getColor(RBTNode<T> *node) {
    if (node != nullptr) {
        return node->color;
    }
    return BLACK;
}