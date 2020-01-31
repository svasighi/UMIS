#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <string>
#include <vector>
#include <map>
#include "User.h"
#include "Course.h"
#include "Student.h"
#include "AcademicAffairs.h"
#include "md5.h"
#include "BinaryFile.h"
#include <algorithm>

// .............................PROFESSOR......................................
class Professor : virtual public User {
protected:
	std::vector<Presented_Course*> courses; //list of presented courses
public:
	Professor() {}
	Professor(int _username, std::string _password, std::string _firstname, std::string _lastname, int _departmentcode)
		: User(_username, _password, _firstname, _lastname, _departmentcode) {}
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
	Faculty() {} //default constructor
	
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
class DepartmentChief : public Faculty, public DepartmentAcademicAffairsStaff {

};

// .............................DepartmentHead......................................
class DepartmentHead : public Faculty {
 	std::vector<Professor*> professors;
public:
	int CalculateProfessorAssessmentSum(Professor) const;
	std::vector<Professor*> getProfessors(void) const;
	void setProfessors(std::vector<Professor*>);
	std::map<Presented_Course*, std::vector <short>> ProfessorAssessment(Professor) const;
	void addProfessor(int, std::string, std::string, std::string);
	void deleteProfessor(Professor*);
	void ReadAllProfessors(void);
	void calcSalary(int*, int ) const;
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
};

#endif // PROFESSOR_H
