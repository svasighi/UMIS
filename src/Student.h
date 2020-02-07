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

#define NOCHNG 0
#define ENROLL 1
#define WAIT   2
#define REMOVE 3

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
	void setAssessmentAnswers(const std::vector<char>& _assessment_answers);
	std::vector<char> getAssessmentAnswers() const;
	void setReview(std::string _review);
	std::string getReview() const;
	void setIsObjector(bool _is_objector);
	bool getIsObjector() const;
	void setObjectionText(std::string _objection_text);
	std::string getObjectionText() const;
	void setObjectionReplyText(std::string _objection_reply_text);
	std::string getObjectionReplyText() const;
	// course status:
	static constexpr char unknown = 0;
	static constexpr char enrolled = 1;
	static constexpr char waiting = 2;
	static constexpr char notconfirmed = 3; // score inserted but not confirmed
	static constexpr char confirmed = 4; // score confirmed by professor
	static constexpr char passed = 5;
	static constexpr char refused = 6;
	static constexpr char emergency_drop = 7;
};

class MyTerm {
protected:
	int no;
	char status;
	Time enrollment_begin_time;
	std::map<EnrollmentError*, char> exceptions;
	std::vector<Course*> preliminary_courses;
	std::map<PresentedCourse*, MyCourse> courses;
public:
	MyTerm(int _no = 0, char _status = MyTerm::created);
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
	void setPreliminaryCourses(const std::vector<Course*>& _preliminary_courses);
	std::vector<Course*> getPreliminaryCourses() const;
	void addPreliminaryCourse(Course* course);
	void removePreliminaryCourse(Course* course);
	void setCourses(const std::map<PresentedCourse*, MyCourse>& _courses);
	std::map<PresentedCourse*, MyCourse> getCourses() const;
	std::vector<PresentedCourse*> getCoursesWithoutResult() const;
	int numberofCourses() const;
	int numberofCoursesWithStatus(char _status) const;
	int numberofCredits() const;
	int numberofCreditsWithStatus(char _status) const;
	// course functions:
	void addCourse(PresentedCourse* course, char _status = MyCourse::unknown);
	void removeCourse(PresentedCourse* course);
	bool haveCourse(Course* course) const;
	bool haveCourseWithStatus(Course* course, char _status) const;
	void setCourseProperties(PresentedCourse* course, const MyCourse& properties);
	MyCourse getCourseProperties(PresentedCourse* course) const;
	void setScoreofCourse(PresentedCourse* course, float _score);
	void setStatusofCourse(PresentedCourse* course, char _status);
	void setAssessmentAnswersofCourse(PresentedCourse* course, const std::vector<char>& answers);
	void setReviewofCourse(PresentedCourse* course, std::string review);
	void setIsObjectorofCourse(PresentedCourse* course, bool is_objector);
	void setObjectionTextofCourse(PresentedCourse* course, std::string objection_text);
	void setObjectionReplyTextofCourse(PresentedCourse* course, std::string objection_reply_text);
	// term status:
	static constexpr char created = 0; // preliminary enrollment in action
	static constexpr char preliminary_enrollment_confirmed_by_student = 1;
	static constexpr char preliminary_enrollment_confirmed_by_professor = 2;
	static constexpr char preliminary_enrollment_rejected_by_professor = -1;
	static constexpr char enrollment_in_action = 3;
	static constexpr char amendment_in_action = 4;
	static constexpr char studying = 5;
	static constexpr char passed = 6; // passed without probation
	static constexpr char on_probation = 7;
	static constexpr char refused = 8;
	static constexpr char removed = 9;
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
	Student(int _username, std::string _password, std::string _firstname, std::string _lastname, short _departmentcode, char _type = Student::day, std::string _field = "", short _groupcode = 0);
	void setType(char _type);
	char getType() const;
	void setField(std::string _field);
	std::string getField() const;
	void updateGrade();
	void setGrade(float _grade);
	float getGrade() const;
	void setSupervisor(Faculty* _supervisor);
	Faculty* getSupervisor() const;
	void setTerms(const std::map<int, MyTerm>& _terms);
	std::map<int, MyTerm> getTerms() const;
	bool changePassword(std::string current_pass, std::string new_pass);
	int numberofTermsonProbation() const;
	int numberofAllCreditsWithStatus(char _status) const;
	bool haveCourse(Course* course) const;
	bool haveCourseWithStatus(Course* course, char _status) const;
	bool haveCourseWithStatus(int course_id, char _status) const;
	// 1 for enroll , 2 for wait, 3 for remove
	std::vector<std::unique_ptr<EnrollmentError>> checkEnrollment(int term_no, const std::map<PresentedCourse*, char>& _courses);  // Enrollment
	std::vector<std::unique_ptr<EnrollmentError>> commitEnrollment(int term_no, const std::map<PresentedCourse*, char>& _courses); // Enrollment
	std::vector<std::unique_ptr<EnrollmentError>> checkPreliminaryEnrollment(int term_no, const std::map<Course*, bool>& preliminary_courses);
	std::vector<std::unique_ptr<EnrollmentError>> commitPreliminaryEnrollment(int term_no, const std::map<Course*, bool>& preliminary_courses);
	int computeTuition(int term_no);
	// term functions:
	void addTerm(MyTerm term);
	void addTerm(int term_no, char _status = MyTerm::created);
	MyTerm getTerm(int term_no) const;
	void setTermStatus(int term_no, char _status); // for confirm preliminary enrollment
	char getTermStatus(int term_no) const;
	void setTermEnrollmentBeginTime(int term_no, Time enrollment_begin_time);
	void addException(int term_no, EnrollmentError* exception);
	void removeException(int term_no, EnrollmentError* exception);
	void setExceptionStatus(int term_no, EnrollmentError* exception, char _status);
	std::map<PresentedCourse*, MyCourse> getTermCourses(int term_no) const;
	std::vector<PresentedCourse*> getTermCoursesWithoutResult(int term_no) const; // for reports no 78(Week Schedule) and 428(Exams Schedule)
	// course functions:
	void addCourse(PresentedCourse* course, char _status = MyCourse::unknown);
	void removeCourse(PresentedCourse* course);
	void setCourseProperties(PresentedCourse* course, const MyCourse& properties);
	MyCourse getCourseProperties(PresentedCourse* course) const;
	void setScoreofCourse(PresentedCourse* course, float _score);
	float getScoreofCourse(PresentedCourse* course) const;
	void setStatusofCourse(PresentedCourse* course, char _status);
	char getStatusofCourse(PresentedCourse* course) const; 
	void setAssessmentAnswersofCourse(PresentedCourse* course, std::vector<char> answers);
	std::vector<char> getAssessmentAnswersofCourse(PresentedCourse* course) const;
	void setReviewofCourse(PresentedCourse* course, std::string review);
	std::string getReviewofCourse(PresentedCourse* course) const;
	void setIsObjectorofCourse(PresentedCourse* course, bool is_objector);
	bool getIsObjectorofCourse(PresentedCourse* course) const;
	void setObjectionTextofCourse(PresentedCourse* course, std::string objection_text);
	std::string getObjectionTextofCourse(PresentedCourse* course) const;
	void setObjectionReplyTextofCourse(PresentedCourse* course, std::string objection_reply_text);
	std::string getObjectionReplyTextofCourse(PresentedCourse* course) const;
	// student type:
	static constexpr char guest = 0;
	static constexpr char transitional = 1;
	static constexpr char night = 2;
	static constexpr char day = 3;
};

#endif // STUDENT_H
