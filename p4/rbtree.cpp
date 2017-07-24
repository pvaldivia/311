/* @filename rbtree.cpp 
 *
 * @brief Stores data in a RBTree and implements different
 * functions with the data
 *
 * @author Pedro Valdivia and Judy Challinger
 * @data 11/9/16
 */
#include <iostream>
#include <iomanip>
#include "rbtree.h"

using std::cout;
using std::setw;
using std::endl;
/*
 * RBTree::RBTree Constructor
 *
 * Initializes all member variables
 * @param nil Node acting as a null pointer
 * @param root Node pointer pointing to root of tree
 */
RBTree::RBTree()
{
    nil = new Node();
    root = nil;
}
/*
 * RBTree::RBTree Destructor
 *
 * Deallocates all allocated memory using a help function
 * @param nil Node acting as a null pointer
 */
RBTree::~RBTree()
{
    delete_tree(root);
    delete nil;
}
/*
 * RBTree::delete_tree
 *
 * A recursive function that goes through the whole tree and
 * deallocates each node
 *
 * @param cur_root Node pointer used to recurse entire tree
 *
 */

void RBTree::delete_tree(Node*& cur_root)
{
    if (cur_root == nil)
    return;

    delete_tree(cur_root->left);
    delete_tree(cur_root->right);
    delete cur_root;

    cur_root = nil;
}
/*
 * RBTree::Node::Node Constructor
 *
 * Initializes few member variables
 * @param parent Node pointer 
 * @param color Holds a character to describe the Node color 
 *
 */

RBTree::Node::Node()
{
    parent = NULL;
    color = 'B';
}
/*
 * RBTree::Node::Node Constructor
 *
 * Initializes all member variables
 * @param key_new String holding key data
 * @param value_new String holding satellite data
 * @param right Node pointer
 * @param left Node pointer
 */

RBTree::Node::Node(const string& key_new, const string& value_new)
{
    parent = NULL;
    left = NULL;
    right = NULL;
    color = '0';
    
    key = new string(key_new);
    value = new string(value_new);
}
/*
 * RBTree::Node::~Node Desstructor
 *
 * Deallocates all member variables
 * @parm key String Pointer
 * @param value String Pointer
 *
 */

RBTree::Node::~Node()
{
    delete key;
    delete value;
}
/*
 * RBTree::rbPrintTree
 *
 * Public member function used to call RBTree::reverseInOrderPrint
 * and acces root of tree
 *
 */

void RBTree::rbPrintTree()
{
    reverseInOrderPrint(root,0);
}
/*
 * RBTree::rbInsert
 *
 * Public member function used to call private member function
 * RBTree::rbInsert. Also allocates a new node with passed in key 
 * and value
 * @param key String holding data
 * @param value String holding data
 *
 */

void RBTree::rbInsert(const string& key, const string& value)
{
    Node* item = new Node(key,value);
    rbInsert(item);
}
/*
 * RBTree::rbInsert
 *
 * Inserts a new allocated node into the tree
 *
 * @param item Node pointer
 *
 */

void RBTree::rbInsert(Node* item)
{
    Node* y = nil;
    Node* x = root;
    while (x != nil)
    {
        y = x;
        if (*(item->key) < *(x->key))
        x = x->left;
        else
        x = x->right;
    }

    item->parent = y;
    if (y == nil)
    root = item;
    else if (*(item->key) < *(y->key))
    y->left = item;
    else
    y->right = item;

    item->left = nil;
    item->right = nil;
    item->color = 'R';
    rbInsertFixup(item);
}
/*
 * RBTree::rbInsertFixup
 *
 * Maintain the 5 properties of the RBTree
 * @param item Node Pointer
 *
 */

