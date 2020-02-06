#include <stdexcept>
#include "../include/Course.h"
#include "../include/Student.h"

Course::Course()
	: department_id(0), group_id(0), course_id(0), credit(0), type(-1) {}

Course::Course(short _department_id, short _group_id, short _course_id, char _credit, std::string _name, char _type)
	: department_id(_department_id), group_id(_group_id), course_id(_course_id), credit(_credit), name(_name), type(-1) {}

std::map<int, Course*> Course::readAllCourses(void) {
	std::map<int, Course*> TempCourses;

	BinaryFile<Course> binary_file((char*) "../storage/Courses.dat");
	std::vector<Course*> courses = binary_file.FetchAllRecords();

	for (int i = 0; i < courses.size(); i++) {
		TempCourses.insert(std::make_pair(courses[i]->getCompleteID(), courses[i]));
	}
	return TempCourses;
}

void Course::setDepartment_id(short _department_id) {
	department_id = _department_id;
}

short Course::getDepartment_id() const {
	return department_id;
}

void Course::setGroup_id(short _group_id) {
	group_id = _group_id;
}

short Course::getGroup_id() const {
	return group_id;
}

void Course::setCourse_id(short _course_id) {
	course_id = _course_id;
}

short Course::getCourse_id() const {
	return course_id;
}

void Course::setCredit(char _credit) {
	credit = _credit;
}

char Course::getCredit() const {
	return credit;
}

void Course::setName(std::string _name) {
	name = _name;
}

std::string Course::getName() const {
	return name;
}

void Course::setType(char _type) {
	type = _type;
}

char Course::getType() const {
	return type;
}

void Course::setPrerequisites(const std::vector<Course*>& _prerequisites) {
	prerequisites = _prerequisites;
}

std::vector<Course*> Course::getPrerequisites() const {
	return prerequisites;
}

void Course::addPrerequisite(Course* course) {
	if (course == this)
		return;
	if (course->department_id == this->department_id && course->group_id == this->group_id && course->course_id == this->course_id)
		return;
	if (std::find(prerequisites.begin(), prerequisites.end(), course) != prerequisites.end())
		return;
	if (std::find(corequisites.begin(), corequisites.end(), course) != corequisites.end())
		return;
	prerequisites.push_back(course);
}

void Course::removePrerequisite(Course* course) {
	std::vector<Course*>::iterator position = std::find(prerequisites.begin(), prerequisites.end(), course);
	if (position != prerequisites.end()) {
		prerequisites.erase(position);
	}
}

void Course::setCorequisites(const std::vector<Course*>& _corequisites) {
	corequisites = _corequisites;
}

std::vector<Course*> Course::getCorequisites() const {
	return corequisites;
}

void Course::addCorequisite(Course* course) {
	if (course == this)
		return;
	if (course->department_id == this->department_id && course->group_id == this->group_id && course->course_id == this->course_id)
		return;
	if (std::find(prerequisites.begin(), prerequisites.end(), course) != prerequisites.end())
		return;
	if (std::find(corequisites.begin(), corequisites.end(), course) != corequisites.end())
		return;
	corequisites.push_back(course);
}

void Course::removeCorequisite(Course* course) {
	std::vector<Course*>::iterator position = std::find(corequisites.begin(), corequisites.end(), course);
	if (position != corequisites.end()) {
		corequisites.erase(position);
	}
}

bool Course::haveSameID(Course* course) const {
	if (this->course_id == course->course_id && this->group_id == course->group_id && this->department_id == course->department_id) {
		return true;
	}
	return false;
}

bool Course::searchSameIDin(const std::vector<Course*>& v) const {
	for (const auto& c : v) {
		if (this->haveSameID(c)) {
			return true;
		}
	}
	return false;
}

int Course::getCompleteID() const {
	return std::stoi(std::to_string(department_id) + std::to_string(group_id) + std::to_string(course_id));
}




Presented_Course::Presented_Course()
	: term_no(0), group_no(0), course_professor(nullptr), capacity(0), enrolled_number(0), waiting_number(0) {}

Presented_Course::Presented_Course(Course* course, int _term_no, char _group_no, Professor* _course_professor, int _capacity)
	: term_no(_term_no), group_no(_group_no), course_professor(_course_professor), capacity(_capacity), enrolled_number(0), waiting_number(0), Course(*course) {}

