/*
 * Shree Murthy
 * 2374658
 * shmurthy@chapman.edu
 * CPSC 350-03
 * Assignment 6
 **/


//a General Binary Search Tree

#ifndef GENBST_H
#define GENBST_H
#include <iostream>
#include "GenLinkedList.h"

using namespace std;

template <class T>
class TreeNode{
    public: 
        TreeNode(); //create default tree node
        TreeNode(T k); //create tree node with key k
        virtual ~TreeNode(); //destroy tree node

        T key; //key
        TreeNode<T> *left; //point to the node on the left
        TreeNode<T> *right; //point to the node on the right
};


template <class T>
/** Default constructor
*/
TreeNode<T>::TreeNode(){
    key = NULL;
    left = NULL;
    right = NULL;

}

template <class T>
/** Overloaded constructor
 * param: T k representing the key of type k
 */
TreeNode<T>::TreeNode(T k){
    key = k;
    left = NULL;
    right = NULL;

}

template <class T>
/** default destructor
 */
TreeNode<T>::~TreeNode(){
    left = NULL;
    right = NULL;
    
}


template <class T>
class GenBST{
    public:
        GenBST(); //construct an empty tree
        virtual ~GenBST(); //destructor

        void insert(T value); //insert a node to the key
        bool contains(T value); //does the tree contain a node
        T* returnData(T value); //return the data if the tree contains a data
        bool deleteNode(T k); //delete a node given it's key
        bool isEmpty(); //is the tree empty
        unsigned int size(); //return size of the BST
        T* getMin(); //smallest value in the tree
        T* getMax(); //largest value in the tree
        TreeNode<T> *getSuccessor(TreeNode<T> *d); //helper method to find a successor for the delete method
        void printNodes(); //print all the nodes in the array
        GenLinkedList<T> preorderNodes(); //return a string of all the preorder nodes
        void prePrint(TreeNode<T> *node);
        void recPrint(TreeNode<T> *node); //recursively print all nodes from a given point


    private:
        TreeNode<T> *root; //the first node in the tree
        GenLinkedList<T> list;
        unsigned int mSize;
        void helperDelete(TreeNode<T> *n); //helper function for the destructor
};


template <class T>
GenBST<T>::GenBST(){

}

template <class T>
/** default destructor
*/
GenBST<T>::~GenBST(){
    //start the deleting process from the root
    helperDelete(root);
}

template <class T>
/** Conduct a recursive delete of all the nodes in the BST
 * param: TreeNode<T> *n representing the node to start the delete process from
 */
void GenBST<T>::helperDelete(TreeNode<T> *n){
    if(n != NULL){
        if(n->left != NULL){
            helperDelete(n->left);
        }
        if(n->right != NULL){
            helperDelete(n->right);
        }
        delete n;
    }
}



template <class T>
/** Print all the nodes in the tree
* param: TreeNode representing where to start from
*/
void GenBST<T>::recPrint(TreeNode<T> *node){
    if(node == NULL){
         return;
    }
    //in-order traversal
    recPrint(node->left);
    cout << node->key;
    recPrint(node->right);
}


template <class T>
/** print all nodes recusively (in order traversal)
*/
void GenBST<T>::printNodes(){
    recPrint(root);
}

template <class T>
/** Return a linkedlist of all the preoder nodes
* return: GenLinkedList of all the nodes in preorder
*/
GenLinkedList<T> GenBST<T>::preorderNodes(){
    prePrint(root);
    return list;
}

template <class T>
/** Print nodes in a preorder format
* param: TreeNode representing the node to start from
*/
void GenBST<T>::prePrint(TreeNode<T> *node){
    if(node == NULL){
        return;
    }
    //preorder traversal
    list.insertHead(node->key);
    prePrint(node->left);
    prePrint(node->right);
}

template <class T>
bool GenBST<T>::isEmpty(){
    return (root == NULL);
}

template <class T>
/** get the lowest number in the tree
 * return: a pointer of the minimum value
 */
T* GenBST<T>::getMin(){
    if(isEmpty()){
        throw runtime_error("EMPTY TREE");
    }
    TreeNode<T> *curr = root;
    
    while(curr->left != NULL){
        curr = curr->left;
    }

    return &(curr->key);


}

template <class T>
/** get the largest value in the tree
 * return: a pointer of the largest value
 */
T* GenBST<T>::getMax(){
   if(isEmpty()){
        throw runtime_error("EMPTY TREE");
    }
    TreeNode<T> *curr = root;
    
    while(curr->right != NULL){
        curr = curr->right;
    }

    return &(curr->key);
}

