/*
 * Shree Murthy
 * 2374658
 * shmurthy@chapman.edu
 * CPSC 350-03
 * Assignment 6
 **/



//handles everything necessary to simulate the database and conduct all the methods necessary to update/print/access the database
#include "Simulation.h"

/** default constructor
*/
Simulation::Simulation(){
    masterFaculty = new GenBST<Faculty>();
    masterStudent = new GenBST<Student>();
    operation = new Rollback<unsigned int>(5);
    information = new Rollback<string>(5);
}


/** default destructor
*/
Simulation::~Simulation(){
    delete masterFaculty;
    delete masterStudent;
    delete operation;
    delete information;
    
}


/** The run method 
 */
void Simulation::run(){
    cout << "WELCOME TO THE SCHOOL DATABASE HERE ARE YOUR OPTIONS: " << endl;
    int x; //represents the option selected by the user
    string input;
    setup();
    while(x != 14){
        cout << endl;
        options();
        getline(cin, input);
        x = stoi(input);
        try{
            switch(x){
                case 1:
                    printStudents();
                    break;
                case 2:
                    printFaculty();
                    break;
                case 3:
                    findStudent();
                    break;
                case 4:
                    findFaculty();
                    break;
                case 5:
                    getFacultyAdvisor();
                    break;
                case 6:
                    getAdvisees();
                    break;
                case 7:
                    addStudent();
                    break;
                case 8:
                    deleteStudent();
                    break;
                case 9:
                    addFaculty();
                    break;
                case 10:
                    deleteFaculty();
                    break;
                case 11:
                    changeStudentAdvisor();
                    break;
                case 12:
                    removeAdvisee();
                    break;
                case 13:
                    rollback();
                    break;
            }
        }catch(exception& e){
            cerr << e.what() << endl;
        }
    }
    saveAndExit();
        
       

}


/** Setup the BSTs given the files
 */
void Simulation::setup(){
    FileProcessor fp; 
    Faculty temp;
    Student tmp;
    try{
        ifstream inFile;
        inFile.open("facultyTable");
        if(inFile.is_open()){
            try{
                string s;
                
                while(getline(inFile, s)){
                    if(!fp.validFacLine(s)){
                        continue;
                    }
                    Faculty f(s);
                    masterFaculty->insert(f);

                }
            }catch(exception& e){
                cerr << e.what() << endl;
            }
        }

    }catch(exception& e){
        cerr << e.what() << endl;
    }

    try{
        ifstream inFile;
        inFile.open("studentTable");
        if(inFile.is_open()){
            
            string s;
            while(getline(inFile, s)){
            
                try{
                    if(!fp.validStuLine(s)){
                        continue;
                    }
                    Student f(s);
                    Faculty t;
                    t.setId(f.getAdvisor());
                    if(!masterFaculty->contains(t)){
                        throw runtime_error("ERROR: INVALID STUDENT PROVIDED");
                    }
                    //also check to see if the faculty's advisee list contains this student's id
                    t = *(masterFaculty->returnData(t));
                    GenLinkedList<unsigned int> adviseeList = t.returnList();
                    if(adviseeList.find(f.getId()) == -1){
                        t.addAdvisee(f);
                    }
                    masterStudent->insert(f);
                }catch(exception& e){
                    cerr << e.what() << endl;
                }
                    

            }
        }

    }catch(exception& e){
        cerr << e.what() << endl;
    }
    
    
}


/** Display all the options for the project
 */
void Simulation::options(){
    cout << "PROVIDE THE OPERATION YOU WOULD TO CONDUCT: " << endl;
    cout << "\t1. Print all students and their information" << endl;
    cout << "\t2. Print all faculty and their information" << endl;
    cout << "\t3. Find and display student information given their id" << endl;
    cout << "\t4. Find and display faculty information given their id" << endl;
    cout << "\t5. Given a student's id, print the name and information of their faculty advisor" << endl;
    cout << "\t6. Given a faculty's id, print ALL the names and info of their advisees" << endl;
    cout << "\t7. Add a new student" << endl;
    cout << "\t8. Delete a student given their id" << endl;
    cout << "\t9. Add a new faculty member" << endl;
    cout << "\t10. Delete a faculty member given their id" << endl;
    cout << "\t11. Change a student's advisor given the student id and the new faculty id" << endl;
    cout << "\t12. Remove an advisee from a faculty member given the ids" << endl;
    cout << "\t13. Undo" << endl;
    cout << "\t14. Save and exit" << endl;

}

