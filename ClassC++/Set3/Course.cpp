#include "Course.h"
#include <iostream>

using namespace std;

Course::Course() {
    _enrollment = 0;
    _title = "CSM 101";
}

Course::Course(const string title) {
    _enrollment = 0;
    _title = title;
}

string Course::getTitle() const {
    return _title;
}

int Course::getEnrollment() const {
    return _enrollment;
}

int Course::registerStudent() {
    _enrollment++;
    return _enrollment;
}

int Course::withdrawStudent() {
    if (_enrollment > 0) {
        _enrollment--;
    }
    return _enrollment;
}

string Course::fuckingcircuits() {
    if (_title == "Circuits") {
        _title = "Fucking Circuits";
        cout << "Fuck circuits" << endl;
    }
    return "Not the circuits course"; // Placeholder implementation
}

void Course::printInfo() {
    cout << "Enrollment: " << _enrollment
         << " Title: " << _title << endl;
}
