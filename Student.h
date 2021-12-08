/*
 * Shree Murthy
 * 2374658
 * shmurthy@chapman.edu
 * CPSC 350-03
 * Assignment 6
 **/

#ifndef STUDENT_H
#define STUDENT_H


#include <iostream>
#include <ostream>
#include <exception>
#include <iomanip>

using namespace std;

//overload operators for comparison
class Student{
    public:
        Student(); //default constructor
        Student(string line); //student object created given a file line
        Student(unsigned int id, string name, string lvl, string major, double gpa, unsigned int advi); //overloaded constructor
        //Student(string fileLine) //given a file line parse it and create a updated student object
        ~Student(); //default destructor
        unsigned int getId(); //get the id of the student
        string getName(); //get the name of the student
        string getLevel(); //get the standing of the student (Fresh, soph, etc)
        string getMajor(); //what is the student's major
        double getGpa(); //what is the student's gpa
        unsigned int getAdvisor(); //returns the id of the student advisor
        void setId(unsigned int i); //set id
        void setName(string name); //set name
        void setLevel(string lvl); //set lvl
        void setMajor(string major); //set major
        void setGpa(double gpa); //set gpa
        void setAdvisorId(unsigned int i); //sets the id of the student's advisor

        //overloaded operators
        bool operator==(Student& right);
        bool operator!=(Student& right);
        bool operator>(Student& right);
        bool operator<(Student& right);
        bool operator<=(Student& right);
        bool operator>=(Student& right);
        friend ostream& operator<<(ostream& s, Student& st);
        friend ostream& operator>>(Student& st, ostream& s); //implement


    private:
        unsigned int studentId; //their unique id
        string studentName; //the name of the member
        string studentMajor; //major of the student
        string studentLevel; //holds the student level (assistant, associate, etc)
        string studentDept; //holds info regarding student's major
        double studentGpa; //holds the student's gpa information
        unsigned int studentAdvisor; // holds the id of their advisor


};






#endif