/** Print all the students in the bst
 */
void Simulation::printStudents(){
    cout << "LISTING ALL STUDENTS IN THE DATABASE..." << endl;
    cout.flush();
    usleep(100000);
    masterStudent->printNodes();
}

/** Print all the faculty members in the bst
 */
void Simulation::printFaculty(){
    cout << "LISTING ALL FACULTY MEMBERS IN THE DATABASE..." << endl;
    cout.flush();
    usleep(100000);
    masterFaculty->printNodes();
}

/** Find the information of a particular student
 */
void Simulation::findStudent(){
    string input;
    unsigned int id;
    cout << "Provide the student's id please: " << endl;
    getline(cin, input);
    try{
        id = stoi(input);
        if(id <= 0){
            throw runtime_error("INVALID ID GIVEN...IT HAS TO BE GREATER THAN 0");

        }
    }catch(exception& e){
        cout << "ERROR" << endl;
        cerr << e.what() << endl;

    }
    Student s;
    s.setId(id);
    cout <<  *(masterStudent->returnData(s));


}

/** Find the information of a particular faculty
 */
void Simulation::findFaculty(){
    string input;
    unsigned int id;
    cout << "Provide the faculty's id please: " << endl;
    getline(cin, input);
    try{
        id = stoi(input);
        if(id <= 0){
            throw runtime_error("INVALID ID GIVEN...IT HAS TO BE GREATER THAN 0");

        }
    }catch(exception& e){
        cout << "ERROR" << endl;
        cerr << e.what() << endl;

    }
    Faculty s;
    s.setId(id);
    cout << *(masterFaculty->returnData(s));

}


//conduct error checking (i.e if they include a comma, large int provided, blank string, etc)
/** Add a particular student to the masterStudent bst
 */
void Simulation::addStudent(){
    Student s;
    string input;

    int id; 
    string name;
    string level;
    string major;
    double gpa;
    unsigned int advisorId;

    cout << "Please be provide the necessary student information: " << endl;
    cout << "Input an ID: ";
    getline(cin, input);
    try{
        id = stoi(input);
        if(id <= 0){
            throw runtime_error("INVALID ID GIVEN...IT HAS TO BE GREATER THAN 0");
            
        }
        char c; //used to check if a provided string is a valid one (i.e no numbers or characters)
        cout << "Input a name: ";
        getline(cin, input);
        name = input;
        cout << "Input the student's level: ";
        getline(cin, input);
        for(int i  = 0; i < input.length(); ++i){
            c = toupper(input[i]);
            if((c < 'A' || c > 'Z') && c != ' ' ){
                throw runtime_error("ERROR: This student line had an invalid level...please make sure there are no numbers/symbols");
            }
        }
        level = input;
        cout << "Input the student's major: ";
        getline(cin, input);
        for(int i  = 0; i < input.length(); ++i){
            c = toupper(input[i]);
            if((c < 'A' || c > 'Z') && c != ' '){
                throw runtime_error("ERROR: This student line had an invalid major...please make sure there are no numbers/symbols");
            }
        }
        major = input;
    

        cout << "Input student's gpa: ";
        getline(cin, input);
        gpa = stod(input);
        if(gpa < 0 && gpa <= 4.00){
            throw runtime_error("INVALID GPA GIVEN...IT HAS TO BE GREATER THAN 0");

        }
        cout << "Input the student's advisor id: ";
        getline(cin, input);
        advisorId = stoi(input);
        if(advisorId <= 0){
            throw runtime_error("INVALID ID GIVEN...IT HAS TO BE GREATER THAN 0");

        }
        Faculty advisor;
        advisor.setId(advisorId);

        s.setId(id);
        s.setName(name);
        s.setAdvisorId(advisorId);
        s.setGpa(gpa);
        s.setMajor(major);
        s.setLevel(level);
        

        bool treeContains;
        treeContains = masterFaculty->contains(advisor);

        
        //this block checks if the faculty information provided is a valid one and if it isn't then ask the the user to update the advisor with a valid one
        while(treeContains == false){
            if(masterFaculty->isEmpty()){
                    throw runtime_error("ERROR: There are no faculty members in the database, please enter some before adding students");
                    break;
            }
            
                
            Faculty newAdvisor;
            cout << "Apologies the given advisor information doesn't exist in the database...please provide an id of someone who exists" << endl;
            getline(cin, input);
            advisorId = stoi(input);
            if(advisorId <= 0){
                throw runtime_error("INVALID ID GIVEN...IT HAS TO BE GREATER THAN 0");

            }
            s.setAdvisorId(advisorId);
            newAdvisor.setId(advisorId);
            treeContains = masterFaculty->contains(newAdvisor);
        
        }
        if(masterStudent->contains(s)){
            throw runtime_error("ERROR: Faculty member with the given id already exists");
        }else{
            masterStudent->insert(s);
        }
        //update the faculty member with the advisee information provided
        Faculty finalAdvisor;
        finalAdvisor.setId(advisorId);
        finalAdvisor = *(masterFaculty->returnData(finalAdvisor));
        finalAdvisor.addAdvisee(s);


        //add information to the rollback
        ostringstream oss;
        s >> oss;
        information->push(oss.str());
        operation->push(8);


        
    }catch(exception& e){
        cout << "ERROR" << endl;
        cerr << e.what() << endl;

    }
    
   
   
  


    
    


    


    
    
        
    

}


