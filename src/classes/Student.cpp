#include <stdexcept>
#include "../include/Student.h"

MyCourse::MyCourse() {

}

void MyCourse::setScore(float _score) {
	score = _score;
}

float MyCourse::getScore() const {
	return score;
}

void MyCourse::setStatus(short _status) {
	status = _status;
}

short MyCourse::getStatus() const {
	return status;
}

void MyCourse::setAssessmentAnswers(std::vector<short> _assessment_answers) {
	assessment_answers = _assessment_answers;
}

std::vector<short> MyCourse::getAssessmentAnswers() const {
	return assessment_answers;
}

void MyCourse::setReview(std::string _review) {
	review = _review;
}

std::string MyCourse::getReview() const {
	return review;
}




MyTerm::MyTerm()
	: no(0), status(0) {}

MyTerm::MyTerm(int _no)
	: no(_no), status(0) {}

void MyTerm::setno(int _no) {
	no = _no;
}

int MyTerm::getno() const {
	return no;
}

void MyTerm::setStatus(short _status) {
	status = _status;
}

short MyTerm::getStatus() const {
	return status;
}

void MyTerm::setEnrollmentBeginTime(Time _enrollment_begin_time) {
	enrollment_begin_time = _enrollment_begin_time;
}

Time MyTerm::getEnrollmentBeginTime() const {
	return enrollment_begin_time;
}

void MyTerm::setCourses(std::map<Presented_Course*, MyCourse> _courses) {
	courses = _courses;
}

std::map<Presented_Course*, MyCourse> MyTerm::getCourses() const {
	return courses;
}

int MyTerm::numberofCredits() const {
	int n = 0;
	for (auto& x : courses) {
		n += x.first->getCredit();
	}
	return n;
}

void MyTerm::addCourse(Presented_Course* course) {
	courses[course] = MyCourse();
}

void MyTerm::removeCourse(Presented_Course* course) {
	courses.erase(course);
}

void MyTerm::setCourseProperties(Presented_Course* course, MyCourse properties) {
	courses[course] = properties;
}

MyCourse MyTerm::getCourseProperties(Presented_Course* course) const {
	if (courses.count(course) == 0)
		throw std::invalid_argument("course not found");
	return courses.at(course);
}

void MyTerm::setScoreofCourse(Presented_Course* course, float score) {
	courses[course].setScore(score);
}

void MyTerm::setStatusofCourse(Presented_Course* course, short status) {
	courses[course].setStatus(status);
}

void MyTerm::setAssessmentAnswersofCourse(Presented_Course* course, std::vector<short> answers) {
	courses[course].setAssessmentAnswers(answers);
}

void MyTerm::setReviewofCourse(Presented_Course* course, std::string review) {
	courses[course].setReview(review);
}




Student::Student() {

}

void Student::setField(std::string _field) {
	field = _field;
}

std::string Student::getField() const {
	return field;
}

void Student::setGrade(float _grade) {
	grade = _grade;
}

float Student::getGrade() const {
	return grade;
}

void Student::setTerms(std::map<int, MyTerm> _terms) {
	terms = _terms;
}

std::map<int, MyTerm> Student::getTerms() const {
	return terms;
}

void Student::addTerm(MyTerm term) {
	terms[term.getno()] = term;
}

void Student::addTerm(int term_no) {
	terms[term_no] = MyTerm();
}

void Student::setTerm(int term_no, MyTerm term) {
	terms[term_no] = term;
}

MyTerm Student::getTerm(int term_no) const {
	return terms.at(term_no);
}

void Student::setTermStatus(int term_no, short status) {
	terms[term_no].setStatus(status);
}

short Student::getTermStatus(int term_no) const {
	return terms.at(term_no).getStatus();
}

void Student::setTermEnrollmentBeginTime(int term_no, Time enrollment_begin_time) {
	terms[term_no].setEnrollmentBeginTime(enrollment_begin_time);
}

Time Student::getTermEnrollmentBeginTime(int term_no) const {
	return terms.at(term_no).getEnrollmentBeginTime();
}

int Student::numberofCredits(int term_no) const {
	return terms.at(term_no).numberofCredits();
}

void Student::addCourse(Presented_Course* course) {
	terms[course->getTerm_no()].addCourse(course);
}

void Student::removeCourse(Presented_Course* course) {
	terms[course->getTerm_no()].removeCourse(course);
}

void Student::setCourseProperties(Presented_Course* course, MyCourse properties) {
	terms[course->getTerm_no()].setCourseProperties(course, properties);
}

MyCourse Student::getCourseProperties(Presented_Course* course) const {
	return terms.at(course->getTerm_no()).getCourseProperties(course);
}

void Student::setScoreofCourse(Presented_Course* course, float score) {
	terms[course->getTerm_no()].setScoreofCourse(course, score);
}

float Student::getScoreofCourse(Presented_Course* course) const {
	return terms.at(course->getTerm_no()).getCourseProperties(course).getScore();
}

void Student::setStatusofCourse(Presented_Course* course, short status) {
	terms[course->getTerm_no()].setStatusofCourse(course, status);
}

short Student::getStatusofCourse(Presented_Course* course) const {
	return terms.at(course->getTerm_no()).getCourseProperties(course).getStatus();
}

void Student::setAssessmentAnswersofCourse(Presented_Course* course, std::vector<short> answers) {
	terms[course->getTerm_no()].setAssessmentAnswersofCourse(course, answers);
}

std::vector<short> Student::getAssessmentAnswersofCourse(Presented_Course* course) const {
	return terms.at(course->getTerm_no()).getCourseProperties(course).getAssessmentAnswers();
}

void Student::setReviewofCourse(Presented_Course* course, std::string review) {
	terms[course->getTerm_no()].setReviewofCourse(course, review);
}

std::string Student::getReviewofCourse(Presented_Course* course) const {
	return terms.at(course->getTerm_no()).getCourseProperties(course).getReview();
}




Tuition_Student::Tuition_Student() {

}

void Tuition_Student::setType(short _type) {
	type = _type;
}

short Tuition_Student::getType() const {
	return type;
}

int Tuition_Student::computeTuition(int term_no) {
	return terms[term_no].numberofCredits();// * credit_fee[type] + const_tuition;
}
