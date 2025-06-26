//=============================================================================
// Name         : ProjectTwo.cpp
// Author       : Jester Cruz
// Description  : ABCU Course Planner Program using Hash Table
//=============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Define structure to hold course information
struct Course {
    string courseNumber; // Identifier for the course
    string courseTitle;  // Title of the course
    vector<string> prerequisites;  // List of course numbers that are prerequisites
};

// HashTable size definition
const unsigned int TABLE_SIZE = 10; // Set the size of the hash table

// Node for chaining in hash table
struct Node {
    Course course;  // Store the course object
    Node* next;  // Pointer to the next node 

    Node(Course aCourse) {
        this->course = aCourse; // Initialize node with course data
        this->next = nullptr; // Initialize next pointer to null
    }
};

// Hash Table class to store courses
class HashTable {
private:
    vector<Node*> table;  // internal hast table represented as a vector of Node pointers

    // Simple hash function based on course number
    unsigned int hash(string courseNumber) {
        unsigned int hash = 0;
        for (char ch : courseNumber) {
            hash += ch;  // Sum ASCII values of characters in course number
        }
        return hash % TABLE_SIZE; // Use modulo to fit within table size
    }

public:
    HashTable() {
        table.resize(TABLE_SIZE);  // Initialize the table with null pointers
    }

    // Insert a course into the hash table
    void Insert(Course course) {
        unsigned int index = hash(course.courseNumber);  // Compute index using hash function
        Node* newNode = new Node(course);  // Create a new node with the course
        if (table[index] == nullptr) { // If empty
            table[index] = newNode;  // Place node directly
        }
        else {
            Node* current = table[index];  // Traverse chain until the end
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;  // Append new node to end of chain
        }
    }

    // Search for a course by course number
    Course* Search(string courseNumber) {
        unsigned int index = hash(courseNumber);  // Compute index using hash function
        Node* current = table[index];  // Traverse the list  at the index
        while (current != nullptr) {
            if (current->course.courseNumber == courseNumber) {
                return &current->course; // Return pointer to course
            }
            current = current->next;
        }
        return nullptr; // Return null if not found
    }

    // Retrieve all courses into a vector (for sorting)
    vector<Course> GetAllCourses() {
        vector<Course> allCourses;
        for (unsigned int i = 0; i < TABLE_SIZE; ++i) {
            Node* current = table[i];
            while (current != nullptr) {
                allCourses.push_back(current->course); // Add each course to the vector
                current = current->next;
            }
        }
        return allCourses; // Return the collected vector
    }
};

// Load course data from a CSV file into the hash table
void LoadData(HashTable& table) {
    ifstream file("CS 300 ABCU_Advising_Program_Input.csv"); // Open the CSV file
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return; // Exit if file can't be opened
    }

    string line;
    while (getline(file, line)) {  // Read each line of the file
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {  // Split line by commas
            tokens.push_back(token);
        }

        Course course;
        if (tokens.size() >= 2) {
            course.courseNumber = tokens[0];  // First field: course number
            course.courseTitle = tokens[1]; // Second field: course title
            for (size_t i = 2; i < tokens.size(); ++i) { // Remaining fields: prerequisites
                if (!tokens[i].empty()) {
                    course.prerequisites.push_back(tokens[i]);
                }
            }
            table.Insert(course);  // Insert course into hash table
        }
    }

    file.close();  // Close the file
    cout << "Courses loaded successfully." << endl;
}

// Print the course list in alphanumeric order
void PrintCourseList(HashTable& table) {
    vector<Course> allCourses = table.GetAllCourses();  // Get all courses from hash table
    sort(allCourses.begin(), allCourses.end(), [](Course a, Course b) {
        return a.courseNumber < b.courseNumber;  // Sort courses by course number
        });

    cout << "Here is a sample schedule:" << endl;
    for (Course course : allCourses) {
        cout << course.courseNumber << ", " << course.courseTitle << endl; // Print each course
    }
}

// Print details about a specific course
void PrintCourseInfo(HashTable& table) {
    string courseNum;
    cout << "What course do you want to know about? ";
    cin >> courseNum;

    // Convert to uppercase for consistent searching
    transform(courseNum.begin(), courseNum.end(), courseNum.begin(), ::toupper);

    Course* course = table.Search(courseNum);  // Search course in hash table
    if (course == nullptr) {
        cout << "Course not found." << endl;  // If not found, display message
    }
    else {
        cout << course->courseNumber << ", " << course->courseTitle << endl;
        if (!course->prerequisites.empty()) {
            cout << "Prerequisites: ";
            for (size_t i = 0; i < course->prerequisites.size(); ++i) {
                cout << course->prerequisites[i];
                if (i < course->prerequisites.size() - 1) cout << ", ";
            }
            cout << endl;
        }
        else {
            cout << "Prerequisites: None" << endl;  // If no prerequisites
        }
    }
}

// Main program loop
int main() {
    HashTable courseTable;  // Create an instance of the hash table
    int choice;  // Store user menu choice

    cout << "Welcome to the course planner." << endl;

    do {
        // Display menu options
        cout << "\n1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";
        cin >> choice;

        // Process user input
        switch (choice) {
        case 1:
            LoadData(courseTable);  // Lead data from CSV file
            break;
        case 2:
            PrintCourseList(courseTable);  // Display all courses
            break;
        case 3:
            PrintCourseInfo(courseTable);  // Display specific course info
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << choice << " is not a valid option." << endl; // Handle invalid input
        }

    } while (choice != 9);  // Repeat menu until user exits

    return 0;
}
