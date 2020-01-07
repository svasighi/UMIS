#pragma once
#include <string>
#include <vector>
#include <map>
#include "TimeDate.h"

class Course {
protected:
	int credit;
	std::string name;
	int type;
	std::vector<Course*> prerequisite;
	std::vector<Course*> corequisite;
};

class Presented_Course : public Course {
protected:
	Professor* course_professor;
	int capacity;
	Course_Time course_time;
	std::string course_location;
	Time finalexam_time;
};

class Person {
protected:
	std::string username;
	std::string password;
	std::string firstName;
	std::string lastName;
public:
	void setPassword(std::string _password);
};

class MyTerm {
protected:
	int no;
	std::map<Presented_Course*, float> courses;
};

class Student : public Person {
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

class Professor : public Person {
protected:
	std::vector<Presented_Course*> courses;
	std::vector<Presented_Course*> course_students;
};

class Invited_Professor : public Professor {
	
};

class Faculty : public Professor {
protected:
	int degree;
	bool issupervisor;
	std::vector<Student*> supervise_students;
};
