#pragma once
#include <string>
#include <vector>
#include "Professor.h"
#include "TimeDate.h"

class Course {
protected:
	int credit;
	std::string name;
	int type;
	std::vector<Course*> prerequisite;
	std::vector<Course*> corequisite;
public:

};

class Presented_Course : public Course {
protected:
	Professor* course_professor;
	int capacity;
	Course_Time course_time;
	std::string course_location;
	Time finalexam_time;
public:

};