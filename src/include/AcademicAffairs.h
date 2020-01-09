#ifndef ACADEMIC
#define ACADEMIC

#include "..\models\AcademicAffairsModel.cpp"
#include "User.h"
#include "Student.h"

class AcademicAffairsStaff : public User {
protected:
	std::string career;
	std::vector<Student*> students;
public:

};
class TopAcademicAffairsStaff : public AcademicAffairsStaff {
// list of all students 
	std::vector<Presented_Course*> presented_courses;
public:
	void changeDepartmentHead(Professor* prof); //forward definitions
};

#endif // ACADEMIC
