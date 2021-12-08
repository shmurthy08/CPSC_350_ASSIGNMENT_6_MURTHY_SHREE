/*
 * Shree Murthy
 * 2374658
 * shmurthy@chapman.edu
 * CPSC 350-03
 * Assignment 6
 **/

//set up the simulation class
#ifndef SIMULATION_H
#define SIMULATION_H


#include <exception>
#include <iostream>
#include <unistd.h>
#include "GenBST.h"
#include "Student.h"
#include "Faculty.h"
#include "Rollback.h"
#include "FileProcessor.h"
#include <fstream>
#include <sstream>

using namespace std;


class Simulation{
    public:
        Simulation();
        ~Simulation();
        void run();
        void setup(); //read the files if they exist
        void options(); //print all the possible options for the user

        void printStudents(); //print all nodes in the student bst such that ids are in ascending 
        void printFaculty(); //print all nodes in the faculty bst such that ids are in ascending order

        void findStudent(); //find a particular student
        void findFaculty(); //find a particular faculty member

        void getFacultyAdvisor(); //get a student's faculty member
        void getAdvisees(); //get the list of advisees for a faculty member

        void addStudent(); //add a student
        void deleteStudent(); //delete a specific student

        void addFaculty(); //add a faculty member
        void deleteFaculty(); //delete a specfic faculty member

        void changeStudentAdvisor(); //change a student's advisor
        void removeAdvisee(); //remove an advisee

        void rollback(); //the database's undo feature
        void saveAndExit(); //save the data and exit
        
    private:
        GenBST<Student> *masterStudent; //bst of students
        GenBST<Faculty> *masterFaculty; //bst of faculty members
        Rollback<string> *information; //rollback info of students and faculty
        Rollback<unsigned int> *operation; //rollback info of operations
       
};





#endif