void RBTree::rbInsertFixup(Node* item)
{
    while (item->parent->color == 'R')
    {
        if (item->parent == item->parent->parent->left)
        {
            Node* y = item->parent->parent->right;
            if (y->color == 'R')
            {
                item->parent->color = 'B';
                y->color = 'B';
                item->parent->parent->color = 'R';
                item = item->parent->parent;
            }
            else 
            {
                if (item == item->parent->right)
                {
                    item = item->parent;
                    leftRotate(item);
                }
                item->parent->color = 'B';
                item->parent->parent->color = 'R';
                rightRotate(item->parent->parent);
            }
        }
        else 
        {
            Node* y = item->parent->parent->left;
            if (y->color == 'R')
            {
                item->parent->color = 'B';
                y->color = 'B';
                item->parent->parent->color = 'R';
                item = item->parent->parent;
            }
            else 
            {
                if (item == item->parent->left)
                {
                    item = item->parent;
                    rightRotate(item);
                }
                item->parent->color = 'B';
                item->parent->parent->color = 'R';
                leftRotate(item->parent->parent);
            }

        }
    }
    root->color = 'B';
}
/*
 * RBTree::leftRotate
 *
 * Used to maintain the BST property of being balanced
 * Rotates the tree at a specified Node. Specified by 
 * item
 * @param item Node Pointer
 *
 */

void RBTree::leftRotate(Node* item)
{
    Node *y = item->right;
    item->right = y->left;
    if (y->left != nil)
    y->left->parent = item;

    y->parent = item->parent;
    if (item->parent == nil)
    root = y;
    else if (item == item->parent->left)
    item->parent->left = y;
    else 
    item->parent->right = y;

    y->left = item;
    item->parent = y;
}
/*
 * RBTree::rightRotate
 *
 * Used to maintain the BST property of being balanced
 * Rotates the tree at a specified Node. Specified by 
 * item
 * @param item Node Pointer
 *
 */
void RBTree::rightRotate(Node* item)
{
    Node *y = item->left;
    item->left = y->right;
    if (y->right != nil)
    y->right->parent = item;

    y->parent = item->parent;
    if (item->parent == nil)
    root = y;
    else if (item == item->parent->right)
    item->parent->right = y;
    else 
    item->parent->left = y;

    y->right = item;
    item->parent = y;
    
}
/*
 * RBTree::rbDelete
 * 
 * public member function that finds all nodes to be deleted
 * with RBTree::rbFind and deletes all matching nodes with 
 * RBTree::rbDelete
 * @param key String holding key data 
 * @param value String holding Satellite Data
 */

void RBTree::rbDelete(const string& key, const string& value)
{
    int numToDelete = 0;
    Node* nodeToDelete;
    vector <const string*> values = rbFind(key);
    for (unsigned int i = 0; i < values.size(); i++)
    {
        if (*(values[i]) == value)
        numToDelete++;
    }

    while (numToDelete > 0)
    {
        Node* myKey = rbTreeSearch(root,key);
        Node* pred_keep;
        if (myKey != nil)
        {
            Node* pred = rbTreePredecessor(myKey);
            Node* succ = rbTreeSuccessor(myKey);
            while (*(pred->key) == key)
            {   
                while (pred->parent != nil && *(pred->parent->key) == key && pred == pred->parent->right)
                pred = pred->parent;

                if (pred->left != nil)
                {
                    pred_keep = pred;
                    pred = rbTreePredecessor(pred);
                    if (*(pred->key) != key)
                    {
                        pred = pred_keep;
                        break;
                    }
                }
                else 
                break;
            }
            if (*(pred->key) == key)
            succ = pred;
            else
            succ = myKey;

            while (*(succ->key) == key)
            {
                if (root == succ && succ->left == nil && succ->right == nil)
                {
                    if (*(succ->value) == value)
                    rbDelete(succ);
                    numToDelete--;
                    break;
                }
                if (root == succ && succ->left != nil && succ->right == nil)
                {
                    if (*(succ->value) == value)
                    rbDelete(succ);
                    numToDelete--;
                    break;
                }
                else if (succ->right == nil)
                {
                    nodeToDelete = succ;
                    if (succ == succ->parent->left)
                    succ = succ->parent;
                    else
                    {
                        if (succ->parent == root)
                        {
                            if (*(succ->value) == value)
                            rbDelete(succ);
                            numToDelete--;
                            break;
                        }

                        while (succ == succ->parent->right)
                        {   
                            succ = succ->parent;
                            if (succ->parent == nil)
                            break;
                        }
                        if (succ->parent != nil) 
                        succ = succ->parent;
                    }
                    if (*(nodeToDelete->value) == value)
                    {
                        rbDelete(nodeToDelete);
                        numToDelete--;
                        break;
                    }
                }
                else if (succ->right != nil && succ->left != nil)
                {
                    if (*(succ->value) == value)
                    {
                        rbDelete(succ);
                        numToDelete--;
                        break;
                    }
                    else succ = rbTreeSuccessor(succ);
                }
                else if (succ->right != nil && succ->left == nil)
                {
                    if (*(succ->value) == value)
                    {
                        rbDelete(succ);
                        numToDelete--;
                        break;
                    }
                    else succ = rbTreeSuccessor(succ);
                }
            }
        }
    }
}
/*
 * RBTree::rbDelete
 *
 * Delete specified Node in tree
 * @param item Node Pointer
 *
 */