/** Add a particular faculty member to the masterFaculty bst
 */
void Simulation::addFaculty(){
    Faculty f;
    string input;

    unsigned int id; 
    string name;
    string level;
    string department;

    cout << "Please be provide the necessary faculty information: " << endl;
    cout << "Input an ID: ";
    getline(cin, input);
    try{
        id = stoi(input);
        if(id <= 0){
            throw runtime_error("INVALID ID GIVEN...IT HAS TO BE GREATER THAN 0");

        }
        char c; //check if a provided string is a valid one (i.e there no random characters/numbers)
        cout << "Input a name: ";
        getline(cin, input);
        name = input;

        cout << "Input the faculty's level: ";
        getline(cin, input);
        for(int i  = 0; i < input.length(); ++i){
            c = toupper(input[i]);
            if((c < 'A' || c > 'Z') && c != ' '){
                throw runtime_error("ERROR: This faculty line had an invalid level...please make sure there are no numbers/symbols");
            }
        }
        level = input;
        
        cout << "Input the faculty's department: ";
        getline(cin, input);
        for(int i  = 0; i < input.length(); ++i){
            c = toupper(input[i]);
            if((c < 'A' || c > 'Z') && c != ' '){
                throw runtime_error("ERROR: This faculty line had an invalid department...please make sure there are no numbers/symbols");
            }
        }
        department = input;

        f.setId(id);
        f.setName(name);
        f.setLevel(level);
        f.setDept(department);
        if(masterFaculty->contains(f)){
            throw runtime_error("ERROR: Faculty member with the given id already exists");
        }else{
            masterFaculty->insert(f);

        }
        
        
        ostringstream oss;
        f >> oss;
        information->push(oss.str());
        operation->push(10);
    }catch(exception& e){
        cout << "ERROR" << endl;
        cerr << e.what() << endl;

    }

    
}


/** Delete a student given their id
 */
void Simulation::deleteStudent(){
    Student s;
    string input;
    unsigned int id;
    cout << "What is the id of the student you would like to delete: ";
    getline(cin, input);
    try{
        id = stoi(input);
        if(id <= 0){
            throw runtime_error("INVALID ID GIVEN...IT HAS TO BE GREATER THAN 0");
   
        }
        s.setId(id);

        //check if the student exists
        if(masterStudent->contains(s)){
            s = *(masterStudent->returnData(s));
            //delete information from the advisor's linkedlist
            Faculty f;
            f.setId(s.getAdvisor());
            //find the faculty member 
            if(masterFaculty->contains(f)){
                f = *(masterFaculty->returnData(f));
                f.removeAdvisee(s); //remove the given student's information
                f.printAdvisees();
            }
            //delete the node
            if(masterStudent->deleteNode(s) == true){
                cout << "Sucessfully delete student with the ID: " << id << endl;
            }
        }else{//runs if the student wasn't found
            string s = "Student with the ID: ";
            s += to_string(id);
            s += " was not found, sorry.";
            throw runtime_error(s);
        }

        //add information to rollback
        ostringstream oss;
        s >> oss;
        information->push(oss.str());
        operation->push(7); //store the opposite operation 

    }catch(exception& e){
        cerr << e.what() << endl;
    }
    
}


/** Delete a faculty member given their id++
 */
