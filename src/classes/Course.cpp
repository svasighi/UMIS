#include "../include/Course.h"

Course::Course() {

}

void Course::setCourse_no(short _course_no) {
	course_no = _course_no;
}

short Course::getCourse_no() const {
	return course_no;
}

void Course::setGroup_id(short _group_id) {
	group_id = _group_id;
}

short Course::getGroup_id() const {
	return group_id;
}

void Course::setDepartment_id(short _department_id) {
	department_id = _department_id;
}

short Course::getDepartment_id() const {
	return department_id;
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

void Course::setPrerequisites(std::vector<Course*> _prerequisites) {
	prerequisites = _prerequisites;
}

std::vector<Course*> Course::getPrerequisites() const {
	return prerequisites;
}

void Course::addPrerequisite(Course* course) {
	prerequisites.push_back(course);
}

void Course::removePrerequisite(Course* course) {
	prerequisites.erase(find(prerequisites.begin(), prerequisites.end(), course));
}

void Course::setCorequisites(std::vector<Course*> _corequisites) {
	corequisites = _corequisites;
}

std::vector<Course*> Course::getCorequisites() const {
	return corequisites;
}

void Course::addCorequisite(Course* course) {
	corequisites.push_back(course);
}

void Course::removeCorequisite(Course* course) {
	corequisites.erase(find(corequisites.begin(), corequisites.end(), course));
}




Presented_Course::Presented_Course() {

}

void Presented_Course::setCourseProfessor(Professor* _course_professor) {
	course_professor = _course_professor;
}

Professor* Presented_Course::getCourseProfessor() const {
	return course_professor;
}

void Presented_Course::setCourseStudents(std::vector<Student*> _course_students) {
	course_students = _course_students;
}

std::vector<Student*> Presented_Course::getCourseStudents() const {
	return course_students;
}

void Presented_Course::addStudent(Student* student) {
	course_students.push_back(student);
}

void Presented_Course::removeStudent(Student* student) {
	course_students.erase(find(course_students.begin(), course_students.end(), student));
}

int Presented_Course::getNumberofStudents() const {
	return course_students.size();
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

void Presented_Course::setFinalExamLocation(std::string _finalexam_location) {
	finalexam_location = _finalexam_location;
}

std::string Presented_Course::getFinalExamLocation() const {
	return finalexam_location;
}
