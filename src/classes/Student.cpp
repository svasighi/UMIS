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

void MyTerm::setRegistrationBeginTime(Time _registration_begin_time) {
	registration_begin_time = _registration_begin_time;
}

Time MyTerm::getRegistrationBeginTime() const {
	return registration_begin_time;
}

void MyTerm::setCourses(std::map<Presented_Course*, MyCourse> _courses) {
	courses = _courses;
}

std::map<Presented_Course*, MyCourse> MyTerm::getCourses() const {
	return courses;
}

void MyTerm::addCourse(Presented_Course* course) {
	courses[course] = MyCourse();
}

void MyTerm::removeCourse(Presented_Course* course) {
	courses.erase(course);
}

void MyTerm::setScoreofCourse(Presented_Course* course, float score) {
	courses[course].setScore(score);
}

float MyTerm::getScoreofCourse(Presented_Course* course) const {
	if (courses.count(course) == 0)
		throw std::invalid_argument("course not found");
	return courses.at(course).getScore();
}

int MyTerm::numberofcredits() const {
	int n = 0;
	for (auto& x : courses) {
		n += x.first->getCredit();
	}
	return n;
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

void Student::setScoreofCourse(Presented_Course* course, float score) {
	terms[course->getTerm_no()].setScoreofCourse(course, score);
}

float Student::getScoreofCourse(Presented_Course* course) const {
	return terms.at(course->getTerm_no()).getScoreofCourse(course);
}

void Student::setTermStatus(int term_no, short status) {
	terms[term_no].setStatus(status);
}

short Student::getTermStatus(int term_no) const {
	return terms.at(term_no).getStatus();
}

void Student::setTermRegistrationBeginTime(int term_no, Time registration_begin_time) {
	terms[term_no].setRegistrationBeginTime(registration_begin_time);
}

Time Student::getTermRegistrationBeginTime(int term_no) const {
	return terms.at(term_no).getRegistrationBeginTime();
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
	return terms[term_no].numberofcredits();// * credit_fee[type] + const_tuition;
}
