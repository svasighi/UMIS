#include <stdexcept>
#include "Course.h"
#include "Student.h"

Course::Course()
	: departmentcode(0), groupcode(0), coursecode(0), credit(0), type(-1) {}

Course::Course(short _departmentcode, short _groupcode, short _coursecode, char _credit, std::string _name, char _type)
	: departmentcode(_departmentcode), groupcode(_groupcode), coursecode(_coursecode), credit(_credit), name(_name), type(-1) {}

void Course::setDepartmentCode(short _departmentcode) {
	departmentcode = _departmentcode;
}

short Course::getDepartmentCode() const {
	return departmentcode;
}

void Course::setGroupCode(short _groupcode) {
	groupcode = _groupcode;
}

short Course::getGroupCode() const {
	return groupcode;
}

void Course::setCourseCode(short _coursecode) {
	coursecode = _coursecode;
}

short Course::getCourseCode() const {
	return coursecode;
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
	if (course->departmentcode == this->departmentcode && course->groupcode == this->groupcode && course->coursecode == this->coursecode)
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
	if (course->departmentcode == this->departmentcode && course->groupcode == this->groupcode && course->coursecode == this->coursecode)
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

bool Course::haveSameCourseID(Course* course) const {
	if (this->coursecode == course->coursecode && this->groupcode == course->groupcode && this->departmentcode == course->departmentcode) {
		return true;
	}
	return false;
}

bool Course::searchSameCourseID(const std::vector<Course*>& v) const {
	for (const auto& course : v) {
		if (this->coursecode == course->coursecode && this->groupcode == course->groupcode && this->departmentcode == course->departmentcode) {
			return true;
		}
	}
	return false;
}

int Course::getCourseID() const {
	return std::stoi(std::to_string(departmentcode) + std::to_string(groupcode) + std::to_string(coursecode));
}




PresentedCourse::PresentedCourse()
	: term_no(0), group_no(0), course_professor(nullptr), capacity(0), enrolled_number(0), waiting_number(0) {}

PresentedCourse::PresentedCourse(Course* course, int _term_no, char _group_no, Professor* _course_professor, int _capacity)
	: term_no(_term_no), group_no(_group_no), course_professor(_course_professor), capacity(_capacity), enrolled_number(0), waiting_number(0), Course(*course) {}

void PresentedCourse::setTerm_no(int _term_no) {
	term_no = _term_no;
}

int PresentedCourse::getTerm_no() const {
	return term_no;
}

void PresentedCourse::setGroup_no(char _group_no) {
	group_no = _group_no;
}

char PresentedCourse::getGroup_no() const {
	return group_no;
}

void PresentedCourse::setCourseProfessor(Professor* _course_professor) {
	course_professor = _course_professor;
}

Professor* PresentedCourse::getCourseProfessor() const {
	return course_professor;
}

void PresentedCourse::setCourseStudents(const std::vector<Student*>& _course_students) {
	course_students = _course_students;
}

std::vector<Student*> PresentedCourse::getCourseStudents() const {
	return course_students;
}

void PresentedCourse::addStudent(Student* student) {
	if (std::find(course_students.begin(), course_students.end(), student) == course_students.end()) {
		course_students.push_back(student);
	}
}

void PresentedCourse::removeStudent(Student* student) {
	std::vector<Student*>::iterator position = std::find(course_students.begin(), course_students.end(), student);
	if (position != course_students.end()) {
		course_students.erase(position);
	}
}

int PresentedCourse::getNumberofStudents() const {
	return course_students.size();
}

int PresentedCourse::getNumberofStudentsWithCourseStatus(char _status) const {
	PresentedCourse* course = const_cast<PresentedCourse*>(this);
	int n = 0;
	for (const auto& student : course_students) {
		if (student->getStatusofCourse(course) == _status) {
			n++;
		}
	}
	return n;
}

void PresentedCourse::setCapacity(int _capacity) {
	if (_capacity < 0)
		throw std::invalid_argument("capacity can't be negative");
	if (_capacity > capacity) {
		enrollFirstStudentWaiting(_capacity - capacity);
	}
	else if (_capacity < capacity) {
		removeLastStudentEnrolled(capacity - _capacity);
	}
	capacity = _capacity;
}

int PresentedCourse::getCapacity() const {
	return capacity;
}

void PresentedCourse::updateEnrolledAndWaitingNumbers() {
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

void PresentedCourse::setEnrolledNumber(int _enrolled_number) {
	if (_enrolled_number < 0)
		throw std::invalid_argument("enrolled_number can't be negative");
	enrolled_number = _enrolled_number;
	if (capacity < enrolled_number) {
		capacity = enrolled_number;
	}
}

void PresentedCourse::addEnrolledNumber(int x) {
	setEnrolledNumber(enrolled_number + x);
}

int PresentedCourse::getEnrolledNumber() const {
	return enrolled_number;
}

void PresentedCourse::setWaitingNumber(int _waiting_number) {
	if (_waiting_number < 0)
		throw std::invalid_argument("waiting_number can't be negative");
	waiting_number = _waiting_number;
}

void PresentedCourse::addWaitingNumber(int x) {
	setWaitingNumber(waiting_number + x);
}

int PresentedCourse::getWaitingNumber() const {
	return waiting_number;
}

void PresentedCourse::enrollFirstStudentWaiting(int n) {
	int i = 0;
	for (auto stu = course_students.begin(); stu != course_students.end() && i < n && waiting_number > 0; stu++) {
		if ((*stu)->getTerm(term_no).getCourseProperties(this).getStatus() == MyCourse::waiting) {
			(*stu)->setStatusofCourse(this, MyCourse::enrolled);
			addEnrolledNumber();
			addWaitingNumber(-1);
			i++;
		}
	}
}

void PresentedCourse::removeLastStudentEnrolled(int n) {
	int i = 0;
	for (auto stu = course_students.end() - 1; stu >= course_students.begin() && i < n && enrolled_number > 0; stu--) {
		if ((*stu)->getTerm(term_no).getCourseProperties(this).getStatus() == MyCourse::enrolled) {
			(*stu)->setStatusofCourse(this, MyCourse::waiting);
			addEnrolledNumber(-1);
			addWaitingNumber();
			i++;
		}
	}
}

void PresentedCourse::removeAllWaitingStudents() {
	for (auto stu = course_students.begin(); stu != course_students.end(); stu++) {
		if ((*stu)->getTerm(term_no).getCourseProperties(this).getStatus() == MyCourse::waiting) {
			course_students.erase(stu);
		}
	}
	waiting_number = 0;
}

void PresentedCourse::setCourseTime(const CourseTime& _course_time) {
	course_time = _course_time;
}

CourseTime PresentedCourse::getCourseTime() const {
	return course_time;
}

void PresentedCourse::setCourseLocation(std::string _course_location) {
	course_location = _course_location;
}

std::string PresentedCourse::getCourseLocation() const {
	return course_location;
}

void PresentedCourse::setFinalExamTime(const ExamTime& _finalexam_time) {
	finalexam_time = _finalexam_time;
}

ExamTime PresentedCourse::getFinalExamTime() const {
	return finalexam_time;
}

void PresentedCourse::setFinalExamLocation(std::string _finalexam_location) {
	finalexam_location = _finalexam_location;
}

std::string PresentedCourse::getFinalExamLocation() const {
	return finalexam_location;
}

bool PresentedCourse::haveSamePresentedCourseID(PresentedCourse* course) const {
	if (this->coursecode == course->coursecode && this->groupcode == course->groupcode && this->departmentcode == course->departmentcode
		&& this->term_no == course->term_no && this->group_no == course->group_no) {
		return true;
	}
	return false;
}

bool PresentedCourse::searchSamePresentedCourseID(const std::vector<PresentedCourse*>& v) const {
	for (const auto& course : v) {
		if (this->coursecode == course->coursecode && this->groupcode == course->groupcode && this->departmentcode == course->departmentcode
			&& this->term_no == course->term_no && this->group_no == course->group_no) {
			return true;
		}
	}
	return false;
}

int PresentedCourse::getPresentedCourseID() const {
	return std::stoi(std::to_string(term_no) + std::to_string(getCourseID()) + std::to_string(group_no));
}
