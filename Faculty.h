/*
 * Shree Murthy
 * 2374658
 * shmurthy@chapman.edu
 * CPSC 350-03
 * Assignment 6
 **/


//header file for a faculty object
#ifndef FACULTY_H
#define FACULTY_H


#include <iostream>
#include "GenLinkedList.h"
#include "Student.h"
#include <ostream>
#include "FileProcessor.h"

using namespace std;

//overload operators for comparison
class Faculty{
    public:
        Faculty(); //default constructor
        Faculty(unsigned int id, string name, string lvl, string dept);
        Faculty(string line); // takes an entire string from the file
        ~Faculty(); //default destructor
        void printAdvisees(); //print all the advisees for an advisor
        unsigned int getId(); //return the id of the advisor
        void setId(unsigned int id); //set the id of the advisor
        string getName(); //name of the advisor
        void setName(string name); //set the name of the advisor
        string getLevel(); //level of the advisor
        void setLevel(string lvl); //set the level of the advisor
        string getDept(); //get the department of the advisor
        void setDept(string dept); //set the department of the advisor
        void addAdvisee(Student s); //add an advisee to the faculty's linkedlist
        void removeAdvisee(Student s); //remove an advisee
        GenLinkedList<unsigned int> returnList(); //return a linkedlist of all advisee members
        string getAdviseeString(); //string of all the advisees in one line

        //overloading operators
        bool operator==(Faculty& right);
        bool operator!=(Faculty& right);
        bool operator>(Faculty& right);
        bool operator<(Faculty& right);
        bool operator<=(Faculty& right);
        bool operator>=(Faculty& right);
        friend ostream& operator<<(ostream& s, Faculty& f);
        friend ostream& operator>>(Faculty& f, ostream& s);

    private:
        unsigned int facultyId; //their unique id
        string facultyName; //the name of the member
        string facultyLevel; //holds the faculty level (assistant, associate, etc)
        string facultyDept; //holds info regarding faculty's department
        GenLinkedList<unsigned int> *studentInfo; //list of student information


};






#endif