void Simulation::deleteFaculty(){
    Faculty s;
    string input;
    unsigned int id;
    cout << "What is the id of the student you would like to delete: ";
    getline(cin, input);

    try{
        id = stoi(input);
        if(id <= 0){
            throw runtime_error("INVALID ID GIVEN...IT HAS TO BE GREATER THAN 0");

        }
            
        s.setId(id);
        Faculty t;
        if(masterFaculty->contains(s)){
            t = *(masterFaculty->returnData(s));
            ostringstream oss;
            t >> oss;
            information->push(oss.str());
            // ask for another faculty member that exists and attach the deleted member's advisee list
            GenLinkedList<unsigned int> list = t.returnList();
            if(list.getSize() > 0){
                if(masterFaculty->size() == 1){
                    throw runtime_error("UNABLE TO DELETE FACULTY: This is the last faculty in the table and deleting it will cause a Referential Integrity Issue");
                }
                cout << "This faculty member had advisees...please provide another faculty member's id to store these advisees: ";
                getline(cin, input);
                int id;
                id = stoi(input);
                Faculty f; 
                f.setId(id);
                if(!masterFaculty->contains(f)){
                    cout << "The faculty member with the id: " << id << " does not exist please provide a valid id" << endl;
                    bool treeContains;
                    treeContains = masterFaculty->contains(f);
                    while(treeContains == false){
                        Faculty newAdvisor;
                        cout << "Apologies the given advisor information doesn't exist in the database...please provide an id of someone who exists" << endl;
                        getline(cin, input);
                        id = stoi(input);
                        if(id <= 0){
                            cerr << "ERROR: ADVISOR ID IS LESS THAN OR EQUAL TO 0...CANNOT ADD STUDENT" << endl;
                            continue;
                        }
                        newAdvisor.setId(id);
                        treeContains = masterFaculty->contains(newAdvisor);
                    }

                    //update the new faculty information with the new advisees they are receiving
                    Faculty nAdvisor;
                    nAdvisor.setId(id);
                    nAdvisor = *(masterFaculty->returnData(nAdvisor));
                    while(list.getSize() != 0){
                        Student s;
                        s.setId(list.removeHead());
                        Student *s1 = masterStudent->returnData(s);
                        s1->setAdvisorId(nAdvisor.getId());
                        Faculty *f1 = masterFaculty->returnData(nAdvisor);
                        f1->addAdvisee(s);
                    }


                }else{
                    f = *(masterFaculty->returnData(f));
                    //update the new faculty information with the new advisees they are receiving
                    while(list.getSize() != 0){
                        Student s;
                        s.setId(list.removeHead());
                        Student *s1 = masterStudent->returnData(s);
                        s1->setAdvisorId(f.getId());
                        Faculty *f1 = masterFaculty->returnData(f);
                        f1->addAdvisee(s);
                    }
                }
                
            }
            cout << masterFaculty->size() << endl;
            
            if(masterFaculty->deleteNode(s) == true){
                cout << "Sucessfully deleted faculty with the ID: " << id << endl;
            }
        }else{
            cout << "Faculty with the ID: " << id << "was not found, sorry" << endl; 
        }

    
        operation->push(9);
    }catch(exception& e){
        cerr << e.what() << endl;

    }

}


/** Given a student's id return their advisor's information
 */
void Simulation::getFacultyAdvisor(){
    Student s;
    string input;
    unsigned int id;

    cout << "What is the id of the student: ";
    getline(cin, input);
    try{
        id = stoi(input);
        if(id <= 0){
            throw runtime_error("INVALID ID GIVEN...IT HAS TO BE GREATER THAN 0");
        }
        s.setId(id);

        //check if the student exists
        if(!(masterStudent->contains(s))){
            throw runtime_error("Student with the given id: " + to_string(id) + " does not exist, sorry");
        }else{
            Student t;
            //set the student information with that of what is in the tree
            t = *(masterStudent->returnData(s));
            cout << "The faculty information of the student with the id " << id << ": " << endl;
            Faculty temp;
            temp.setId(t.getAdvisor());

            Faculty found;
            //if the faculty member isn't found then throw an error
            if(masterFaculty->contains(temp) == false){
                string s = "Sorry the faculty advisor with the id " + to_string(temp.getId()) + " was not found, sorry";
                throw runtime_error(s);
            }else{//else return the information of the member
                found = *(masterFaculty->returnData(temp));
                cout << found;
            }
        }
        
    }catch(exception& e){
        cerr << e.what() << endl;
    }

}


/** Get the advisees of a particular faculty member
 */
