/*
 * Shree Murthy
 * 2374658
 * shmurthy@chapman.edu
 * CPSC 350-03
 * Assignment 6
 **/

//fileprocessor set up

#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <iostream>
#include <exception>
#include <fstream>
#include <sstream>



using namespace std;

//Class to handle all file processing
class FileProcessor{
    public:
        FileProcessor(); //default constructor
        FileProcessor(string fileInput); //default constructor
        ~FileProcessor(); //default destructor
        bool processInputFile(); //void method that will read from a file
        string truncString(string& s, string delimiter); //truncate a string to remove all commas
        bool validFacLine(string line); //valid faculty line
        bool validStuLine(string line); //valid student line
    private: 
        string fileName; //store the name of the file
};
#endif