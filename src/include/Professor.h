#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <string>
#include <vector>
#include <map>
#include "User.h"
#include "Course.h"
#include "Student.h"
#include "AcademicAffairs.h"

// .............................PROFESSOR......................................
class Professor : public User {
protected:
	std::vector<Presented_Course*> courses; //list of presented courses
public:
	void setCourses(std::vector<Presented_Course*>);
	std::vector<Presented_Course*> getCourses() const;
	void addCourse(Presented_Course*);
	void removeCourse(Presented_Course*);
	void changePassword(std::string current_pass, std::string new_pass); //forward definition
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
	void setDegree(int _degree);
	int getDegree(void) const;
	void setAsSupervisor(void);
	bool isSupervisor (void) const;
	void setAsHead(void);
	bool isHead (void) const;
	void setSupervisedStudents(std::vector<Student*>);
	std::vector<Student*> getSupervisedStudents(void) const;
	void addSupervisedStudents(Student*);
	void removeSupervisedStudents(Student*);
	void applyEnrollment(Student);
};

// .............................DepartmentAcademicAffairsStaff......................................
class DepartmentAcademicAffairsStaff : public AcademicAffairsStaff {
protected:
	std::vector<Course*> courses;
	std::vector<Presented_Course*> presented_courses;
public:
	void setCourses(std::vector<Course*>);
	std::vector<Course*> getCourses(void) const;
	void setPresentedCourses(std::vector<Presented_Course*>);
	std::vector<Presented_Course*> getPresentedCourses(void) const;
	void changePassword(std::string current_pass, std::string new_pass); //forward definition
};

#endif // PROFESSOR_H
