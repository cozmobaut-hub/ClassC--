#ifndef COURSE_H
#define COURSE_H

#include <string>

class Course {
private:
    int _enrollment;
    std::string _title;

public:
    Course();
    Course(const std::string title);
    std::string getTitle() const;
    int getEnrollment() const;
    int registerStudent();
    int withdrawStudent();
    void printInfo();
};

#endif