void Simulation::getAdvisees(){
    string input;
    unsigned int id;

    cout << "Please provide the id of the faculty: ";
    getline(cin, input);
    try{
        id = stoi(input);
        if(id <= 0){
            throw runtime_error("INVALID ID GIVEN...IT HAS TO BE GREATER THAN 0");
        }

        Faculty temp;
        temp.setId(id);
        if(!(masterFaculty->contains(temp))){
            throw runtime_error("The faculty with the id: " + to_string(id) + " does not exist" );
        }else{
            //set temp to the information from the tree
            temp = *(masterFaculty->returnData(temp));
            cout << "Here is a list of all the faculty's advisees for the faculty id " << id << ": " << endl;
            GenLinkedList<unsigned int> list = temp.returnList();
            
            while(list.getSize() != 0){
                Student s;
                s.setId(list.removeHead());
                if(masterStudent->contains(s)){ //make sure the student exists due to integrity issues
                    s = *(masterStudent->returnData(s));
                    cout << s;
                }else{ //if a student with a given id doesn't exist then just remove them from the list
                    temp.removeAdvisee(s);
                }

            }
        }
    }catch(exception& e){
        cerr << e.what() << endl;

    }

    


}


/** Change a student's advisor given the id of the new and old faculty members
 */
void Simulation::changeStudentAdvisor(){
    string input;
    unsigned int id;
    cout << "Please provide the id of the student: ";
    getline(cin, input);
    try{
        id = stoi(input);
        if(id <= 0){
            throw runtime_error("INVALID ID GIVEN...IT HAS TO BE GREATER THAN 0");

        }
        Student s;
        s.setId(id);
        
        //check if student exists
        if(masterStudent->contains(s)){
            cout << "Student with the given id was found" << endl;
            s = *(masterStudent->returnData(s));
            ostringstream oss;
            s >> oss;
            //add the information of the old student to the rollback 
            information->push(oss.str());
            
            //set a temp faculty member to the id of the student's advisor
            id = s.getAdvisor();
            Faculty old;
            old.setId(id);

            //update the old faculty's advisee information
            Faculty *updateOld = masterFaculty->returnData(old);    
            updateOld->removeAdvisee(s);
            cout << "REMOVED THE ADVISEE FROM THE OLD FACULTY MEMBER " << id << endl;
        }else{
            throw runtime_error("Student with the given id was NOT found");
        }

        //conduct the transfer process
        cout << "Please provide the new faculty's id: ";
        getline(cin, input);
        
        id = stoi(input);
        if(id <= 0){
            throw runtime_error("INVALID ID GIVEN...IT HAS TO BE GREATER THAN 0");

        }
        

        Faculty newFac;
        newFac.setId(id);
        Student *s1 = masterStudent->returnData(s);
        s1->setAdvisorId(id);
        //check if the faculty member exists
        if(masterFaculty->contains(newFac)){
            Faculty *updateNewFac = masterFaculty->returnData(newFac);
            updateNewFac->addAdvisee(s);
        }else{  //referential integrity issue occurs if there is no faculty to attach the student to...this block fixes that
            bool treeContains;
            treeContains = masterFaculty->contains(newFac);
            
            while(treeContains == false){
                if(masterFaculty->isEmpty()){
                        throw runtime_error("ERROR: There are no faculty members in the database, please enter some before adding students");
                        break;
                }
                
                    
                Faculty newAdvisor;
                cout << "Apologies the given advisor information doesn't exist in the database...please provide an id of someone who exists" << endl;
                getline(cin, input);
                int advisorId = stoi(input);
                if(advisorId <= 0){
                    throw runtime_error("INVALID ID GIVEN...IT HAS TO BE GREATER THAN 0");

                }

                //update information 
                s1->setAdvisorId(advisorId);
                newAdvisor.setId(advisorId);
                //update while condition
                treeContains = masterFaculty->contains(newAdvisor);
            
            }
            //update the faculty member with the advisee information provided
            Faculty finalAdvisor;
            finalAdvisor.setId(s1->getAdvisor());
            finalAdvisor = *(masterFaculty->returnData(finalAdvisor));
            finalAdvisor.addAdvisee(s);

        }
                
        operation->push(15);
            
    }catch(exception& e){
        cout << e.what() << endl;
    }
    


}


/** Remove an advisee given their id
 */
