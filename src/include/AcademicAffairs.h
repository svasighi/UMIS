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
	void setCareer(std::string);
	std::string getCareer(void) const;
	void setStudents(std::map<int, Student*>);
	std::map<int, Student*> getStudents(void) const;
};

class TopAcademicAffairsStaff : public AcademicAffairsStaff {

public:
	void changeDepartmentHead(Faculty*);
	void changePassword(std::string current_pass, std::string new_pass) {} //forward definition
};

// .............................DepartmentAcademicAffairsStaff......................................
class DepartmentAcademicAffairsStaff : virtual public AcademicAffairsStaff {
protected:
	std::vector<Course*> courses;
	std::vector<PresentedCourse*> PresentedCourses;
public:
	DepartmentAcademicAffairsStaff() {}

	//active or diactive time conflict
	//activate prequisit or co requisit
	void setCourses(std::vector<Course*>);
	std::vector<Course*> getCourses(void) const;
	void setPresentedCourses(std::vector<PresentedCourse*>);
	std::vector<PresentedCourse*> getPresentedCourses(void) const;
	void changePassword(std::string current_pass, std::string new_pass) {} //forward definition
};

#endif // ACADEMIC_H
