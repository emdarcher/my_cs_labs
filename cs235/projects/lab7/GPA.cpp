
#include "GPA.h"


GPA::GPA(){

}

GPA::~GPA(){
    clear();
}


map<unsigned long long int,StudentInterface*> GPA::getMap(){
    return student_map;
}
set<StudentInterface*,Comparator> GPA::getSet(){
    return student_set;
}

int GPA::count_file_lines(string in_file_name){
    int lc = 0;
    string linestr = "";
    ifstream in_file(in_file_name);
    if(in_file.is_open()){
        while(getline(in_file, linestr, '\n')){
            ++lc; 
        }
        in_file.close();
        return lc;
    }
    return NO_FILE;
}


bool GPA::importStudents(string mapFileName, string setFileName){
    string linestr =  "";

    int mapFile_lc = NO_FILE;
    int setFile_lc = NO_FILE;
    mapFile_lc = count_file_lines(mapFileName);
    setFile_lc = count_file_lines(setFileName);
    //cout << "filenames: mapFileName = " << mapFileName 
    //        << " setFileName = " << setFileName << "\n";
    if((mapFile_lc == NO_FILE) || (setFile_lc == NO_FILE)){
        //if any file doesn't exist
        //cout << "file doesn't exist!\n";
        return false; 
    } else if((mapFile_lc % 4 != 0) || (setFile_lc % 4 != 0)){
        //if any file doesn't have a correct line count 
        //cout << "incorrect line count! mapFile_lc = " << mapFile_lc 
        //        << " setFile_lc = " << setFile_lc <<"\n";
        return false;
    }  

    ifstream mapFile(mapFileName);
    ifstream setFile(setFileName);
    
    unsigned long long int id = -1; 
    string name = ""; 
    string address = ""; 
    string phone_number = "";

    while(getline(mapFile, linestr)){
        istringstream iss_line(linestr);
        iss_line >> id; 
        getline(mapFile, name);
        getline(mapFile, address);
        getline(mapFile, phone_number);
   
        student_map[id] = new Student(id, name, address, phone_number);
    }
    mapFile.close();

    while(getline(setFile, linestr)){
        istringstream iss_line(linestr);
        iss_line >> id; 
        getline(setFile, name);
        getline(setFile, address);
        getline(setFile, phone_number);
        
        student_set.insert( new Student(id, name, address, phone_number) );
    }
    setFile.close();
    return true;
}
bool GPA::importGrades(string fileName){
    string linestr = "";
    int file_lc = NO_FILE;
    file_lc = count_file_lines(fileName);
    if((file_lc == NO_FILE) || (file_lc % 3 != 0)){
        return false;
    }
    
    ifstream gradeFile(fileName);

    unsigned long long int id = -1;
    
    string course = ""; 
    string grade = "";
    while(getline(gradeFile, linestr)){
        istringstream iss_line(linestr);
        iss_line >> id;
        getline(gradeFile, course);
        getline(gradeFile, linestr);
        istringstream grade_ss(linestr);
        grade_ss >> grade; 
        double points = grade_to_points(grade);
        //cout << "read in grade " << grade << "\n"; 
        if(student_map.count(id)){
            student_map[id]->addGPA(points);
        }  
        for( StudentInterface* student : student_set ){
            if(student->getID() == id){
                student->addGPA(points);
            } 
        }

    }
    gradeFile.close();
    return true;
}
string GPA::querySet(string fileName){
    ifstream queryFile(fileName);
    if(!queryFile.is_open()){
        return "";
    }
    stringstream ss;
    unsigned long long int id = -1;
    while(queryFile >> id){
        for( StudentInterface* student : student_set ){
            if(student->getID() == id){
                ss << id << " " << student->getGPA() << " " 
                    << student->getName() << "\n";
            }
        }
    }
    return ss.str();
}
string GPA::queryMap(string fileName){
    ifstream queryFile(fileName);
    if(!queryFile.is_open()){
        return "";
    }
    stringstream ss;
    unsigned long long int id = -1;
    while(queryFile >> id){
        //check if that id exists
        if(student_map.count(id)){
            ss << id << " " << student_map[id]->getGPA() << " "
                << student_map[id]->getName() << "\n";
        }
    }
    return ss.str();
}
void GPA::clear(){
    
    for( auto& student : student_map ){
        delete student.second;
    }
    student_map.clear();

    for( StudentInterface* student : student_set ){
        delete student; 
    }
    student_set.clear();
}

double GPA::grade_to_points(string grade){

		 /* Use the following point values for each grade.
		 *
		 *		  A = 4.0  A- = 3.7
		 *	B+ = 3.4  B = 3.0  B- = 2.7
		 *	C+ = 2.4  C = 2.0  C- = 1.7
		 *	D+ = 1.4  D = 1.0  D- = 0.7
		 *		  E = 0.0
		 */
    double out_points = 0;
    if(grade == "A"){
        out_points = 4.0;
    } else if(grade == "A-"){
        out_points = 3.7;
    } else if(grade == "B+"){
        out_points = 3.4;
    } else if(grade == "B"){
        out_points = 3.0;
    } else if(grade == "B-"){
        out_points = 2.7;
    } else if(grade == "C+"){
        out_points = 2.4;
    } else if(grade == "C"){
        out_points = 2.0;
    } else if(grade == "C-"){
        out_points = 1.7;
    } else if(grade == "D+"){
        out_points = 1.4;
    } else if(grade == "D"){
        out_points = 1.0;
    } else if(grade == "D-"){
        out_points = 0.7;
    } else if(grade == "E"){
        out_points = 0.0;
    } else {
        out_points = 0.0; 
    }
    return out_points;
}
