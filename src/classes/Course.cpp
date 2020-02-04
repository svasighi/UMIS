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

void Course::setPrerequisites(std::vector<Course*> _prerequisites) {
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
	prerequisites.erase(std::find(prerequisites.begin(), prerequisites.end(), course));
}

void Course::setCorequisites(std::vector<Course*> _corequisites) {
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
	corequisites.erase(std::find(corequisites.begin(), corequisites.end(), course));
}

bool Course::haveSameID(Course* course) const {
	if (course->course_id == this->course_id && course->group_id == this->group_id && course->department_id == this->department_id) {
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

bool Course::searchSameIDin(const std::vector<Presented_Course*>& v) const {
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
	: term_no(0), group_no(0), course_professor(nullptr), capacity(0) {}

Presented_Course::Presented_Course(Course* course, int _term_no, char _group_no, Professor* _course_professor, int _capacity)
	: term_no(_term_no), group_no(_group_no), course_professor(_course_professor), capacity(_capacity), Course(*course) {}

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

void Presented_Course::setCourseStudents(std::vector<Student*> _course_students) {
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
	course_students.erase(std::find(course_students.begin(), course_students.end(), student));
}

int Presented_Course::getNumberofStudents() const {
	return course_students.size();
}

int Presented_Course::getNumberofStudentsWithCourseStatus(char _status) const {
	int n = 0;
	for (int i = 0; i < course_students.size(); i++) {
		if (course_students.at(i)->getStatusofCourse(const_cast<Presented_Course*>(this)) == _status) {
			n++;
		}
	}
	return n;
}

void Presented_Course::setCapacity(int _capacity) {
	capacity = _capacity;
}

int Presented_Course::getCapacity() const {
	return capacity;
}

void Presented_Course::setCourseTime(CourseTime _course_time) {
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

void Presented_Course::setFinalExamTime(ExamTime _finalexam_time) {
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