void RBTree::rbDelete(Node* item)
{
    Node* x;
    Node* y = item;
    char yoc = y->color;
    if (item->left == nil)
    {
        x = item->right;
        rbTransplant(item,item->right);
    }
    else if (item->right == nil)
    {
        x = item->left;
        rbTransplant(item,item->left);
    }
    else
    {
        y = rbTreeMaximum(item->left);
        yoc = y->color;
        x = y->left;
        if (y->parent == item)
        x->parent = y;
        else
        {
            rbTransplant(y,y->left);
            y->left = item->left;
            y->left->parent = y;
        }
        rbTransplant(item,y);
        y->right = item->right;
        y->right->parent = y;
        y->color = item->color;
    }
    delete item;
    if (yoc == 'B')
    rbDeleteFixup(x);
}
/*
 * RBTree::rbDeleteFixup
 *
 * Maintains the 5 RBTree properties once a node is deleted
 * @param item Node Pointer
 *
 */

void RBTree::rbDeleteFixup(Node* item)
{
    Node* w;
    while (item != root && item->color == 'B')
    {
        if (item == item->parent->left)
        {
            w = item->parent->right;
            if (w->color == 'R')
            {
                w->color = 'B';
                item->parent->color = 'R';
                leftRotate(item->parent);
                w = item->parent->right;
            }
            if (w->left->color == 'B' && w->right->color == 'B')
            {
                w->color = 'R';
                item = item->parent;
            }
            else
            {
                if (w->right->color == 'B')
                {
                    w->left->color = 'B';
                    w->color = 'R';
                    rightRotate(w);
                    w = item->parent->right;
                }
                w->color = item->parent->color;
                item->parent->color = 'B';
                w->right->color = 'B';
                leftRotate(item->parent);
                item = root;
            }
        }
        else
        {
            w = item->parent->left;
            if (w->color == 'R')
            {
                w->color = 'B';
                item->parent->color = 'R';
                rightRotate(item->parent);
                w = item->parent->left;
            }
            if (w->right->color == 'B' && w->left->color == 'B')
            {
                w->color = 'R';
                item = item->parent;
            }
            else
            {
                if (w->left->color == 'B')
                {
                    w->right->color = 'B';
                    w->color = 'R';
                    leftRotate(w);
                    w = item->parent->left;
                }
                w->color = item->parent->color;
                item->parent->color = 'B';
                w->left->color = 'B';
                rightRotate(item->parent);
                item = root;
            }
            
        }
    }
    item->color = 'B';

}
/*
 * RBTree::rbTransplant
 *
 * Takes in two Node pointer and prepares to swap their location in tree
 * @param u Node Pointer
 * @param v Node Pointer
 */
void RBTree::rbTransplant(Node* u,Node* v)
{
    if (u->parent == nil)
    root = v;
    else if (u == u->parent->left)
    u->parent->left = v;
    else
    u->parent->right = v;
    v->parent = u->parent;
}
/*
 * RBTree::rbTreeMinimum
 *
 * find the minimum key value of right subtree of the passed in node
 * @param min Node Pointer
 * 
 * @return Node Pointer 
 */

RBTree::Node* RBTree::rbTreeMinimum(Node* min)
{
    if (min == nil)
    return nil;

    while (min->left != nil)
    {
        min = min->left;
    }
    return min;

}
/*
 * RBTree::rbTreeMinimum
 *
 * Finds the maximum key value of left subtree of the passed in node
 * @param max Node Pointer
 *
 * @return Node pointer
 */

RBTree::Node* RBTree::rbTreeMaximum(Node* max)
{
    if (max == nil)
    return nil;

    while (max->right != nil)
    {
        max = max->right;
    }
    return max;

}
/*
 * RBTree::rbFind
 *
 * Traverses through the tree and pushes matching keys into a vector
 * @param key String holding key data
 *
 * @return a vector holding const string pointer
 *
 */

