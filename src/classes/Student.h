#pragma once
#include <string>
#include <vector>
#include <map>
#include "Course.h"
#include "User.h"

class MyTerm {
protected:
	int no;
	std::map<Presented_Course*, float> courses;
public:

};

class Student : public User {
protected:
	std::string field;
	float grade;
	std::vector<MyTerm> terms;
public:
	// getFullInformation();
	// getWeeklySchedule();
	// getExamsSchedule();
};

class Guest_Student : public Student {
public:
	// getTuitionStatus();
	// compute tuition
};
