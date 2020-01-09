#ifndef ACADEMIC
#define ACADEMIC

#include "User.h"
#include "Student.h"

class AcademicAffairsStaff : public User{
protected:
	std::string career;
	std::vector<Student*> students;
public:
	std::vector<Student*> getStudents(void);
};
class TopAcademicAffairsStaff : public AcademicAffairsStaff {
	std::vector<Presented_Course*> presented_courses;
public:
	void changeDepartmentHead(Professor* prof); //forward definitions
};

#endif // ACADEMIC