void Presented_Course::setTerm_no(int _term_no) {
	term_no = _term_no;
}

int Presented_Course::getTerm_no() const {
	return term_no;
}

void Presented_Course::setGroup_no(char _group_no) {
	group_no = _group_no;
}

char Presented_Course::getGroup_no() const {
	return group_no;
}

void Presented_Course::setCourseProfessor(Professor* _course_professor) {
	course_professor = _course_professor;
}

Professor* Presented_Course::getCourseProfessor() const {
	return course_professor;
}

void Presented_Course::setCourseStudents(const std::vector<Student*>& _course_students) {
	course_students = _course_students;
}

std::vector<Student*> Presented_Course::getCourseStudents() const {
	return course_students;
}

void Presented_Course::addStudent(Student* student) {
	if (std::find(course_students.begin(), course_students.end(), student) == course_students.end()) {
		course_students.push_back(student);
	}
}

void Presented_Course::removeStudent(Student* student) {
	std::vector<Student*>::iterator position = std::find(course_students.begin(), course_students.end(), student);
	if (position != course_students.end()) {
		course_students.erase(position);
	}
}

int Presented_Course::getNumberofStudents() const {
	return course_students.size();
}

int Presented_Course::getNumberofStudentsWithCourseStatus(char _status) const {
	Presented_Course* course = const_cast<Presented_Course*>(this);
	int n = 0;
	for (const auto& student : course_students) {
		if (student->getStatusofCourse(course) == _status) {
			n++;
		}
	}
	return n;
}

void Presented_Course::setCapacity(int _capacity) {
	if (_capacity < 0)
		throw std::invalid_argument("capacity can't be negative");
	capacity = _capacity;
}

int Presented_Course::getCapacity() const {
	return capacity;
}

void Presented_Course::updateEnrolledAndWaitingNumbers() {
	int _enrolled_number = 0, _waiting_number = 0;
	for (const auto& student : course_students) {
		if (student->getStatusofCourse(this) == MyCourse::enrolled) {
			_enrolled_number++;
		}
		if (student->getStatusofCourse(this) == MyCourse::waiting) {
			_waiting_number++;
		}
	}

	enrolled_number = _enrolled_number;
	waiting_number = _waiting_number;

	if (capacity < enrolled_number) {
		capacity = enrolled_number;
	}
}

void Presented_Course::setEnrolledNumber(int _enrolled_number) {
	if (_enrolled_number < 0 || _enrolled_number > capacity)
		throw std::invalid_argument("enrolled_number must be between 0 and capacity");
	enrolled_number = _enrolled_number;
}

void Presented_Course::addEnrolledNumber(int x) {
	enrolled_number += x;
	if (enrolled_number < 0)
		throw std::invalid_argument("enrolled_number can't be negative");
	if (capacity < enrolled_number) {
		capacity = enrolled_number;
	}
}

int Presented_Course::getEnrolledNumber() const {
	return enrolled_number;
}

void Presented_Course::setWaitingNumber(int _waiting_number) {
	if (_waiting_number < 0)
		throw std::invalid_argument("waiting_number can't be negative");
	waiting_number = _waiting_number;
}

void Presented_Course::addWaitingNumber(int x) {
	setWaitingNumber(waiting_number + x);
}

int Presented_Course::getWaitingNumber() const {
	return waiting_number;
}

void Presented_Course::setCourseTime(const CourseTime& _course_time) {
	course_time = _course_time;
}

CourseTime Presented_Course::getCourseTime() const {
	return course_time;
}

void Presented_Course::setCourseLocation(std::string _course_location) {
	course_location = _course_location;
}

std::string Presented_Course::getCourseLocation() const {
	return course_location;
}

void Presented_Course::setFinalExamTime(const ExamTime& _finalexam_time) {
	finalexam_time = _finalexam_time;
}

ExamTime Presented_Course::getFinalExamTime() const {
	return finalexam_time;
}

void Presented_Course::setFinalExamLocation(std::string _finalexam_location) {
	finalexam_location = _finalexam_location;
}

std::string Presented_Course::getFinalExamLocation() const {
	return finalexam_location;
}

bool Presented_Course::isSameWith(Presented_Course* course) const {
	if (this->course_id == course->course_id && this->group_id == course->group_id && this->department_id == course->department_id
		&& this->term_no == course->term_no && this->group_no == course->group_no) {
		return true;
	}
	return false;
}
