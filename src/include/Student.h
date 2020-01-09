#ifndef Student_H
#define Student_H

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
	MyTerm();
	MyTerm(int _no);
	void setno(int _no);
	int getno() const;
	void setCourses(std::map<Presented_Course*, float> _courses);
	std::map<Presented_Course*, float> getCourses() const;
	void addCourse(Presented_Course* course, float score);
	float getScoreofCourse(Presented_Course* course) const;
};

class Student : public User {
protected:
	std::string field;
	float grade;
	std::vector<MyTerm> terms;
public:
	Student();
	void setField(std::string _field);
	std::string getField() const;
	void setGrade(float _grade);
	float getGrade() const;
	void setTerms(std::vector<MyTerm> _terms);
	std::vector<MyTerm> getTerms() const;
	void addTerm(MyTerm term);
	void setScoreofCourse(Presented_Course* course, float score);
	float getScoreofCourse(Presented_Course* course) const;
};

class Guest_Student : public Student {
public:
	// TuitionStatus;
	// compute tuition
};

#endif // Student_H
