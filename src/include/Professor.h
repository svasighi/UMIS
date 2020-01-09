#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <string>
#include <vector>
#include <map>
#include "AcademicAffairs.h"
#include "User.h"
#include "Student.h"
#include "Course.h"

// .............................PROFESSOR......................................

class Professor : public User {
protected:
	std::vector<Presented_Course*> courses; //list of presented courses
public:
<<<<<<< HEAD
	void setCourses(std::vector<Presented_Course*>);
	std::vector<Presented_Course*> getCourses() const;
	void addCourse(Presented_Course*);
	void removeCourse(Presented_Course*);
	void enterScore(Presented_Course* , Student*, float);
=======
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
	
>>>>>>> d433c210ebd7b54b1192673e6238ea9c4f1264fc
	void ChangePassword(std::string current_pass, std::string new_pass); //forward definition
};
// .............................AdjunctProfessor......................................

class AdjunctProfessor : public Professor { 


};

// .............................Faculty......................................
class Faculty : public Professor {
protected:
	int degree;
	bool isSupervisor;
	bool isHead; 
	std::vector<Student*> supervised_students;
public:
	int getDegree (void) const;
	void setDegree(const int);
	bool isSupervisor (void) const;
	void setAsSupervisor(void);
	bool isHead (void) const;
	void setAsHead(void);
	void setSupervised_Students(std::vector<Student*>);
	std::vector<Student*> getSupervised_Students(void) const;
	void addSupervised_Students(Student*);
	void removeSupervised_Students(Student*);
	void applyEnrollment(Student);
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
