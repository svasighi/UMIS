#ifndef ACADEMIC_H
#define ACADEMIC_H

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "User.h"
#include "Student.h"
#include "Professor.h"
#include <exception>

class AcademicAffairsStaff : virtual public User {
protected:
	std::string career;
	std::map<int,Student*> students;
public:
	void setCareer(std::string);
	std::string getCareer(void) const;
	void setStudents(std::map<int,Student*>);
	std::map<int,Student*> getStudents(void) const;
};

class TopAcademicAffairsStaff : public AcademicAffairsStaff {
	
public:
	void  changeDepartmentHead(Faculty*);
	void readAllStudents(void);
};

#endif // ACADEMIC_H
