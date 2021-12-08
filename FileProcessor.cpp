/*
 * Shree Murthy
 * 2374658
 * shmurthy@chapman.edu
 * CPSC 350-03
 * Assignment 6
 **/

//process the facultyTable and studentTable files and check if they are valid files as well as have methods that check if a string is a valid string
#include "FileProcessor.h"




FileProcessor::FileProcessor(){

}

/** Default constructor
 */
FileProcessor::FileProcessor(string fileInput){
    fileName = fileInput;
} 


/** Default destructor
 */
FileProcessor::~FileProcessor(){

}


/** This will process the user's fileName file check if it exists
 * return: bool if the fileName file was found
 */
bool FileProcessor::processInputFile(){
    
    // //Input file
    ifstream inFacFile;
    inFacFile.open("facultyTable");
    ifstream inStuFile;
    inStuFile.open("studentTable");
   
    //Check if the fileName file is open to be read
    if(inFacFile.is_open()){
        cout << "FACULTY FILE EXISTS" << endl;
        //close the fileName file to avoid memory issues
        inFacFile.close();
        //close the output file to avoid memory issues
        
    }
    //if the file cannot be opened output this error
    else{
        cout << "FACULTY FILE EXISTS" << endl;

        return false; //faculty file takes precedence due to the student advisee list therefore if it doesn't exist then the method can return false
    }   

    //check if the file is open to be read
    if(inStuFile.is_open()){
        cout << "STUDENT FILE EXISTS" << endl;
        //close it to avoid memory issues
        inStuFile.close();
    }else{
        cout << "FACULTY FILE EXISTS" << endl;
        //return false if it cannot be opened
        return false;
    }
    return true;
}



/** Truncate a string given two params and return everything before the delimiter
 * param: string& s the string to be manipulated and string delimiter representing the spot where we cut off the string
 * return string representing everything before the delimiter
 */
string FileProcessor::truncString(string& s, string delimiter){
    int delimiterLength = delimiter.length();
    string ans;
    if(s.find(delimiter) != std::string::npos){
        ans = s.substr(0, s.find(delimiter));
        //truncate the string and store everything after the delimiter
        s = s.substr(s.find(delimiter) + delimiter.length(), s.length());
    }
    return ans;
    
    
}

/** Check if a provided faculty line is a valid one
 * param: string line representing the line to be validated
 * return: bool T/F depending on if the line is valid or not
 */
bool FileProcessor::validFacLine(string line){
    //set up delimiter and intial string sets
    string delimiter = ", ";
    string input = truncString(line, delimiter);
    int facultyId;
    string facultyName;
    string facultyLevel;
    string facultyDept;

    try{
        //check if id is a valid id
        facultyId = stoi(input);
        if(facultyId <= 0){
            throw runtime_error("Invalid ID provided, sorry");
        }
        char c;
        input = truncString(line, delimiter);
        facultyName = input;
        input = truncString(line, delimiter);
        //check if input is a valid input (faculty level shouldn't have a number in it hence why it is error checked )
        for(int i  = 0; i < input.length(); ++i){
            c = toupper(input[i]);
            if((c < 'A' || c > 'Z') && c != ' '){
                throw runtime_error("ERROR: This faculty line had an invalid level...please make sure there are no numbers/symbols");
            }
        }
        facultyLevel = input;
        
        input = truncString(line, delimiter);
        //check if input is a valid input (dept shouldn't have a number in it hence why it is error checked )
        for(int i  = 0; i < input.length(); ++i){
            c = toupper(input[i]);
            if((c < 'A' || c > 'Z') && c != ' '){
                throw runtime_error("ERROR: This faculty line had an invalid department...please make sure there are no numbers/symbols");
            }
        }
        facultyDept = input;
       
        //check if the final fields are valid student ids
        int studentId;
        while(line == ""){
            input = truncString(line, delimiter);
            studentId = stoi(input);
        }
        if(line.length() > 0){
            studentId = stoi(line);
        }
    }catch(exception& e){
        cout << "ERROR: INVALID LINE PROVIDED FOR THE GIVEN FACULTY MEMBER: " << facultyId << endl;
        cerr << e.what() << endl;
        return false;
    }
    return true;

}


/** Check if a provided student line is a valid one
 * param: string line representing the line to be validated
 * return: bool T/F depending on if the line is valid or not
 */
bool FileProcessor::validStuLine(string line){

    //intial setup for delimiter, variables, input
    string input = "";
    string delimiter = ", ";
    int studentId;
    string studentName;
    string studentLevel;
    string studentMajor;
    double studentGpa;
    int studentAdvisor;
    input = truncString(line, delimiter);

    try{
        char c;
        //check if id is a valid id
        studentId = stoi(input);
        if(studentId <= 0){
            throw runtime_error("Invalid ID provided, sorry");
        }
        input = truncString(line, delimiter);
        studentName = input;

        input = truncString(line, delimiter);
        for(int i  = 0; i < input.length(); ++i){
            c = toupper(input[i]);
            if((c < 'A' || c > 'Z') && c != ' '){
                throw runtime_error("ERROR: This student line had an invalid level...please make sure there are no numbers/symbols");
            }
        }
        studentLevel = input;

        input = truncString(line, delimiter);
        for(int i  = 0; i < input.length(); ++i){
            c = toupper(input[i]);
            if((c < 'A' || c > 'Z') && c != ' '){
                throw runtime_error("ERROR: This student line had an invalid major...please make sure there are no numbers/symbols");
            }
        }
        studentMajor = input;
        input = truncString(line, delimiter);
        studentGpa = stod(input);
        //check if it was a valid gpa input
        if(studentGpa < 0 || studentGpa > 4){
            throw runtime_error("Invalid GPA Provided");
        }
        studentAdvisor = stoi(line);
        //check if it was a valid advisor input
        if(studentAdvisor <= 0){
            throw runtime_error("Invalid student advisor id provided");
        }
       
    }catch(exception& e){
        cout << "ERROR: INVALID STUDENT MEMBER PROVIDED FOR THE ID: " << studentId << endl;
        cerr << e.what() << endl;
        return false;
    }
    return true;
    
}