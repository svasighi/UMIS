#ifndef Course_H
#define Course_H

#include <string>
#include <vector>
#include "Professor.h"
#include "TimeDate.h"

class Course {
protected:
	short credit;
	std::string name;
	short type;
	std::vector<Course*> prerequisite;
	std::vector<Course*> corequisite;
public:
	Course();
	void setCredit(short _credit);
	short getCredit();
	void setName(std::string _name);
	std::string getName();
	void setType(short _type);
	short getType();
	void setPrerequisite(std::vector<Course*> _prerequisite);
	void addPrerequisite(Course* course);
	std::vector<Course*> getPrerequisite();
	void setCorequisite(std::vector<Course*> _corequisite);
	void addCorequisite(Course* course);
	std::vector<Course*> getCorequisite();
};

class Presented_Course : public Course {
protected:
	Professor* course_professor;
	int capacity;
	Course_Time course_time;
	std::string course_location;
	Time finalexam_time;
public:
	Presented_Course();
	void setCourseProfessor(Professor* _course_professor);
	Professor* getCourseProfessor();
	void setCapacity(int _capacity);
	int getCapacity();
	void setCourseTime(Course_Time _course_time);
	Course_Time getCourseTime();
	void setCourseLocation(std::string _course_location);
	std::string getCourseLocation();
	void setFinalExamTime(Time _finalexam_time);
	Time getFinalExamTime();
};

#endif // Course_H
