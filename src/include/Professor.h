#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>
#include "User.h"
#include "Course.h"
#include "Student.h"
#include "AcademicAffairs.h"

// .............................PROFESSOR......................................
class Professor : virtual public User {
protected:
	std::vector<PresentedCourse*> courses; //list of presented courses
public:
	Professor() {}
	Professor(int _username, std::string _password, std::string _firstname, std::string _lastname, short _departmentcode, short _groupcode = 0)
		: User(_username, _password, _firstname, _lastname, _departmentcode, _groupcode) {}
	void setCourses(const std::vector<PresentedCourse*>&);
	std::vector<PresentedCourse*> getCourses(void) const;
	void addCourse(PresentedCourse*);
	void removeCourse(PresentedCourse*);
	void replyToObjecton(Student*, PresentedCourse*, std::string);
	std::string viewObjectonReply(Student*, PresentedCourse*) const;
};
// .............................AdjunctProfessor......................................
class AdjunctProfessor : public Professor {
public:
	AdjunctProfessor() {}
	AdjunctProfessor(int _username, std::string _password, std::string _firstname, std::string _lastname, short _departmentcode)
		: Professor(_username, _password, _firstname, _lastname, _departmentcode) {}
	void changePassword(std::string current_pass, std::string new_pass) {} //forward definition
};

// .............................Faculty......................................
class Faculty :public Professor {
protected:
	int degree;
	bool is_supervisor;
	std::vector<Student*> supervised_students;
public:
	Faculty()
		: degree(0), is_supervisor(false) {} //default constructor
	Faculty(int _username, std::string _password, std::string _firstname, std::string _lastname, short _departmentcode, int _degree = 0, bool _is_supervisor = false)
		: degree(_degree), is_supervisor(_is_supervisor), Professor(_username, _password, _firstname, _lastname, _departmentcode) {}
	void setDegree(int _degree);
	int getDegree(void) const;
	void setAsSupervisor(bool = true);
	bool getisSupervisor(void) const;
	void setSupervisedStudents(const std::vector<Student*>&);
	std::vector<Student*> getSupervisedStudents(void) const;
	void addSupervisedStudent(Student*);
	void removeSupervisedStudent(Student*);
	void applyEnrollment(Student*);
	void changePassword(std::string current_pass, std::string new_pass) {} //forward definition
};

// .............................GroupManager......................................
class GroupManager : public Faculty {
	//PreEnrollment_Stats
	std::map<int, PresentedCourse*> group_courses;
public:
	GroupManager() {}
	void setGroupCourses(std::map<int, PresentedCourse*>);
	std::map<int, PresentedCourse*> getGroupCourses();
	void createGroupCourse(int, std::string, int, int, int, int, Professor*, int, std::vector<Course*>, std::vector<Course*>);//asasasa
	void deleteGroupCourse(PresentedCourse*);//asasasa
	void updateGroupCourse(PresentedCourse*);//asasasa
	void createGroupPresentedCourse(int, std::string, int, int, int, Professor*, int, std::vector<Course*>, std::vector<Course*>);//asasasa
	void deleteGroupPresentedCourse(PresentedCourse*);//asasasa
	void updateGroupPresentedCourse(PresentedCourse*);//asasasa
};

// .............................DepartmentAcademicAssistant......................................

class DepartmentAcademicAssistant : public Faculty, public AcademicAffairsStaff {
public:
	DepartmentAcademicAssistant() {}
};

// .............................DepartmentHead......................................
class DepartmentHead : public Faculty {
public:
	DepartmentHead() {}
	DepartmentHead(Faculty*);
	int calculateProfessorAssessmentSum(Professor*) const;
	std::map<int, Professor*> getDepartmentProfessors(void) const;
	void setDepartmentProfessors(std::map<int, Professor*>);
	std::map<PresentedCourse*, std::vector<char>> ProfessorAssessment(Professor*) const;
	void addFaculty(int, std::string, std::string, std::string);
	void deleteProfessor(Professor*);
	void readAllDepartmentProfessors(void);
	void calcSalary(int*, int) const;
};

#endif // PROFESSOR_H
