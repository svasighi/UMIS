#include "Course.h"

Course::Course() {

}

void Course::setCredit(short _credit) {
	credit = _credit;
}

short Course::getCredit() const {
	return credit;
}

void Course::setName(std::string _name) {
	name = _name;
}

std::string Course::getName() const {
	return name;
}

void Course::setType(short _type) {
	type = _type;
}

short Course::getType() const {
	return type;
}

void Course::setPrerequisite(std::vector<Course*> _prerequisite) {
	prerequisite = _prerequisite;
}

void Course::addPrerequisite(Course* course) {
	prerequisite.push_back(course);
}

std::vector<Course*> Course::getPrerequisite() const {
	return prerequisite;
}

void Course::setCorequisite(std::vector<Course*> _corequisite) {
	corequisite = _corequisite;
}

void Course::addCorequisite(Course* course) {
	corequisite.push_back(course);
}

std::vector<Course*> Course::getCorequisite() const {
	return corequisite;
}




Presented_Course::Presented_Course() {

}

void Presented_Course::setCourseProfessor(Professor* _course_professor) {
	course_professor = _course_professor;
}

Professor* Presented_Course::getCourseProfessor() const {
	return course_professor;
}

void Presented_Course::setCapacity(int _capacity) {
	capacity = _capacity;
}

int Presented_Course::getCapacity() const {
	return capacity;
}

void Presented_Course::setTerm_no(int _term_no) {
	term_no = _term_no;
}

int Presented_Course::getTerm_no() const {
	return term_no;
}

void Presented_Course::setCourseTime(Course_Time _course_time) {
	course_time = _course_time;
}

Course_Time Presented_Course::getCourseTime() const {
	return course_time;
}

void Presented_Course::setCourseLocation(std::string _course_location) {
	course_location = _course_location;
}

std::string Presented_Course::getCourseLocation() const {
	return course_location;
}

void Presented_Course::setFinalExamTime(Time _finalexam_time) {
	finalexam_time = _finalexam_time;
}

Time Presented_Course::getFinalExamTime() const {
	return finalexam_time;
}