void Simulation::removeAdvisee(){
    string input;
    unsigned int id;
    cout << "Please provide the faculty id: ";
    getline(cin, input);
    try{
        if(input.empty()){
            throw runtime_error("Sorry you provided an empty string...that is invalid!");
        }
        id = stoi(input);
        Faculty temp; 
        temp.setId(id);
        if(masterFaculty->contains(temp) == false){
            throw runtime_error("Invalid faculty id provided...they don't exist");
        }else{
            temp = *(masterFaculty->returnData(temp));
        }
        cout << "Faculty member found, please provide the id of the student to be removed ";
        getline(cin, input);
        if(input.empty()){
            throw runtime_error("Sorry you provided an empty string...that is invalid!");
        }
        id = stoi(input);        
        Student s;
        s.setId(id);

        //check if the student exists
        if(masterStudent->contains(s)){
            s = *(masterStudent->returnData(s));
            temp.removeAdvisee(s);
        }else{ //throw error because student doesn't exist
            throw runtime_error("Student with the given id: " + to_string(id) + " does not exist");
        }
        

        //update rollback information
        ostringstream oss;
        s >> oss;
        information->push(oss.str());
        operation->push(16);

        


    }catch(exception& e){
        cerr << e.what() << endl;
    }

}


/** Undo the last thing that changed the advisee lists or the bst
 */
void Simulation::rollback(){
    //if the operations stack is empty there is nothing we can do
    if(operation->getSize() == 0){
        cout << "ERROR: THERE IS NOTHING TO UNDO" << endl;
        return;
    }
    int ops = operation->pop();
    //original method: delete; undo method: add
    if(ops == 7){
        Student s(information->pop());
        masterStudent->insert(s);
        Faculty f;
        f.setId(s.getAdvisor());
        f = *(masterFaculty->returnData(f));
        f.addAdvisee(s);
        f.printAdvisees();
        
    }
    //original method: add; undo method: delete
    if(ops == 8){
        Student s(information->pop());
        Faculty f;
        f.setId(s.getAdvisor());
        f = *(masterFaculty->returnData(f));
        f.removeAdvisee(s);
        masterStudent->deleteNode(s);

    }
    //original method: delete; undo method: add
    if(ops == 9){
        Faculty f(information->pop());
        masterFaculty->insert(f);
        GenLinkedList<unsigned int> list = f.returnList();
        int size = list.getSize();
        for(int i = 0; i < size; ++i){
            Student s;
            s.setId(list.removeHead());
            s = *(masterStudent->returnData(s));
            Student *s1 = masterStudent->returnData(s);
            Faculty t;
            t.setId(s.getAdvisor());
            if(masterFaculty->contains(t))
                masterFaculty->returnData(t)->removeAdvisee(s);
            else{
                cout << "ERROR" << endl;
            }
            s1->setAdvisorId(f.getId());
        }
    }
    //original method: add; undo method delete;
    if(ops == 10){
        Faculty f(information->pop());
        masterFaculty->deleteNode(f);
    }
    //original method: change an advisor; undo method: undo the change 
    if(ops == 15){
        //gather student info
        Student s(information->pop());
        Student *currInfo;
        currInfo = masterStudent->returnData(s);

        //gather info on their current advisor
        Faculty currentAdvisor;
        currentAdvisor.setId(currInfo->getAdvisor());
        Faculty *currAdvisor = masterFaculty->returnData(currentAdvisor);
        currAdvisor->removeAdvisee(s);

        //add the advisee back onto the new advisor (aka their old one)
        Faculty newAdvisor;
        newAdvisor.setId(s.getAdvisor());
        Faculty *nAdvisor = masterFaculty->returnData(newAdvisor);
        nAdvisor->addAdvisee(s);


    }
    //orignal method: remove an advisee new: add an advisee
    if(ops == 16){
        Student s(information->pop());
        Faculty f;
        f.setId(s.getAdvisor());
        f = *(masterFaculty->returnData(f)); 
        f.addAdvisee(s);
    }
}


/** Save the final bst created to a file in CSV format
 */
void Simulation::saveAndExit(){
    //ofstream to write into the facultyTable
    ofstream facFile;
    facFile.open("facultyTable"); //open the file
    //copy a linkedlist that stored all the faculty information
    GenLinkedList<Faculty> list = masterFaculty->preorderNodes();
    int size = list.getSize();
    
    Faculty f;
    for(int i = 0; i < size; ++i){
        //remove from the list and then add it to the facFile
        f = list.removeHead();
        f >> facFile;

    }
    facFile.close(); //close it to avoid memory issues

    ofstream stuFile;
    stuFile.open("studentTable");
    //copy a list of student nodes into the linkedlist
    GenLinkedList<Student> stuList = masterStudent->preorderNodes();
    size = stuList.getSize();
    Student s;
    for(int i = 0; i < size; ++i){
        //write into the stuFile
        s = stuList.removeHead();
        s >> stuFile;

    }
    stuFile.close(); //close to avoid memory issues
}
