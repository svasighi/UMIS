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
	// 0 : suggested in preliminary enrollment
	// 1 : added in preliminary enrollment
	// 2 : enrolled
	// 3 : wait
	// 4 : score inserted but not confirmed
	// 5 : score confirmed by professor
	// 6 : passed
	// 7 : refused
	// 8 : emergency drop
	std::vector<short> assessment_answers;
	std::string review;
public:
	MyCourse();
	void setScore(float _score);
	float getScore() const;
	void setStatus(short _status);
	short getStatus() const;
	void setAssessmentAnswers(std::vector<short> _assessment_answers);
	std::vector<short> getAssessmentAnswers() const;
	void setReview(std::string _review);
	std::string getReview() const;
};

class MyTerm {
protected:
	int no;
	short status;
	// status:
	// 0 : term created
	// 1 : preliminary enrollment confirmed by student
	//-1 : preliminary enrollment rejected by professor
	// 2 : preliminary enrollment confirmed by professor
	// 3 : enrollment in action
	// 4 : reshuffle in action
	// 5 : studying
	// 6 : passed
	// 7 : provisional
	// 8 : removed
	Time enrollment_begin_time;
	std::map<Presented_Course*, MyCourse> courses;
public:
	MyTerm();
	MyTerm(int _no);
	void setno(int _no);
	int getno() const;
	void setStatus(short _status);
	short getStatus() const;
	void setEnrollmentBeginTime(Time _enrollment_begin_time);
	Time getEnrollmentBeginTime() const;
	void setCourses(std::map<Presented_Course*, MyCourse> _courses);
	std::map<Presented_Course*, MyCourse> getCourses() const;
	int numberofCredits() const;
	// course functions
	void addCourse(Presented_Course* course);
	void removeCourse(Presented_Course* course);
	void setCourseProperties(Presented_Course* course, MyCourse properties);
	MyCourse getCourseProperties(Presented_Course* course) const;
	void setScoreofCourse(Presented_Course* course, float score);
	void setStatusofCourse(Presented_Course* course, short status);
	void setAssessmentAnswersofCourse(Presented_Course* course, std::vector<short> answers);
	void setReviewofCourse(Presented_Course* course, std::string review);
};

class Student : public User {
protected:
	std::string field;
	float grade;
	std::map<int, MyTerm> terms;
public:
	Student();
	void setField(std::string _field);
	std::string getField() const;
	void setGrade(float _grade);
	float getGrade() const;
	void setTerms(std::map<int, MyTerm> _terms);
	std::map<int, MyTerm> getTerms() const;
	// term functions
	void addTerm(MyTerm term);
	void addTerm(int term_no);
	void setTerm(int term_no, MyTerm term);
	MyTerm getTerm(int term_no) const;
	void setTermStatus(int term_no, short status);
	short getTermStatus(int term_no) const;
	void setTermEnrollmentBeginTime(int term_no, Time enrollment_begin_time);
	Time getTermEnrollmentBeginTime(int term_no) const;
	int numberofCredits(int term_no) const;
	// course functions
	void addCourse(Presented_Course* course);
	void removeCourse(Presented_Course* course);
	void setCourseProperties(Presented_Course* course, MyCourse properties);
	MyCourse getCourseProperties(Presented_Course* course) const;
	void setScoreofCourse(Presented_Course* course, float score);
	float getScoreofCourse(Presented_Course* course) const;
	void setStatusofCourse(Presented_Course* course, short status);
	short getStatusofCourse(Presented_Course* course) const;
	void setAssessmentAnswersofCourse(Presented_Course* course, std::vector<short> answers);
	std::vector<short> getAssessmentAnswersofCourse(Presented_Course* course) const;
	void setReviewofCourse(Presented_Course* course, std::string review);
	std::string getReviewofCourse(Presented_Course* course) const;
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
