#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <map>
#include "User.h"
#include "Course.h"
#include "TimeDate.h"

class MyCourse {
protected:
	float score;
	short status;
	// status:
	// 0 : added in preliminary registration
	// 1 : registered
	// 2 : wait
	// 3 : score confirmed by professor
	// 4 : passed
	// 5 : refused
	// 6 : emergency drop
	std::map<std::string, short> evaluation;
public:
	MyCourse();
	void setScore(float _score);
	float getScore() const;
	void setStatus(short _status);
	short getStatus() const;

};

class MyTerm {
protected:
	int no;
	short status;
	// status:
	// 0 : term created
	// 1 : preliminary registration confirmed by student
	//-1 : preliminary registration rejected by professor
	// 2 : preliminary registration confirmed by professor
	// 3 : registration in action
	// 4 : reshuffle in action
	// 5 : studying
	// 6 : passed
	// 7 : provisional
	// 8 : removed
	Time registration_begin_time;
	std::map<Presented_Course*, MyCourse> courses;
public:
	MyTerm();
	MyTerm(int _no);
	void setno(int _no);
	int getno() const;
	void setStatus(short _status);
	short getStatus() const;
	void setRegistrationBeginTime(Time _registration_begin_time);
	Time getRegistrationBeginTime() const;
	void setCourses(std::map<Presented_Course*, MyCourse> _courses);
	std::map<Presented_Course*, MyCourse> getCourses() const;
	void addCourse(Presented_Course* course);
	void removeCourse(Presented_Course* course);
	void setScoreofCourse(Presented_Course* course, float score);
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
	void setTermRegistrationBeginTime(int term_no, Time registration_begin_time);
	Time getTermRegistrationBeginTime(int term_no) const;
};

class Tuition_Student : public Student {
protected:
	int type;
	// type:
	// 0 : guest student
	// 1 : transitional student
	// 2 : night student
public:
	Tuition_Student();
	void setType(short _type);
	short getType() const;
	int computeTuition(int term_no);
};

#endif // STUDENT_H
