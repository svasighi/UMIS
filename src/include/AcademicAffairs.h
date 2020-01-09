#ifndef ACADEMIC_H
#define ACADEMIC_H

#include "User.h"
#include "Student.h"

class AcademicAffairsStaff : public User{
protected:
	std::string career;
	std::vector<Student*> students;
public:
	std::vector<Student*> getStudents(void);
	void setStudents(std::vector<Student *>);
	std::string getCareer(void);
	void setCareer(std::string);
};
class TopAcademicAffairsStaff : public AcademicAffairsStaff {
	
public:
	void changeDepartmentHead(Professor* prof); //forward definitions
};

#endif // ACADEMIC_H