vector <const string*> RBTree::rbFind(const string& key)
{
    vector<const string*> values;
    Node* myKey = rbTreeSearch(root,key);
    Node* pred_keep;
    if (myKey != nil)
    {
        Node* pred = rbTreePredecessor(myKey);
        Node* succ = rbTreeSuccessor(myKey);
        while (*(pred->key) == key)
        {   
            while (pred->parent != nil && *(pred->parent->key) == key && pred == pred->parent->right)
            pred = pred->parent;

            if (pred->left != nil)
            {
                pred_keep = pred;
                pred = rbTreePredecessor(pred);
                if (*(pred->key) != key)
                {
                    pred = pred_keep;
                    break;
                }
            }
            else 
            break;
        }
        if (*(pred->key) == key)
        succ = pred;
        else
        succ = myKey;

        while (*(succ->key) == key)
        {
            if (root == succ && succ->left == nil && succ->right == nil)
            {
                values.push_back(succ->value);
                break;
            }
            if (root == succ && succ->left != nil && succ->right == nil)
            {
                values.push_back(succ->value);
                break;
            }
            else if (succ->right == nil)
            {
                values.push_back(succ->value);
                if (succ == succ->parent->left)
                succ = succ->parent;
                else
                {
                    if (succ->parent == root)
                    break;

                    while (succ == succ->parent->right)
                    {   
                        succ = succ->parent;
                        if (succ->parent == nil)
                        break;
                    }
                    if (succ->parent != nil)
                    succ = succ->parent;
                    else 
                    break;
                }
            }
            else if (succ->right != nil && succ->left != nil)
            {
                values.push_back(succ->value);
                succ = rbTreeSuccessor(succ);
            }
            else if (succ->right != nil && succ->left == nil)
            {
                values.push_back(succ->value);
                succ = rbTreeSuccessor(succ);
            }
        }
    }

    return values;
}
/*
 * RBTree::rbTreePredecessor
 *
 * finds the max key value of left subtree
 * @param cur_key Node Pointer
 *
 * @returns Node Pointer holding max key value 
 */
RBTree::Node* RBTree::rbTreePredecessor(Node* cur_key)
{
    if (cur_key == nil)
    return nil;

    if (cur_key->left != nil)
    {
        cur_key = cur_key->left;
        while (cur_key->right != nil)
        {
            cur_key = cur_key->right;
        }
    }
    return cur_key;
}
/*
 * RBTree::rbTreeSuccessor
 *
 * Finds the min key value of right subtree
 * @param cur_key Node Pointer
 *
 * @return Node Pointer holding min key value
 *
 */

RBTree::Node* RBTree::rbTreeSuccessor(Node* cur_key)
{
    if (cur_key == nil)
    return nil;

    if (cur_key->right != nil)
    {
        cur_key = cur_key->right;
        while (cur_key->left != nil)
        {
            cur_key = cur_key->left;
        }
    }
    return cur_key;
}
/*
 * RBTree::rbTreeSearch
 *
 * traverses through the tree to find first occurance of a matching key value
 * 
 * @param cur_root Node Pointer
 * @param key String holding key data
 *
 * @return Node pointer holding matching key value if found
 *
 */

RBTree::Node* RBTree::rbTreeSearch(Node* cur_root, const string& key)
{
    if (cur_root == nil)
    return cur_root;

    Node* cur;

    if (*(cur_root->key) == key)
    return cur_root;
    else if (*(cur_root->key) < key)
    cur = rbTreeSearch(cur_root->right,key);
    else
    cur = rbTreeSearch(cur_root->left,key);

    return cur;
}

/*
 * RBTree::reverseInOrderPrint
 *
 * Prints the tree, sideways
 * @param x Node Pointer
 * @param depth Integer holding how far to print each node
 *
 */
void RBTree::reverseInOrderPrint(Node *x, int depth) {
   if ( x != nil ) {
      reverseInOrderPrint(x->right, depth+1);
      cout << setw(depth*4+4) << x->color << " ";
      cout << *(x->key) << " " << *(x->value) << endl;
      reverseInOrderPrint(x->left, depth+1);
   }
}
