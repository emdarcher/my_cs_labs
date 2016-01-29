
#ifndef GPA_H
#define GPA_H

#include "GPAInterface.h"

class GPA : GPAInterface {
    private:
        map<unsigned long long int,StudentInterface*> student_map;
        set<StudentInterface*,Comparator> student_set;
        double grade_to_points(string grade);
    public:
        GPA(void);
        virtual ~GPA(void);

		virtual map<unsigned long long int,StudentInterface*> getMap();
		virtual set<StudentInterface*,Comparator> getSet();
		virtual bool importStudents(string mapFileName, string setFileName);
		virtual bool importGrades(string fileName);
		virtual string querySet(string fileName);
		virtual string queryMap(string fileName);
		virtual void clear();
};

#endif
