#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <string>
#include <vector>
#include <map>
#include "AcademicAffairs.h"
#include "User.h"
#include "Student.h"
#include "Course.h"
#include "..\classes\md5.cpp"

// .............................PROFESSOR......................................

class Professor : public User {
protected:
	std::map<Presented_Course*, std::vector<Student*>> courses; //list of presented courses with their students
public:
	void ChangePassword(std::string current_pass, std::string new_pass); //forward definition
	void enterScore(Presented_Course* presented_course , Student* student, float score) {
		
	}
};
// .............................AdjunctProfessor......................................

class AdjunctProfessor : public Professor { 


};

// .............................Faculty......................................
class Faculty : public Professor {
//?? -> apply enrollments
	int degree;
	bool isSupervisor;
	bool isHead; 
	std::vector<Student*> supervised_students;

};
// .............................DepartmentAcademicAffairsStaff......................................

class DepartmentAcademicAffairsStaff : public AcademicAffairsStaff {
protected:
	std::vector<Course*> courses;
	std::vector<Presented_Course*> presented_courses;
public:
	void ChangePassword(std::string current_pass, std::string new_pass); //forward definition
};

#endif // PROFESSOR_H
