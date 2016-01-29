
#ifndef STUDENT_H
#define STUDENT_H

#include "StudentInterface.h"
#include <iomanip>
#include <string>
#include <sstream>
#include <iostream>

class Student : public StudentInterface {
    private:
        unsigned long long int id;
        string name;
        string address;
        string phone_number;
        double gpa;
        int num_courses;
        double grade_sum;
    public:
        Student(unsigned long long int id, string name,
                    string address, string phone_number, double gpa);
        virtual ~Student(void);

		virtual unsigned long long int getID();

		virtual string getName();
		virtual string getGPA();
		virtual void addGPA(double classGrade);
		virtual string toString();

};

#endif