template <class T>
/** Insert a node into the tree
 * param: type t representing the value to be inserted 
 */
void GenBST<T>::insert(T value){
    TreeNode<T> *node = new TreeNode<T>(value);
    if(isEmpty()){
        root = node;

    }
    else{
        TreeNode<T> *curr = root;
        TreeNode<T> *parent = NULL;

        while(true){
            parent = curr;
            if(value < curr->key){
                curr = curr->left;
                if(curr == NULL){
                    //found the insertion point
                    parent->left = node;
                    break;
                }
            }
            else{
                curr = curr->right;
                if(curr == NULL){
                    parent->right = node;
                    break;
                }
            }
        }
    }
    ++mSize;
}

template <class T>
/** Parse the tree to see if it contains a specfic node
 * param: Type t representing the value to fine
 * return: bool true or false if the tree contains the value
 */
bool GenBST<T>::contains(T value){
    if(isEmpty()){
        return false;
    }
    TreeNode<T> *curr = root;
    while(curr->key != value){
        if(value <  curr->key){
            curr = curr->left;
        }
        else{
            curr = curr->right;
        }
        if(curr == NULL){
            return false;
        }
    }
    return true;
}

/** Check the bst to see if it has a value and then return that data if it is found
 * param: T value representing the value to check for
 * return: type T represeting the data that is returned
 */
template <class T>
T* GenBST<T>::returnData(T value){
    TreeNode<T> *curr = root;
    if(contains(value) == false){
        return NULL;
    }
    else{
        
        while(curr->key != value){
            if(value <  curr->key){
                curr = curr->left;
            }
            else{
                curr = curr->right;
            }
            if(curr == NULL){
                return NULL;
            }
        }
    }
    return &(curr->key);
}
template <class T>
/** Delete a specific node from the tree
 * param: type t k repsenting the value that should be deleted
 * return: bool true or false depending on if the node was deleted
 */
bool GenBST<T>::deleteNode(T k){
    if(isEmpty()){
        return false;
    }
    TreeNode<T> *curr = root;
    TreeNode<T> *parent = root;
    bool isLeft = true;

    while(curr->key != k){
        parent = curr;
        if(k < curr->key){
            isLeft = true;
            curr = curr->left;
        }
        else{
            isLeft = false;
            curr = curr->right;
        }
        if(curr == NULL)
            return false;
    }
    //we found the node now onward to deleting
    //no children, node to be deleted is a leaf
    if(curr->left == NULL && curr->right == NULL){
        if(curr == root){
            root = NULL;
        }
        else if(isLeft){
            parent->left = NULL;

        }
        else{
            parent->right = NULL;
        }
    }
    //only one child that is on the right
    else if(curr->right == NULL){

        if(curr == root){
            root = curr->left;
        }
        else if(isLeft){
            parent->left = curr->left;
        }
        else{
            parent->right = curr->left;
        }
    }
    //only one child that is on the left
    else if(curr->left == NULL){
        if(curr == root){
            root = curr->right;
        }
        else if(isLeft){
            parent->left = curr->right;
        }
        else{
            parent->right = curr->right;
        }
    }
    else{ //two children
        TreeNode<T> *successor = getSuccessor(curr);
        if(curr == root){
            root = successor;
        }        
        else if(isLeft){
            parent->left = successor;
        }
        else{
            parent->right = successor;
        }
        successor->left = curr->left;
        curr->left = NULL;
        curr->right = NULL;

    }
    delete curr;
    --mSize;
    return true;
}

template <class T>
/** Get the successor of the node that will replace the node that is going to be deleted
 * param: TreeNode<T> *d representing the node where we start from 
 * return: TreeNode reprsenting the node that will be successor
 */
TreeNode<T> *GenBST<T>::getSuccessor(TreeNode<T>  *d){
    TreeNode<T> *sp =  d;
    TreeNode<T> *successor = d;
    TreeNode<T> *current = d->right;
    while(current != NULL){
        sp = successor;
        successor = current;
        current = current->left;
    }
    //we found successorbut we need to check if the successor is a descendant of the right child
    if(successor != d->right){
        sp->left = successor->right;
        successor->right = d->right;
    }

    return successor;
}

template <class T>
/** FInd and return the size of the bst
* return: unsigned int of the size
*/
unsigned int GenBST<T>::size(){
    return mSize;
}

#endif