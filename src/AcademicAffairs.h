#ifndef ACADEMIC_H
#define ACADEMIC_H

#include <string>
#include <map>
#include <algorithm>
#include "User.h"
#include "Student.h"

class Faculty;

class AcademicAffairsStaff : public User {
protected:
	std::string career;
	std::map<int, Student*> students;
public:
	AcademicAffairsStaff() {}
	AcademicAffairsStaff(int _username, std::string _password, std::string _firstname, std::string _lastname, std::string _career = "", short _departmentcode = 0)
		: career(_career), User(_username, _password, _firstname, _lastname, _departmentcode, 0) {}
	void setCareer(std::string);
	std::string getCareer(void) const;
	void setStudents(std::map<int, Student*>);
	std::map<int, Student*> getStudents(void) const;
};

class TopAcademicAffairsStaff : public AcademicAffairsStaff {

public:
	TopAcademicAffairsStaff() {}
	TopAcademicAffairsStaff(int _username, std::string _password, std::string _firstname, std::string _lastname, std::string _career = "")
		: AcademicAffairsStaff(_username, _password, _firstname, _lastname, _career, 0) {}
	void changeDepartmentHead(Faculty*);
	bool changePassword(std::string current_pass, std::string new_pass);
};

class DepartmentAcademicAffairsStaff : virtual public AcademicAffairsStaff {
protected:
	std::vector<Course*> courses;
	std::vector<PresentedCourse*> PresentedCourses;
public:
	DepartmentAcademicAffairsStaff() {}
	DepartmentAcademicAffairsStaff(int _username, std::string _password, std::string _firstname, std::string _lastname, short _departmentcode, std::string _career = "")
		: AcademicAffairsStaff(_username, _password, _firstname, _lastname, _career, _departmentcode) {}
	//active or diactive time conflict
	//activate prequisit or co requisit
	void setCourses(std::vector<Course*>);
	std::vector<Course*> getCourses(void) const;
	void setPresentedCourses(std::vector<PresentedCourse*>);
	std::vector<PresentedCourse*> getPresentedCourses(void) const;
	bool changePassword(std::string current_pass, std::string new_pass);
};

#endif // ACADEMIC_H
