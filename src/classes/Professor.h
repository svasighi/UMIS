#include "AcademicAffairs.h"
#include "User.h"
#include "Student.h"
#include "Course.h"
#include "..\include\md5.h"

// .............................PROFESSOR......................................

class Professor : public User {
protected:
	std::vector<Presented_Course*> courses; //list of presented courses
	std::vector<Students*> course_students; //
public:
    void ChangePassword(std::string current_pass, std::string new_pass); //forward definition
    void EnterGrades(Presented_Course presented_course , float grade) {
        
        MyTerm myterm;
        myterm.courses.insert.insert(pair<Presented_Course*, float>(presented_course, grade));
   
    }
};
// .............................AdjunctProfessor......................................

class AdjunctProfessor : public Professor { 


//access grades list

};
// .............................Degree......................................
class Degree
{
priavte:
    int ID;
    std::string DegreeName;

public:
    inline void SetID(int FieldID){ ID = FieldID;}
    inline std::String GetID(void) const {return ID;}
    inline void SetDegreeName(std::String fieldname){FieldName = fieldname;}
    inline std::String GetDegreeName(void) const {return DegreeName;}


};
// .............................Faculty......................................
class Faculty : public AdjunctProfessor{
//?? -> apply enrollments
	Degree degree;
	bool IsSupervisor;
	bool IsHead; 
	std::vector<Student*> supervised_students;

};
// .............................DepartmentAcademicAffairsStaff......................................

class DepartmentAcademicAffairsStaff : public AcademicAffairsStaff {
    std::vector<Presented_Course*> courses;
public:
    void ChangePassword(std::string current_pass, std::string new_pass){}; //forward definition
};
