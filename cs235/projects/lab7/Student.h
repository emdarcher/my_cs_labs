
#ifndef STUDENT_H
#define STUDENT_H

#include "StudentInterface.h"


class Student : public StudentInterface {
    private:
        unsigned long long int id;
        string name;
        string address;
        string phone_number;
        double gpa;
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
