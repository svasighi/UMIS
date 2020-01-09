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
	std::vector<Presented_Course*> courses; //list of presented courses
public:
	void setCourses(std::vector<Presented_Course*> _courses) {
		courses = _courses;
	}

	std::vector<Presented_Course*> getCourses() const {
		return courses;
	}

	void addCourse(Presented_Course* course) {
		courses.push_back(course);
	}

	void removeCourse(Presented_Course* course) {
		courses.erase(find(courses.begin(), courses.end(), course));
	}
	
	void enterScore(Presented_Course* presented_course , Student* student, float score) {
		student->setScoreofCourse(presented_course, score);
	}
	
	void ChangePassword(std::string current_pass, std::string new_pass); //forward definition
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
