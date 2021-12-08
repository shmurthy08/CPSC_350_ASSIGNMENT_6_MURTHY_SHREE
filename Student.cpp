/*
 * Shree Murthy
 * 2374658
 * shmurthy@chapman.edu
 * CPSC 350-03
 * Assignment 6
 **/


//create valid student objects and handle any updates 
#include "Student.h"
#include "FileProcessor.h"


using namespace std;


/** Default constructor
 */
Student::Student(){
    studentName = "null student";
    studentId = 0;
    studentLevel = "na";
    studentMajor = "undeclared";
    studentGpa = 1.0;
    studentAdvisor = 1234;
}



/** Constructor given a line from a file
* param: string line representing the line from the file 
*/
Student::Student(string line){
    FileProcessor fp;
    string input;
    string delimiter = ", ";
    input = fp.truncString(line, delimiter);

    try{
        studentId = stoi(input);
        if(studentId <= 0){
            throw runtime_error("Invalid ID provided, sorry");
        }
        input = fp.truncString(line, delimiter);
        studentName = input;
        input = fp.truncString(line, delimiter);
        studentLevel = input;
        input = fp.truncString(line, delimiter);
        studentMajor = input;
        input = fp.truncString(line, delimiter);
        studentGpa = stod(input);
        if(studentGpa < 0){
            throw runtime_error("Invalid GPA Provided");
        }
        studentAdvisor = stoi(line);
        if(studentAdvisor < 0){
            throw runtime_error("Invalid student advisor id provided");
        }
       
    }catch(exception& e){
        cout << "ERROR: INVALID STUDENT MEMBER PROVIDED" << endl;
    }
    
}

/** Overloaded constructor
 * param: unsigned int id representing the id of the student; string name, lvl, major representing the name, level and major of the student
 * param: double gpa represents the gpa of the student; unsigned int advi represents the id of the student's advisor
 */
Student::Student(unsigned int id, string name, string lvl, string major, double gpa, unsigned int advi){
    studentName = name;
    studentId = 0;
    studentLevel = lvl;
    studentMajor = major;
    studentGpa = gpa;
    studentAdvisor = advi;
    setId(id);
}

//default destructor
Student::~Student(){

}

/** get the id of the student
 * return: unsigned int representing the id of the student
 */
unsigned int Student::getId(){
    return studentId;
}

/** get the name of the student
 * return: string represeting the name of the student
 */
string Student::getName(){
    return studentName;
}

/** get the level of the student
 * return: string represeting the level of the student
 */
string Student::getLevel(){
    return studentLevel;
}

/** get the major of the student
 * return: string represeting the major of the student
 */
string Student::getMajor(){
    return studentMajor;
}

/** get the gpa of the student
 * return: double represeting the gpa of the student
 */
double Student::getGpa(){
    return studentGpa;
}

/** get the name of the student
 * return: string represeting the name of the student
 */
unsigned int Student::getAdvisor(){
    return studentAdvisor;
}


/** update id
* param: unsigned int of the new id
*/
void Student::setId(unsigned int i){
    //id can only be updated once...this checks that
    if(studentId > 0){
        throw runtime_error("CANNOT UPDATE ID AFTER INTIALLY SETTING IT");
    }
    studentId = i;
}

/** update name
* param: string representing a name
*/
void Student::setName(string name){
    studentName = name;
}
/** update level
* param: string representing the new level
*/
void Student::setLevel(string lvl){
    studentLevel = lvl;
}
/** update major
* param: string representing the new major
*/
void Student::setMajor(string major){
    studentMajor = major;
}
/** update gpa
* param: double gpa representing the new gpa
*/
void Student::setGpa(double gpa){
    studentGpa = gpa;
}

/** update advisor id
* param unsigned int representing the new advisor id
*/
void Student::setAdvisorId(unsigned int i){
    studentAdvisor = i;
}

/** check if student is == than what is passed in
* Param: Student to be compared
* return: bool with result of the comparison
*
*/
bool Student::operator==(Student& right){
    return (getId() == right.getId());
}

/** check if student is != than what is passed in
* Param: Student to be compared
* return: bool with result of the comparison
*
*/
bool Student::operator!=(Student& right){
    return (getId() != right.getId());
}

/** check if student is > than what is passed in
* Param: Student to be compared
* return: bool with result of the comparison
*
*/
bool Student::operator>(Student& right){
    return (getId() > right.getId());
}

/** check if student is < than what is passed in
* Param: Student to be compared
* return: bool with result of the comparison
*
*/
bool Student::operator<(Student& right){
    return (getId() < right.getId());
}


/** check if student is <= than what is passed in
* Param: Student to be compared
* return: bool with result of the comparison
*
*/
bool Student::operator<=(Student& right){
    return (getId() <= right.getId());
}

/** check if student is >= than what is passed in
* Param: Student to be compared
* return: bool with result of the comparison
*
*/
bool Student::operator>=(Student& right){
    return (getId() >= right.getId());
}

/** Output student info 
* Param: Student passed by reference to pull information and ostream passed by reference to append it and then return it
* return: ostream with all the information of the student
*
*/
ostream& operator<<(ostream& s, Student& st){
    s << "  STUDENT INFORMATION:  " << endl;
    s << "     ID: " << st.getId() << endl;
    s << "     NAME: " << st.getName() << endl;
    s << "     LEVEL: " << st.getLevel() << endl;
    s << "     MAJOR: " << st.getMajor() << endl;
    s << "     GPA: " << fixed << setprecision(2) << st.getGpa() << endl;
    s << "     ADVISOR: " << st.getAdvisor() << endl;

    return s;

}

/** Output student info as a csv format (id, name, lvl, etc)
* Param: Student passed by reference to pull information and ostream passed by reference to append it and then return it
* return: ostream with all the information of the student
*
*/
ostream& operator>>(Student& st, ostream& s){

    s << st.getId() << ", " << st.getName() << ", " << st.getLevel() << ", " << st.getMajor() << ", " << fixed << setprecision(2) << st.getGpa() << ", " << st.getAdvisor() << endl;

    return s;
}