#include "Student.h"

Student::Student(unsigned long long int id, string name, 
                    string address, string phone_number){
    this->id = id;
    this->name = name;
    this->address = address;
    this->phone_number = phone_number;
    //this->gpa = gpa;
    this->num_courses = 0;
    this->grade_sum = 0;
}

Student::~Student(){}

unsigned long long int Student::getID(){
    return this->id;
}

string Student::getName(){
    return this->name;
}
string Student::getGPA(){
    stringstream ss;
    ss << setprecision(2) << fixed << gpa; 
    return ss.str();
}
void Student::addGPA(double classGrade){
    this->num_courses++;
    this->grade_sum += classGrade;
    this->gpa = this->grade_sum / (double)this->num_courses; 
}
string Student::toString(){
    stringstream ss;
    ss << id << "\n";
    ss << name << "\n";
    ss << address << "\n";
    ss << phone_number << "\n";
    ss << setprecision(2) << fixed << gpa;
    return ss.str();
}
