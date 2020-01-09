#include <stdexcept>
#include "Student.h"

MyTerm::MyTerm() {

}

MyTerm::MyTerm(int _no)
	: no(_no) {}

void MyTerm::setno(int _no) {
	no = _no;
}

int MyTerm::getno() const {
	return no;
}

void MyTerm::setCourses(std::map<Presented_Course*, float> _courses) {
	courses = _courses;
}

std::map<Presented_Course*, float> MyTerm::getCourses() const {
	return courses;
}

void MyTerm::addCourse(Presented_Course* course, float score) {
	courses[course] = score;
}

float MyTerm::getScoreofCourse(Presented_Course* course) const {
	if (courses.count(course) == 0)
		throw std::invalid_argument("course not found");
	return courses.at(course);
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

void Student::setTerms(std::vector<MyTerm> _terms) {
	terms = _terms;
}

std::vector<MyTerm> Student::getTerms() const {
	return terms;
}

void Student::addTerm(MyTerm term) {
	terms.push_back(term);
}

void Student::setScoreofCourse(Presented_Course* course, float score) {
	terms[course->getTerm_no()].addCourse(course, score);
}

float Student::getScoreofCourse(Presented_Course* course) const {
	terms[course->getTerm_no()].getScoreofCourse(course);
}