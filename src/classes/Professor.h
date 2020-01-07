#include <iostream>
#include "AcademicAffairs.h"
#include "User.h"
#include "Student.h"
#include "..\include\md5.h"

// .............................PROFESSOR......................................

class Professor : public User{

public:
    void ChangePassword(std::string current_pass, std::string new_pass); //forward definition
    std::vector<Presented_Course*> courses;
	std::vector<Presented_Course*> course_students;
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

class DepartmentAcademicAffairsStaff :public AcademicAffairsStaff{
    std::vector<Presented_Course*> courses;
public:
    void ChangePassword(std::string current_pass, std::string new_pass); //forward definition
};

int main(){

}
