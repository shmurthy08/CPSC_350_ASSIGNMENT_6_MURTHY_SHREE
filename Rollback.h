/*
 * Shree Murthy
 * 2374658
 * shmurthy@chapman.edu
 * CPSC 350-03
 * Assignment 6
 **/
 
//generic rollback file that will function as an undo feature for the project

#ifndef ROLLBACK_H
#define ROLLBACK_H


#include <iostream>
#include <exception>
#include "GenLinkedList.h"

using namespace std;

template <typename T>
class Rollback{
    public:
        Rollback(); //default constructor
        Rollback(int maxSize);
        ~Rollback(); //default destructor

        //core functions
        void push(T data); //push data onto the stack
        T pop(); //pop the first item in the stack

        //helper functions
        T peek(); //peek at the top of the stack and return the value
        int getSize(); //get the size of the stack
        bool isEmpty(); //is the stack empty?
        bool isFull(); //is the array full
       
    private:
        T *myArray; //LinkedList that will be used to build the stack
        int mSize; //size of the stack
        int top; //the top of the stack

};

template <typename T>
/** Default constructor of data type T that will create a new array based stack
 *
 */
Rollback<T>::Rollback(){
    mSize = 128; //size is 0
    top = -1;
    myArray = new T[mSize]; //intialize array of data type T
}


template <typename T>
/**Constructor given a specific size
* param: int maxSize representing the size
*/
Rollback<T>::Rollback(int maxSize){
    mSize = maxSize; //size is 0
    top = -1;
    myArray = new T[mSize]; //intialize array of data type T
}

template <typename T>
/** Destructor
*/
Rollback<T>::~Rollback(){
    delete [] myArray; //delete the array
}

template <typename T>
/** This is the method used to push data onto the stack
 * param: type T data represents the information to be pushed into the stack
 */
void Rollback<T>::push(T data){
    
    if(isFull()){
        for(int i = 0; i < mSize - 1; ++i){
            myArray[i] = myArray[i+1];
        }
        myArray[top] = data;
        return;
    }
    myArray[++top] = data;
}

template <typename T>
/** This method is used to pop the first item in the stack
 * return: type T representing the data removed from the top of the stack
 */
T Rollback<T>::pop(){
   if(isEmpty()){
        throw runtime_error("Stack empty can NOT pop!");
    }
    return myArray[top--];
}


template <typename T>
/** This method lets the user look at the information at the top of the stack without removing it
 * return: type T representing the data at the top
 */
T Rollback<T>::peek(){
    //error check
    if(isEmpty()){
        throw runtime_error("Stack empty can NOT PEEK!");
    }
    return myArray[top];
}


template <typename T>
/** This method shows us the size of the stack
 * return: int representing the size of the stack
 */
int Rollback<T>::getSize(){
    return mSize;
}


template <typename T>
/** returns if the stack is full
* return: bool of stack's size status
*/
bool Rollback<T>::isFull(){
    return (top == mSize - 1);
}

template <typename T>
/** Method to check if the stack is empty
 * return: bool representing if the stack is empty (true) or not (false)
 */
bool Rollback<T>::isEmpty(){
    return (top == -1);
}


#endif