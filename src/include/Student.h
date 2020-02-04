#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include "User.h"
#include "Course.h"
#include "TimeDate.h"
#include "EnrollmentError.h"

class Faculty;

class MyCourse {
protected:
	float score;
	char status;
	std::vector<char> assessment_answers;
	std::string review;
	bool is_objector;
	std::string objection_text;
	std::string objection_reply_text;
public:
	MyCourse(char _status = MyCourse::unknown);
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
	// status:
	static constexpr char unknown		 = -1;
	static constexpr char suggested		 = 0; // suggested in preliminary enrollment
	static constexpr char preliminary	 = 1; // added in preliminary enrollment
	static constexpr char enrolled		 = 2;
	static constexpr char waiting		 = 3;
	static constexpr char notconfirmed	 = 4; // score inserted but not confirmed
	static constexpr char confirmed		 = 5; // score confirmed by professor
	static constexpr char passed		 = 6;
	static constexpr char refused		 = 7;
	static constexpr char emergency_drop = 8;
};

class MyTerm {
protected:
	int no;
	char status;
	Time enrollment_begin_time;
	std::map<EnrollmentError*, char> exceptions;
	std::map<Presented_Course*, MyCourse> courses;
public:
	MyTerm(int _no = 0);
	void setno(int _no);
	int getno() const;
	void setStatus(char _status);
	char getStatus() const;
	void setEnrollmentBeginTime(Time _enrollment_begin_time);
	Time getEnrollmentBeginTime() const;

	void setExceptions(std::map<EnrollmentError*, char> _exceptions);
	std::map<EnrollmentError*, char> getExceptions() const;
	void addException(EnrollmentError* exception);
	void removeException(EnrollmentError* exception);
	void setExceptionStatus(EnrollmentError* exception, char _status);
	char getExceptionStatus(EnrollmentError* exception) const;

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
	bool haveCourse(Course* course) const;
	bool haveCourseWithStatus(Course* course, char _status) const;
	void setCourseProperties(Presented_Course* course, MyCourse properties);
	MyCourse getCourseProperties(Presented_Course* course) const;
	void setScoreofCourse(Presented_Course* course, float _score);
	void setStatusofCourse(Presented_Course* course, char _status);
	void setAssessmentAnswersofCourse(Presented_Course* course, std::vector<char> answers);
	void setReviewofCourse(Presented_Course* course, std::string review);
	void setIsObjectorofCourse(Presented_Course* course, bool is_objector);
	void setObjectionTextofCourse(Presented_Course* course, std::string objection_text);
	void setObjectionReplyTextofCourse(Presented_Course* course, std::string objection_reply_text);
	// status:
	static constexpr char created = 0;
	static constexpr char preliminary_enrollment_confirmed_by_student = 1;
	static constexpr char preliminary_enrollment_rejected_by_professor = -1;
	static constexpr char preliminary_enrollment_confirmed_by_professor = 2;
	static constexpr char enrollment_in_action = 3;
	static constexpr char amendment_in_action = 4; // tarmim
	static constexpr char studying = 5;
	static constexpr char passed = 6; // passed without probation
	static constexpr char on_probation = 7;
	static constexpr char removed = 8;
};

class Student : public User {
protected:
	char type;
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
	bool haveCourse(Course* course) const;
	bool haveCourseWithStatus(Course* course, char _status) const;
	bool haveCourseWithStatus(short department_id, short group_id, short course_id, char _status) const;
	std::vector<std::unique_ptr<EnrollmentError>> checkEnrollment(int term_no, std::vector<Presented_Course*> courses);  // Enrollment
	std::vector<std::unique_ptr<EnrollmentError>> commitEnrollment(int term_no, std::vector<Presented_Course*> courses); // Enrollment
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
	//
	void addException(int term_no, EnrollmentError* exception);
	void removeException(int term_no, EnrollmentError* exception);
	void setExceptionStatus(int term_no, EnrollmentError* exception, char _status);
	//
	std::map<Presented_Course*, MyCourse> getTermCourses(int term_no) const;
	std::vector<Presented_Course*> getTermCoursesWithoutResult(int term_no) const; // for reports no 78(Week Schedule) and 428(Exams Schedule)
	// course functions:
	void addCourse(Presented_Course* course, char _status = -1);
	void removeCourse(Presented_Course* course);
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
	// type:
	static constexpr char unknown		= -1;
	static constexpr char guest		= 0;
	static constexpr char transitional	= 1;
	static constexpr char night		= 2;
	static constexpr char day		= 3;
};

#endif // STUDENT_H
