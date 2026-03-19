#include "Course.h"
#include <iostream>
using namespace std;

int main() {
    // Test constructors
    Course defaultCourse;                    // Default constructor
    Course titledCourse("Algebra 101");      // String constructor
    
    // Test getters
    cout << "Default course enrollment: " << defaultCourse.getEnrollment() << endl;
    cout << "Titled course: " << titledCourse.getTitle() << endl;
    
    // Test registration and withdrawal
    titledCourse.registerStudent();
    titledCourse.registerStudent();
    titledCourse.withdrawStudent();
    
    // Print final info
    defaultCourse.printInfo();
    titledCourse.printInfo();
    
    // Test more registrations
    cout << "After 3 more registrations: " << titledCourse.registerStudent() << endl;
    cout << "Current enrollment: " << titledCourse.getEnrollment() << endl;

    Course copyCourse(titledCourse); // Test copy constructor
    copyCourse.printInfo(); // Should match titledCourse info

    Course assignedCourse; // Test assignment operator
    assignedCourse = titledCourse;
    assignedCourse.printInfo(); // Should match titledCourse info

    {
        Course tempCourse("Temporary Course");
        tempCourse.registerStudent();
        tempCourse.printInfo();
    } // tempCourse goes out of scope here, destructor should be called         

    Course randomcourse("Circuits");
    string x;
    x = randomcourse.fuckingcircuits(); // Test the fuckingcircuits method
    cout << x << endl;


    return 0;
}
