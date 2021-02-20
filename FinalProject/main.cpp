#include "Instructor.h"
#include "Learner.h"
#include "Lecture.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool isFileExists(const string& name) {
    FILE* file;
    fopen_s(&file, name.c_str(), "r");
    if(file)
    {
        fclose(file);
        return true;
    }
    else
    {
        return false;
    }
}



// loads lecture values from Lectures.txt and returns
vector<Lecture> loadLectures() { 
    vector<Lecture> lectures; 

    // controls if file exists
    if (isFileExists("Lectures.txt"))
    {
        std::ifstream file("Lectures.txt");
        std::string str; 

        // reads line by line
        while (std::getline(file, str))
        {
            Lecture lecture; 

            // reads name of course
            lecture.name = str; 

            // reads price of course
            if (std::getline(file, str))
            {
                lecture.price = stod(str); 
            }

            // reads language of course
            if (std::getline(file, str))
            {
                lecture.language = str;
            }

            // reads number of purchases of coure
            if (std::getline(file, str))
            {
                lecture.nofPurchases = stoi(str); 
            }

            // adds course to lectures vector
            lectures.push_back(lecture); 
        }
        file.close();
    }
    else
    {
        cout << "Lectures.txt does not exist!" << endl;
    }

    return lectures;
}


// loads instructor values from Instructors.txt and returns
vector<Instructor> loadInstructors() {
    vector<Instructor> instructors;

    // controls if file exists
    if (isFileExists("Instructors.txt"))
    {
        std::ifstream file("Instructors.txt");
        std::string str; 

        // reads line by line
        while (std::getline(file, str))
        {
            Instructor instructor; 

            // reads name of instructor
            instructor.name = str;

            // reads instructor's course names seperated with ';'
            if (std::getline(file, str)) {
                string delimiter = ";";
                size_t pos = 0;                               
                string token;
                while ((pos = str.find(delimiter)) != std::string::npos)
                { 
                    token = str.substr(0, pos); // takes substring (course name) between start and semicolon                       
                    instructor.coursesToGive.push_back(token); // adds course name to instructor object
                    str.erase(0, pos + delimiter.length()); // clears added course names with their delimeters 
                }
            }

            // reads balance of instructor
            if (std::getline(file, str))
            {
                instructor.balance = stod(str); 
            }

            // adds instructor to instructors vector
            instructors.push_back(instructor); 
        }
        file.close();
    }
    else
    {
        cout << "Insructors.txt does not exist!" << endl;
    }

    return instructors;
}


// loads learner values from Learners.txt and returns 
vector<Learner> loadLearners() {
    vector<Learner> learners;

    // controls if file exists
    if (isFileExists("Learners.txt"))
    {
        std::ifstream file("Learners.txt");
        std::string str;

        // reads line by line
        while (std::getline(file, str))
        {
            Learner learner; 

            // reads name of learner
            learner.name = str;

            // read learner's course names seperated with ';'
            if (std::getline(file, str))
            {
                string delimiter = ";";
                size_t pos = 0;
                string token;
                while ((pos = str.find(delimiter)) != std::string::npos)
                {
                    token = str.substr(0, pos); // takes substring (course name) between start and semicolon
                    learner.coursesToTake.push_back(token); // adds course name to learner object
                    str.erase(0, pos + delimiter.length()); // clears added course names with their delimeters
                }
            }

            // reads balance of learner
            if (std::getline(file, str))
            {
                learner.balance = stod(str); 
            }

            // adds learner to learners vector
            learners.push_back(learner);
        }
        file.close();
    }
    else
    {
        cout << "Learners.txt file does not exist!" << endl;
    }

    return learners;
}


// saves lecture values to Lectures.txt
void saveLectures(vector<Lecture> lectures) {
    ofstream myfile;
    myfile.open("Lectures.txt");

    // writes values
    for (std::vector<Lecture>::iterator it = lectures.begin(); it != lectures.end(); ++it) 
    { 
        myfile << it->name << "\n"; 
        myfile << it->price << "\n";
        myfile << it->language << "\n";  
        myfile << it->nofPurchases << "\n";
    }
    myfile.close();
}


// saves instructor values to Lectures.txt
void saveInstructors(vector<Instructor> instructors) { 
    ofstream myfile;
    myfile.open("Instructors.txt");

    // writes values
    for (std::vector<Instructor>::iterator it = instructors.begin(); it != instructors.end(); ++it) 
    {
        myfile << it->name << "\n";
        for (std::vector<string>::iterator jt = it->coursesToGive.begin(); jt != it->coursesToGive.end(); ++jt)
        {
            myfile << *jt << ";";
        }
        myfile << "\n";
        myfile << it->balance << "\n";
    }
    myfile.close();
}


