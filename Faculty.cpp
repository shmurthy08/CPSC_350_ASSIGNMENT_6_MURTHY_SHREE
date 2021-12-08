/*
 * Shree Murthy
 * 2374658
 * shmurthy@chapman.edu
 * CPSC 350-03
 * Assignment 6
 **/


//create a faculty and then handle any updates to their advisee list as well as be able to compare them effectively
#include "Faculty.h"





/** Default constructor
*/
Faculty::Faculty(){
    facultyId = 0000000;
    facultyName = "No Faculty";
    facultyDept = "na";
    facultyLevel = "na";
    studentInfo = new GenLinkedList<unsigned int>();
    
}

/** Constructor given a line from a file
* param: string line representing the line from the file 
*/
Faculty::Faculty(string line){
    FileProcessor fp;
    string input;
    string delimiter = ", ";
    input = fp.truncString(line, delimiter);

    studentInfo = new GenLinkedList<unsigned int>();
    try{
        facultyId = stoi(input);
        if(facultyId <= 0){
            throw runtime_error("Invalid ID provided, sorry");
        }
        input = fp.truncString(line, delimiter);
        facultyName = input;
        input = fp.truncString(line, delimiter);
        facultyLevel = input;
        input = fp.truncString(line, delimiter);
        facultyDept = input;
        int studentId;
        if(line == ""){
            cout << "LINE HAS BEEN PARSED " << endl;
        }else{
            int studentId;
            while(line.find(", ") != std::string::npos){
                input = fp.truncString(line, delimiter);
                studentId = stoi(input);
                studentInfo->insertHead(studentId);
            }
            if(line.length() > 0){
                
                studentId = stoi(line);
                studentInfo->insertHead(studentId);
            }
        }
    }catch(exception& e){
        cout << "ERROR: INVALID LINE PROVIDED FOR THE GIVEN FACULTY MEMBER" << endl;
        cerr << e.what() << endl;
    }
}


/** Overloaded constructor
 * param: unsigned int id representing the id of the faculty; string name, lvl, and dept represent the faculty's name, standing, and department
 */
Faculty::Faculty(unsigned int id, string name, string lvl, string dept){
    facultyId = id;
    facultyName = name;
    facultyDept = dept;
    facultyLevel = lvl;
    studentInfo = new GenLinkedList<unsigned int>();

}


//Destructor
Faculty::~Faculty(){
    
}


/** Get the id of the faculty member
 * return: unsigned int that returns the id of the faculty member
 */
unsigned int Faculty::getId(){
    return facultyId;
}

/** get the name of the faculty
 * return: string of the faculty's name
 */
string Faculty::getName(){
    return facultyName;
}

/** get the department the faculty works at
 * return: string of the faculty's department
 */
string Faculty::getDept(){
    return facultyDept;
}

/** get the level of the faculty
 * return: string of the faculty's level
 */
string Faculty::getLevel(){
    return facultyLevel;
}

/** Set the id of the faculty
*/
void Faculty::setId(unsigned int id){
    //id can only be updated once
    if(facultyId > 0){
        throw runtime_error("CANNOT UPDATE ID AFTER INTIALLY SETTING IT");
    }
    facultyId = id;
}

/** set the name of the advisor
 * param: string name reprsenting the name
 */
void Faculty::setName(string name){
    facultyName = name;
} 

/** set the level of the advisor
 * param: string level reprsenting the level
 */
void Faculty::setLevel(string lvl){
    facultyLevel = lvl;
}


/** set the department of the advisor
 * param: string department reprsenting the depeartment
 */
void Faculty::setDept(string dept){
    facultyDept = dept;
} 


/** Add a student to the faculty's linkedlist of advisees
 * param: Student *s representing the student to be added into the linkedlist
 */
void Faculty::addAdvisee(Student s){
    //check if the advisee already exists
    if(studentInfo->find(s.getId()) != -1){
        cout << "Couldn't add student because the student already exists in this list" << endl;
    }else{
        //insert the advisee information to the linkedlist
        studentInfo->insertHead(s.getId());
        studentInfo->sort();
        cout << "SUCESSFULLY ADDED ADVISEE " << endl;
   }
}


/**print all the advisee ids in the linked list
 */
void Faculty::printAdvisees(){
    if(studentInfo->getSize() == 0){
        cout << "This faculty member has no advisees!" << endl;
    }else{
        studentInfo->print();
    }
}

/** return all the advisees in the list as one long csv string
 * return string representing a csv string of all the advisees
 */
string Faculty::getAdviseeString(){
    GenLinkedList<unsigned int> list = *(studentInfo);
    
    string ans;
    unsigned int temp;
    int size = list.getSize();
    
    //remove the contents of the list and add them to the answer string
    for(int i = 0; i < size; ++i){
        temp = list.removeHead();
        ans += to_string(temp);
        ans += ", ";
        list.insertTail(temp);
    }
    ans = ans.substr(0, ans.length() - 2); //remove the last , and then return it
    return ans;
}

/** Remove an advisee from a linkedlist given the student object
 * param: student s representing the student info to remove
 */
void Faculty::removeAdvisee(Student s){
    //find the position of the student's id
    int pos = studentInfo->find(s.getId());
    //remove the node
    studentInfo->removeNode(pos);
}

/** return a linkedlist of all the ids
 * return GenLinkedList<unsigned int> representing a copy of the member variable
 */
GenLinkedList<unsigned int> Faculty::returnList(){

    GenLinkedList<unsigned int> list;
    int size = studentInfo->getSize();
    unsigned int temp;
    //copy the member variable information into the new linkedlist that will be returned
    for(int i = 0; i < size; ++i){
        temp = studentInfo->removeHead();
        list.insertHead(temp);
        studentInfo->insertTail(temp);
    }
    studentInfo->sort();
    return list;
}

/** Overload the == method 
 * param: Faculty member that is to be compared
 */
bool Faculty::operator==(Faculty& right){
    return (getId() == right.getId());
}


/** Overload the != method 
 * param: Faculty member that is to be compared
 */
bool Faculty::operator!=(Faculty& right){
    return (getId() != right.getId());
}


/** Overload the > method 
 * param: Faculty member that is to be compared
 */
bool Faculty::operator>(Faculty& right){
    return (getId() > right.getId());
}


/** Overload the < method 
 * param: Faculty member that is to be compared
 */
bool Faculty::operator<(Faculty& right){
    return (getId() < right.getId());
}


/** Overload the <= method 
 * param: Faculty member that is to be compared
 */
bool Faculty::operator<=(Faculty& right){
    return (getId() <= right.getId());
}



/** Overload the >= method 
 * param: Faculty member that is to be compared
 */
bool Faculty::operator>=(Faculty& right){
    return (getId() >= right.getId());
}



/** Overload the << method 
 * param: Faculty member that is to be compared
 * return: return an ostream that will output the faculty information
 */
ostream& operator<<(ostream& s, Faculty& f){
    s << "  ADVISOR INFORMATION:  " << endl;
    s << "     ID: " << f.getId() << endl;
    s << "     NAME: " << f.getName() << endl;
    s << "     LEVEL: " << f.getLevel() << endl;
    s << "     DEPARTMENT: " << f.getDept() << endl;

    return s;

}


/** Overload the << method 
 * param: Faculty member that is to be compared
 * return: return an ostream that will output the faculty information in a csv format
 */
ostream& operator>>(Faculty& f, ostream& s){
    s << f.getId() << ", " << f.getName() << ", " << f.getLevel() << ", " <<  f.getDept() << ", " << f.getAdviseeString() << endl;

    return s;
}


