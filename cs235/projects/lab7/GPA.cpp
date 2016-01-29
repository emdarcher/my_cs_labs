
#include "GPA.h"


GPA::GPA(){

}

GPA::~GPA(){}


map<unsigned long long int,StudentInterface*> GPA::getMap(){
    return student_map;
}
set<StudentInterface*,Comparator> GPA::getSet(){
    return student_set;
}

int GPA::count_file_lines(string in_file_name){
    int lc;
    string linestr;
    ifstream in_file(in_file_name);
    if(in_file.is_open()){
        while(getline(in_file, linestr)){
            ++lc; 
        }
        in_file.close();
        return lc;
    }
    return NO_FILE;
}


bool GPA::importStudents(string mapFileName, string setFileName){
    string linestr;

    int mapFile_lc;
    int setFile_lc;
    mapFile_lc = count_file_lines(mapFileName);
    setFile_lc = count_file_lines(setFileName);
    if((mapFile_lc == NO_FILE) || (setFile_lc == NO_FILE)){
        //if any file doesn't exist
        return false; 
    } else if((mapFile_lc % 4 != 0) || (setFile_lc % 4 != 0)){
        //if any file doesn't have a correct line count 
        //cout << "incorrect line count!\n";
        return false;
    }  

    ifstream mapFile(mapFileName);
    ifstream setFile(setFileName);
    if(!mapFile.is_open() || !setFile.is_open()){
        //the any file does't exist
        return false; 
    }
    //string linestr;
    
    unsigned long long int id; 
    string name, address, phone_number;
    while(!mapFile.eof()){
        getline(mapFile, linestr);
        istringstream iss_line(linestr);
        iss_line >> id; 
        getline(mapFile, name);
        //name = linestr;
        getline(mapFile, address);
        //address = linestr;
        getline(mapFile, phone_number);
        //phone_number = linestr;
   
        student_map[id] = new Student(id, name, address, phone_number);
    }
    mapFile.close();
    while(!setFile.eof()){
        getline(setFile, linestr);
        istringstream iss_line(linestr);
        iss_line >> id; 
        getline(setFile, name);
        //name = linestr;
        getline(setFile, address);
        //address = linestr;
        getline(setFile, phone_number);
        //phone_number = linestr;
        
        student_set.insert( new Student(id, name, address, phone_number) );
    }
    setFile.close();
    return true;
}
bool GPA::importGrades(string fileName){
    return false;
}
string GPA::querySet(string fileName){
    return "";
}
string GPA::queryMap(string fileName){
    return "";
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
