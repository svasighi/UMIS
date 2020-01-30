#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <map>
#include "User.h"
#include "Course.h"

class MyTerm {
protected:
	int no;
		short status;
	// term created, not registered(0)
	// preliminary registration confirmed by student(1)
	// preliminary registration rejected by professor(-1)
	// preliminary registration confirmed by professor(2)
	// registration in action(3)
	// restoration in action(4)
	// studying(5)
	// passed(6)
	// provisional(7)
	// removed(8)
	std::map<Presented_Course*, float> courses;
public:
	MyTerm();
	MyTerm(int _no);
	void setno(int _no);
	int getno() const;
	void setStatus(short _status);
	short getStatus() const;
	void setCourses(std::map<Presented_Course*, float> _courses);
	std::map<Presented_Course*, float> getCourses() const;
	void addCourse(Presented_Course* course, float score);
	void removeCourse(Presented_Course* course);
	float getScoreofCourse(Presented_Course* course) const;
	int numberofcredits() const;
};

class Student : public User {
protected:
	std::string field;
	float grade;
	std::map<int, MyTerm> terms;
public:
	// FullInformation;
	// WeeklySchedule;
	// ExamsSchedule;
	Student();
	void setField(std::string _field);
	std::string getField() const;
	void setGrade(float _grade);
	float getGrade() const;
	void setTerms(std::map<int, MyTerm> _terms);
	std::map<int, MyTerm> getTerms() const;
	void addTerm(MyTerm term);
	void setScoreofCourse(Presented_Course* course, float score);
	float getScoreofCourse(Presented_Course* course) const;
	void setTermStatus(int term_no, short status);
	short getTermStatus(int term_no) const;
	};

class Tuition_Student : public Student {
protected:
	int type; // guest(0) or transitional(1) or night(2)
public:
	int computeTuition(int term_no);
};

#endif // STUDENT_H
