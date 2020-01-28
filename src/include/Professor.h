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
class Professor : public virtual User {
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
	bool is_supervisor;
	bool is_head; 
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
// .............................DepartmentManager......................................
class DepartmentManager : public Faculty {
	//PreEnrollment_Stats
	//gozaresh 110 baraye daneshkade khod
};
// .............................DepartmentManager......................................
class DepartmentChief: public Faculty , AcademicAffairsStaff{

};
// .............................DepartmentHead......................................

class DepartmentHead : public Faculty {
	//arzeshyabi har ostad
	//add prof
	//access to all proff & calc salary
};

// .............................DepartmentAcademicAffairsStaff......................................
class DepartmentAcademicAffairsStaff : public AcademicAffairsStaff {
protected:
	std::vector<Course*> courses;
	std::vector<Presented_Course*> presented_courses;
public:
	//active or diactive time conflict
	//activate prequisit
	void setCourses(std::vector<Course*>);
	std::vector<Course*> getCourses(void) const;
	void setPresentedCourses(std::vector<Presented_Course*>);
	std::vector<Presented_Course*> getPresentedCourses(void) const;
	void changePassword(std::string current_pass, std::string new_pass); //forward definition
};

#endif // PROFESSOR_H
