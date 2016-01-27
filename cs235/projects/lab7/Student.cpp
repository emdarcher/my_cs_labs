#include "Student.h"

Student::Student(unsigned long long int id, string name, 
                    string address, string phone_number, double gpa){
    this->id = id;
    this->name = name;
    this->address = address;
    this->phone_number = phone_number;
    this->gpa = gpa;
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
    return ss;
}
void Student::addGPA(double classGrade){

}
string Student::toString(){

}