// saves learner values to Lectures.txt
void saveLearners(vector<Learner> learners) {
    ofstream myfile;
    myfile.open("Learners.txt");

    // writes values
    for (std::vector<Learner>::iterator it = learners.begin(); it != learners.end(); ++it) 
    {
        myfile << it->name << "\n";
        for (std::vector<string>::iterator jt = it->coursesToTake.begin(); jt != it->coursesToTake.end(); ++jt)
        {
            myfile << *jt << ";";
        }
        myfile << "\n";
        myfile << it->balance << "\n";
    }
    myfile.close();
}



int main() {

    // loads values from .txt files to vectors
    vector<Lecture> lectures = loadLectures();
    vector<Instructor> instructors = loadInstructors();
    vector<Learner> learners = loadLearners();

    // user input part
    bool isContinue = true;
    string input = "";

    while (isContinue) {

    main_page:
        int lectureIndex = 0;
        int instructorIndex = 0;
        int learnerIndex = 0;
        int iter_index = 0;

        // prints main menu
        cout << endl << "[1] Learner" << endl << "[2] Instructor" << endl << "[3] Save & Exit" << endl;
        getline(std::cin, input); // takes input for profile selection or finishing the operations
                    
        // [1] - learners menu
        if (!input.compare("1")) // instead of if(input == 1) 
        {                        // learner is selected
        
        learners_mainpage:
            iter_index = 1;
            cout << endl;
            for (std::vector<Learner>::iterator it = learners.begin(); it != learners.end(); ++it)
            {   // prints names of all learners
                cout << "[" << iter_index << "] " << it->name << endl;
                iter_index++;
            }
            getline(std::cin, input); // takes selection input for spesific learner
            if (stoi(input) >= iter_index) // converts string input to input and checks validity
            { 
                cout << "Invalid input." << endl;
                goto learners_mainpage; // returns to learners menu 
            }
            else
            {
                // specific learner is selected
                learnerIndex = stoi(input) - 1;

            learner_selected:
                // prints learner menu
                cout << endl << "[1] Current Courses" << endl << "[2] Buy Course" << endl << "[3] Balance" << endl << "[4] Logout" << endl;
                getline(std::cin, input); // takes input for choosing operation
                if (!input.compare("1")) // prints current courses menu of selected learner
                { 
                    cout << endl;
                    for (std::vector<string>::iterator it = learners[learnerIndex].coursesToTake.begin(); it != learners[learnerIndex].coursesToTake.end(); ++it)
                    {
                        cout << *it << endl; 
                    }
                    goto learner_selected; // returns to selected learner's main menu
                }
                else if (!input.compare("2")) // prints buy course menu of selected learner
                {

                buy_course_page:
                    // print courses
                    cout << endl;
                    iter_index = 1;
                    for (std::vector<Lecture>::iterator it = lectures.begin(); it != lectures.end(); ++it)
                    {   // prints names of all courses
                        cout << "[" << iter_index << "] " << it->name << endl;
                        iter_index++;
                    }
                    // if the learner does not buy anything
                    cout << "[" << iter_index << "] " << "Return" << endl;

                    getline(std::cin, input); // takes selection input for spesific course
                    if (stoi(input) > iter_index) // converts string input to integer and checks validity
                    { 
                        cout << "Invalid input." << endl;
                        goto buy_course_page; // returns to courses menu
                    }
                    else if (stoi(input) == iter_index)
                    {
                        // return is selected
                        goto learner_selected; // returns to selected learner's main menu
                    }
                    else
                    {   // specific course is selected
                        lectureIndex = stoi(input) - 1;

                    lecture_buy_page:
                        // prints course properties menu
                        cout << endl << lectures[lectureIndex].name << ": " << endl << endl;
                        cout << "Price:                  " << lectures[lectureIndex].price << endl;
                        cout << "Number Of Purchases:    " << lectures[lectureIndex].nofPurchases << endl;
                        cout << "Language:               " << lectures[lectureIndex].language << endl << endl;

                        // prints purchasing decision menu
                        cout << "[1] Buy The Course" << endl << "[2] Return" << endl;
                        getline(std::cin, input);

                        if (!input.compare("1")) // buy the course
                        {
                            // checks if course has already been purchased
                            if (std::count(learners[learnerIndex].coursesToTake.begin(), learners[learnerIndex].coursesToTake.end(), lectures[lectureIndex].name))
                            {
                                cout << endl << "This course already exists!" << endl;
                                goto learner_selected; // returns to selected learner's main menu
                            }
                            else
                            {   // if balance is enough
                                if (learners[learnerIndex].balance >= lectures[lectureIndex].price) 
                                {
                                    cout << endl << "Course is added to Current Courses successfully!" << endl;
                                    // decreases the learner's balance 
                                    learners[learnerIndex].balance -= lectures[lectureIndex].price;
                                    // increases number of purchases of the lecture 
                                    lectures[lectureIndex].nofPurchases++;
                                    // adds course to learner 
                                    learners[learnerIndex].coursesToTake.push_back(lectures[lectureIndex].name);
                                    // increases the instructor's balance 
                                    // finds instructor who has this course 
                                    for (std::vector<Instructor>::iterator it = instructors.begin(); it != instructors.end(); ++it)
                                    {
                                        if (std::count(it->coursesToGive.begin(), it->coursesToGive.end(), lectures[lectureIndex].name))
                                        {
                                            it->balance += lectures[lectureIndex].price;
                                            break;
                                        }
                                    }
                                }
                                else 
                                {
                                    cout << endl << "There is not enough balance!" << endl;
                                    goto lecture_buy_page; // returns to selected course's properties menu 
                                }
                                goto learner_selected; // returns to selected learner's main menu
                            }
                        }
                        else if (!input.compare("2")) // return
                        {
                            goto learner_selected; // returns to selected learner's main menu
                        }
                        else
                        {
                            cout << endl << "Invalid input." << endl;
                            goto lecture_buy_page; // returns to selected course's properties menu 
                        }
                    }
                }
                else if (!input.compare("3")) 
                {
                    // prints balance for selected learner
                    cout << endl << learners[learnerIndex].balance << endl;
                    goto learner_selected;
                }
                else if (!input.compare("4"))
                {
                    goto main_page; // returns to main menu
                }
            }
        }


        // [2] - instructors menu
        else if (!input.compare("2")) // instead of if(input == 2)
        {
            
        instructors_mainpage:
            iter_index = 1;

            cout << endl;
            for (std::vector<Instructor>::iterator it = instructors.begin(); it != instructors.end(); ++it)
            {   // prints names of all instructors
                cout << "[" << iter_index << "] " << it->name << endl;
                iter_index++;
            }
            getline(std::cin, input); // takes selection input for specific intructor
            if (stoi(input) >= iter_index) // converts string input to integer and checks validity
            {
                cout << "Invalid input." << endl;
                goto instructors_mainpage; // returns to instructors menu
            }
            else
            {
                // specific instructor is selected
                instructorIndex = stoi(input) - 1;
            instructor_selected:
                // prints instructor menu
                cout << endl << "[1] Current Courses" << endl << "[2] Add New Course" << endl << "[3] Balance" << endl << "[4] Logout" << endl;
                getline(std::cin, input); // takes input for choosing operation
                if (!input.compare("1")) // prints current courses menu for selected instructor
                {
                    cout << endl;
                    for (std::vector<string>::iterator it = instructors[instructorIndex].coursesToGive.begin(); it != instructors[instructorIndex].coursesToGive.end(); ++it)
                    {
                        cout << *it << endl;
                    }
                    goto instructor_selected; // returns to selected learner's main menu
                }
                else if (!input.compare("2")) // adds new course with its features
                {
                    Lecture newLecture; // newLecture is an instance of Lecture class

                    cout << endl << "name: " << endl;
                    getline(std::cin, input);
                    newLecture.name = input;

                    cout << "price: " << endl;
                    getline(std::cin, input);
                    newLecture.price = stod(input);

                    cout << "language: " << endl;
                    getline(std::cin, input);
                    newLecture.language = input;

                    newLecture.nofPurchases = 0;

                    lectures.push_back(newLecture); // adds newLecture to lectures vector
                    instructors[instructorIndex].coursesToGive.push_back(newLecture.name); // adds newLecture to instuctor's Current Courses
                    cout << endl << "Course is added to Current Courses successfully!" << endl;

                    goto instructor_selected; // returns to selected learner's main menu
                }
                else if (!input.compare("3")) 
                {
                    // print balance for selected instructor
                    cout << endl << instructors[instructorIndex].balance << endl;
                    goto instructor_selected; // returns to selected learner's main menu
                }
                else if (!input.compare("4"))
                {
                    goto main_page; // returns to main menu
                }
            }
        }


        // [3] - save and exit
        else if (!input.compare("3"))
        {
            // break from while
            isContinue = false;
        }


        else
        {
            cout << "Invalid input." << endl << endl;
        }
    }

    // saves updated values to .txt files
    saveLectures(lectures);
    saveInstructors(instructors);
    saveLearners(learners);

    return 0;

}