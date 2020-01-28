#ifndef ACADEMIC_H
#define ACADEMIC_H

#include "User.h"
#include "Student.h"

class AcademicAffairsStaff : public virtual User {
protected:
	std::string career;
	std::vector<Student*> students;
public:
	void setCareer(std::string);
	std::string getCareer(void) const;
	void setStudents(std::vector<Student*>);
	std::vector<Student*> getStudents(void) const;
};

class TopAcademicAffairsStaff : public AcademicAffairsStaff {
	
public:
	void changeDepartmentHead(Professor* prof); //forward definitions
};

#endif // ACADEMIC_H
