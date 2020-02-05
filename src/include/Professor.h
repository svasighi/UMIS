#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <string>
#include <vector>
#include <map>
#include "User.h"
#include "Course.h"
#include "Student.h"
#include "AcademicAffairs.h"
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
	std::vector<Presented_Course*> getCourses(void) const;
	void addCourse(Presented_Course*);
	void removeCourse(Presented_Course*);
	void replyToObjecton(Student*, Presented_Course*, std::string);
	std::string viewObjectonReply(Student*, Presented_Course*) const;
	static std::map<int,Professor*> readAllProfessors(void);
	void changePassword(std::string current_pass, std::string new_pass); //forward definition
};

// .............................AdjunctProfessor......................................
class AdjunctProfessor : public Professor { 
	AdjunctProfessor(int _username, std::string _password, std::string _firstname, std::string _lastname, int _departmentcode)
		: User(_username, _password, _firstname, _lastname, _departmentcode) {}
};

// .............................Faculty......................................
class Faculty : public Professor {
protected:
	int degree;
	bool is_supervisor;
	std::vector<Student*> supervised_students;
public:
	Faculty() {} //default constructor
	
	void setDegree(int _degree);
	int getDegree(void) const;
	void setAsSupervisor(void);
	bool getisSupervisor (void) const;
	void setSupervisedStudents(std::vector<Student*>);
	std::vector<Student*> getSupervisedStudents(void) const;
	void addSupervisedStudents(Student*);
	void removeSupervisedStudents(Student*);
	void applyEnrollment(Student*);
};

// .............................GroupManager......................................
class GroupManager : public Faculty {
	//PreEnrollment_Stats
	std::map<int,Presented_Course*> group_courses;
public:
	GroupManager(){}
	std::map<int,Presented_Course*> getGroupCourses();
	void setGroupCourses(std::map<int,Presented_Course*>);
	void createGroupCourse(int ,std::string ,int ,int ,int ,Professor* ,int ,std::vector<Course*> ,std::vector<Course*>);
	void deleteGroupCourse(Presented_Course*);
	void updateGroupCourse(Presented_Course*);

};

// .............................DepartmentAcademicAssistant......................................
class DepartmentAcademicAssistant : public Faculty, public DepartmentAcademicAffairsStaff {

public:
	DepartmentAcademicAssistant(){};
};

// .............................DepartmentHead......................................
class DepartmentHead : public Faculty {
 	std::map<int,Professor*> professors;
public:
	DepartmentHead(Faculty*);
	int calculateProfessorAssessmentSum(Professor*) const;
	std::map<int,Professor*> getDepartmentProfessors(void) const;
	void setDepartmentProfessors(std::map<int,Professor*>);
	std::map<Presented_Course*, std::vector<char>> ProfessorAssessment(Professor*) const;
	void addProfessor(int, std::string, std::string, std::string);
	void addAdjunctProfessor(int, std::string, std::string, std::string); //sadasdasdasd
	void addDepartmentAcademicAffairsStaff(int, std::string, std::string, std::string);
	
	void changeToFacutly(Professor*); //sadasdasdasd
	void changeToGroupManager(Faculty*); //sadasdasdasd
	
	void deleteProfessor(Professor*);
	void readAllDepartmentProfessors(void);
	void calcSalary(int*, int) const;
};

// .............................DepartmentAcademicAffairsStaff......................................
class DepartmentAcademicAffairsStaff : public AcademicAffairsStaff {
protected:
	std::vector<Course*> courses;
	std::vector<Presented_Course*> presented_courses;
public:
	//active or diactive time conflict
	//activate prequisit or co requisit
	void setCourses(std::vector<Course*>);
	std::vector<Course*> getCourses(void) const;
	void setPresentedCourses(std::vector<Presented_Course*>);
	std::vector<Presented_Course*> getPresentedCourses(void) const;
};

#endif // PROFESSOR_H
