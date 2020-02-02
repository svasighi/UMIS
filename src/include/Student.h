#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <map>
#include "User.h"
#include "Course.h"
#include "TimeDate.h"

class Faculty;

class MyCourse {
protected:
	float score;
	char status;
	// status:
	//-1 : unknown
	// 0 : suggested in preliminary enrollment
	// 1 : added in preliminary enrollment
	// 2 : enrolled
	// 3 : wait
	// 4 : score inserted but not confirmed
	// 5 : score confirmed by professor
	// 6 : passed
	// 7 : refused
	// 8 : emergency drop
	std::vector<char> assessment_answers;
	std::string review;
	bool is_objector;
	std::string objection_text;
	bool is_objector_replied;
	std::string objection_reply_text;
public:
	MyCourse(char _status = -1);
	void setScore(float _score);
	float getScore() const;
	void setStatus(char _status);
	char getStatus() const;
	void setAssessmentAnswers(std::vector<char> _assessment_answers);
	std::vector<char> getAssessmentAnswers() const;
	void setReview(std::string _review);
	std::string getReview() const;
	void setIsObjector(bool _is_objector);
	std::string getObjectionText() const;
	bool getIsObjector() const;
	void setObjectionText(std::string _objection_text);
	void setObjectonReplyText(std::string _objection_text);
	std::string getObjectonReplyText() const;
};

class MyTerm {
protected:
	int no;
	char status;
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
	MyTerm(int _no = 0);
	void setno(int _no);
	int getno() const;
	void setStatus(char _status);
	char getStatus() const;
	void setEnrollmentBeginTime(Time _enrollment_begin_time);
	Time getEnrollmentBeginTime() const;
	void setCourses(std::map<Presented_Course*, MyCourse> _courses);
	std::map<Presented_Course*, MyCourse> getCourses() const;
	int numberofCredits() const;
	// course functions:
	void addCourse(Presented_Course* course);
	void removeCourse(Presented_Course* course);
	void setCourseProperties(Presented_Course* course, MyCourse properties);
	MyCourse getCourseProperties(Presented_Course* course) const;
	void setScoreofCourse(Presented_Course* course, float score);
	void setStatusofCourse(Presented_Course* course, char status);
	void setAssessmentAnswersofCourse(Presented_Course* course, std::vector<char> answers);
	void setReviewofCourse(Presented_Course* course, std::string review);
	void setIsObjectorofCourse(Presented_Course* course, bool is_objector);
	void setObjectionTextofCourse(Presented_Course* course, std::string objection_text);
	void setObjectionReplyTextofCourse(Presented_Course* course, std::string objection_reply_text);
};

class Student : public User {
protected:
	std::string field;
	float grade;
	Faculty* supervisor;
	std::map<int, MyTerm> terms;
public:
	Student();
	Student(int _username, std::string _password, std::string _firstname, std::string _lastname, int _departmentcode, std::string _field = "");
	void setField(std::string _field);
	std::string getField() const;
	void setGrade(float _grade);
	float getGrade() const;
	void setSupervisor(Faculty* _supervisor);
	Faculty* getSupervisor() const;
	void setTerms(std::map<int, MyTerm> _terms);
	std::map<int, MyTerm> getTerms() const;
	// term functions:
	void addTerm(MyTerm term);
	void addTerm(int term_no);
	void setTerm(int term_no, MyTerm term);
	MyTerm getTerm(int term_no) const;
	void setTermStatus(int term_no, char status);
	char getTermStatus(int term_no) const;
	void setTermEnrollmentBeginTime(int term_no, Time enrollment_begin_time);
	Time getTermEnrollmentBeginTime(int term_no) const;
	std::map<Presented_Course*, MyCourse> getTermCourses(int term_no) const;
	std::vector<Presented_Course*> getTermCoursesWithoutResult(int term_no) const; // for reports no 78(Week Schedule) and 428(Exams Schedule)
	int numberofCredits(int term_no) const;
	// course functions:
	void addCourse(Presented_Course* course);
	void removeCourse(Presented_Course* course);
	void setCourseProperties(Presented_Course* course, MyCourse properties);
	MyCourse getCourseProperties(Presented_Course* course) const;
	void setScoreofCourse(Presented_Course* course, float score);
	float getScoreofCourse(Presented_Course* course) const;
	void setStatusofCourse(Presented_Course* course, char status);
	char getStatusofCourse(Presented_Course* course) const;
	void setAssessmentAnswersofCourse(Presented_Course* course, std::vector<char> answers);
	std::vector<char> getAssessmentAnswersofCourse(Presented_Course* course) const;
	void setReviewofCourse(Presented_Course* course, std::string review);
	std::string getReviewofCourse(Presented_Course* course) const;
	void setIsObjectorofCourse(Presented_Course* course, bool is_objector);
	bool getIsObjectorofCourse(Presented_Course* course) const;
	void setObjectionTextofCourse(Presented_Course* course, std::string objection_text);
	std::string getObjectionTextofCourse(Presented_Course* course) const;
	std::string getObjectionReplyTextofCourse(Presented_Course* course) const;
};

class Tuition_Student : public Student {
protected:
	char type;
	// type:
	//-1 : unknown
	// 0 : guest student
	// 1 : transitional student
	// 2 : night student
public:
	Tuition_Student(char _type = -1);
	void setType(char _type);
	char getType() const;
	int computeTuition(int term_no);
};

#endif // STUDENT_H
