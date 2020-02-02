#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <map>
#include <algorithm>
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
	bool getIsObjector() const;
	void setObjectionText(std::string _objection_text);
	std::string getObjectionText() const;
	void setObjectionReplyText(std::string _objection_reply_text);
	std::string getObjectionReplyText() const;
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
	// 4 : tarmim in action
	// 5 : studying
	// 6 : passed without probation
	// 7 : on academic probation
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
	std::vector<Presented_Course*> getCoursesWithoutResult() const;
	int numberofCourses() const;
	int numberofCoursesWithStatus(char _status) const;
	int numberofCredits() const;
	int numberofCreditsWithStatus(char _status) const;
	// course functions:
	void addCourse(Presented_Course* course, char _status = -1);
	void removeCourse(Presented_Course* course);
	bool hasCourse(Presented_Course* course) const;
	void setCourseProperties(Presented_Course* course, MyCourse properties);
	MyCourse getCourseProperties(Presented_Course* course) const;
	void setScoreofCourse(Presented_Course* course, float _score);
	void setStatusofCourse(Presented_Course* course, char _status);
	void setAssessmentAnswersofCourse(Presented_Course* course, std::vector<char> answers);
	void setReviewofCourse(Presented_Course* course, std::string review);
	void setIsObjectorofCourse(Presented_Course* course, bool is_objector);
	void setObjectionTextofCourse(Presented_Course* course, std::string objection_text);
	void setObjectionReplyTextofCourse(Presented_Course* course, std::string objection_reply_text);
};

class Student : public User {
protected:
	char type;
	// type:
	//-1 : unknown
	// 0 : guest student
	// 1 : transitional student
	// 2 : night student
	// 3 : day student
	std::string field;
	float grade;
	Faculty* supervisor;
	std::map<int, MyTerm> terms;
public:
	
	Student();
	Student(int _username, std::string _password, std::string _firstname, std::string _lastname, int _departmentcode, char _type = -1, std::string _field = "");
	void setType(char _type);
	char getType() const;
	void setField(std::string _field);
	std::string getField() const;
	void setGrade(float _grade);
	float getGrade() const;
	void setSupervisor(Faculty* _supervisor);
	Faculty* getSupervisor() const;
	void setTerms(std::map<int, MyTerm> _terms);
	std::map<int, MyTerm> getTerms() const;
	int numberofTermsonProbation() const;
	int numberofAllCreditsWithStatus(char _status) const;
	int computeTuition(int term_no);
	// term functions:
	void addTerm(MyTerm term);
	void addTerm(int term_no);
	void setTerm(int term_no, MyTerm term);
	MyTerm getTerm(int term_no) const;
	void setTermStatus(int term_no, char _status);
	char getTermStatus(int term_no) const;
	void setTermEnrollmentBeginTime(int term_no, Time enrollment_begin_time);
	Time getTermEnrollmentBeginTime(int term_no) const;
	std::map<Presented_Course*, MyCourse> getTermCourses(int term_no) const;
	std::vector<Presented_Course*> getTermCoursesWithoutResult(int term_no) const; // for reports no 78(Week Schedule) and 428(Exams Schedule)
	int numberofCourses(int term_no) const;
	int numberofCoursesWithStatus(int term_no, char _status) const;
	int numberofCredits(int term_no) const;
	int numberofCreditsWithStatus(int term_no, char _status) const;
	// course functions:
	void addCourse(Presented_Course* course, char _status = -1); // enrollment
	void removeCourse(Presented_Course* course);
	bool hasCourse(Presented_Course* course) const;
	void setCourseProperties(Presented_Course* course, MyCourse properties);
	MyCourse getCourseProperties(Presented_Course* course) const;
	void setScoreofCourse(Presented_Course* course, float _score);
	float getScoreofCourse(Presented_Course* course) const;
	void setStatusofCourse(Presented_Course* course, char _status);
	char getStatusofCourse(Presented_Course* course) const; 
	void setAssessmentAnswersofCourse(Presented_Course* course, std::vector<char> answers);
	std::vector<char> getAssessmentAnswersofCourse(Presented_Course* course) const;
	void setReviewofCourse(Presented_Course* course, std::string review);
	std::string getReviewofCourse(Presented_Course* course) const;
	void setIsObjectorofCourse(Presented_Course* course, bool is_objector);
	bool getIsObjectorofCourse(Presented_Course* course) const;
	void setObjectionTextofCourse(Presented_Course* course, std::string objection_text);
	std::string getObjectionTextofCourse(Presented_Course* course) const;
	void setObjectionReplyTextofCourse(Presented_Course* course, std::string objection_reply_text);
	std::string getObjectionReplyTextofCourse(Presented_Course* course) const;
};


#endif // STUDENT_H
