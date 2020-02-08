#include "Professor.h"

void Professor::setCourses(const std::vector<PresentedCourse*>& _courses) {
	courses = _courses;
}

std::vector<PresentedCourse*> Professor::getCourses(void) const {
	return courses;
}

void Professor::addCourse(PresentedCourse* course) {
	if (std::find(courses.begin(), courses.end(), course) == courses.end()) {
		courses.push_back(course);
	}
}

void Professor::removeCourse(PresentedCourse* course) {
	std::vector<PresentedCourse*>::iterator position = std::find(courses.begin(), courses.end(), course);
	if (position != courses.end()) {
		courses.erase(position);
	}
}
void Professor::replyToObjecton(Student* _student, PresentedCourse* _course, std::string _objection_reply_text) {
	_student->setObjectionReplyTextofCourse(_course, _objection_reply_text);

}
std::string Professor::viewObjectonReply(Student* _student, PresentedCourse* _course) const {
	return _student->getObjectionReplyTextofCourse(_course);
}




bool AdjunctProfessor::changePassword(std::string current_pass, std::string new_pass) {
	if (checkPassword(current_pass)) {
		setPassword(new_pass);
		return true;
	}
	else {
		return false;
	}
}

void Faculty::setDegree(int _degree) {
	degree = _degree;
}

int Faculty::getDegree(void) const {
	return degree;
}

void Faculty::setAsSupervisor(bool _is_supervisor) {
	is_supervisor = _is_supervisor;
}

bool Faculty::getisSupervisor(void) const {
	return is_supervisor;
}

void Faculty::setSupervisedStudents(const std::vector<Student*>& _supervised_students) {
	supervised_students = _supervised_students;
}

std::vector<Student*> Faculty::getSupervisedStudents(void) const {
	return supervised_students;
}

void Faculty::addSupervisedStudent(Student* student) {
	if (std::find(supervised_students.begin(), supervised_students.end(), student) == supervised_students.end()) {
		supervised_students.push_back(student);
	}
}

void Faculty::removeSupervisedStudent(Student* student) {
	std::vector<Student*>::iterator position = std::find(supervised_students.begin(), supervised_students.end(), student);
	if (position != supervised_students.end()) {
		supervised_students.erase(position);
	}
}

bool Faculty::changePassword(std::string current_pass, std::string new_pass) {
	if (checkPassword(current_pass)) {
		setPassword(new_pass);
		return true;
	}
	else {
		return false;
	}
}




void GroupManager::setGroupCourses(std::map<int, Course*> _group_courses) {
	group_courses = _group_courses;
}

std::map<int, Course*> GroupManager::getGroupCourses() {
	return group_courses;
}

void GroupManager::setGroupPresentedCourses(std::map<int, PresentedCourse*> _group_presentedcourses) {
	group_presentedcourses = _group_presentedcourses;
}

std::map<int, PresentedCourse*> GroupManager::getGroupPresentedCourses() {
	return group_presentedcourses;
}

bool GroupManager::addGroupCourse(short coursecode, std::string name, char credit, char type, std::vector<Course*> prerequisites, std::vector<Course*> corequisites) {
	Course* course = new Course(departmentcode, groupcode, coursecode, credit, name, type);
	if (group_courses.count(course->getCourseID()) == 0) {
		course->setCorequisites(corequisites);
		course->setPrerequisites(prerequisites);
		group_courses.insert(std::make_pair(course->getCourseID(), course));
		return true;
	}
	else {
		delete course;
		return false;
	}
}

bool GroupManager::deleteGroupCourse(Course* _course) {
	if (group_courses.count(_course->getCourseID())) {
		group_courses.erase(_course->getCourseID());
		delete _course;
		return true;
	}
	return false;
}

void GroupManager::deleteAllGroupCourses() {
	for (auto& c : group_courses) {
		delete c.second;
	}
	group_courses.clear();
}

bool GroupManager::addGroupPresentedCourse(Course* course, int term_no, char group_no, Professor* course_professor, int capacity,
	CourseTime course_time, std::string course_location, ExamTime finalexam_time, std::string finalexam_location) {
	if (group_courses.count(course->getCourseID()) == 0) {
		return false;
	}
	PresentedCourse* presented_course = new PresentedCourse(course, term_no, group_no, course_professor, capacity);
	if (group_presentedcourses.count(presented_course->getPresentedCourseID()) == 0) {
		presented_course->setCourseTime(course_time);
		presented_course->setCourseLocation(course_location);
		presented_course->setFinalExamTime(finalexam_time);
		presented_course->setFinalExamLocation(finalexam_location);
		group_presentedcourses.insert(std::make_pair(presented_course->getPresentedCourseID(), presented_course));
		return true;
	}
	else {
		delete presented_course;
		return false;
	}
}

bool GroupManager::deleteGroupPresentedCourse(PresentedCourse* _presentedcourse) {
	if (group_presentedcourses.count(_presentedcourse->getPresentedCourseID())) {
		group_presentedcourses.erase(_presentedcourse->getPresentedCourseID());
		delete _presentedcourse;
		return true;
	}
	return false;
}

void GroupManager::deleteAllGroupPresentedCourses() {
	for (auto& c : group_presentedcourses) {
		delete c.second;
	}
	group_presentedcourses.clear();
}




DepartmentHead::DepartmentHead(Faculty* _faculty) {
	username = _faculty->getUserName();
	password = _faculty->getPassword();
	firstname = _faculty->getFirstName();
	lastname = _faculty->getLastName();
	departmentcode = _faculty->getDepartmentCode();
	groupcode = _faculty->getGroupCode();
	courses = _faculty->getCourses();
	degree = _faculty->getDegree();
	is_supervisor = _faculty->getisSupervisor();
	supervised_students = _faculty->getSupervisedStudents();
}

void DepartmentHead::setDepartmentProfessors(std::map<int, Professor*> _professors) {
	professors = _professors;
}

std::map<int, Professor*> DepartmentHead::getDepartmentProfessors(void) const {
	return professors;
}

// returns an int <= 5 which shows each professor assessment
int DepartmentHead::calculateProfessorAssessmentSum(Professor* _professor) const {
	std::vector<PresentedCourse*> _courses = _professor->getCourses();
	int students_count = 0, assessments_sum = 0;
	for (int i = 0; i < _courses.size(); i++) {
		std::vector<Student*> students = _courses[i]->getCourseStudents();
		for (int j = 0; j < students.size(); j++) {
			std::vector<char> assessment = students[j]->getAssessmentAnswersofCourse(_courses[i]);
			int temp = 0;
			for (int k = 0; k < assessment.size(); k++)
				temp += assessment[k];
			assessments_sum += (temp / assessment.size());
			students_count++;
		}
	}
	return assessments_sum / students_count;
}

void DepartmentHead::addFaculty(int _username, std::string _password, std::string _firstname, std::string _lastname) {
	Professor* faculty = new Faculty(_username, _password, _firstname, _lastname, this->departmentcode);
	professors.insert(std::make_pair(faculty->getUserName(), faculty));
}

void DepartmentHead::addAdjunctProfessor(int _username, std::string _password, std::string _firstname, std::string _lastname ,int groupcode) {
    Professor* adjunct_professor(new AdjunctProfessor(_username, _password, _firstname, _lastname, this->departmentcode, groupcode));
	professors.insert(std::make_pair(adjunct_professor->getUserName(), adjunct_professor));
}

void DepartmentHead::deleteProfessor(Professor* _professor) {
	if (professors.count(_professor->getUserName())) {
		professors.erase(_professor->getUserName());
	}
}

std::map<PresentedCourse*, std::vector<char>> DepartmentHead::ProfessorAssessment(Professor* _professor) const {
	std::vector<PresentedCourse*> _courses = _professor->getCourses();
	std::map<PresentedCourse*, std::vector<char>> assessments;
	for (int i = 0; i < _courses.size(); i++) {
		std::vector<Student*> students = _courses[i]->getCourseStudents();

		for (int j = 0; j < students.size(); j++) {
			std::vector<char> assessment_sum;
			std::vector<char> assessment_temp = students[j]->getAssessmentAnswersofCourse(_courses[i]);
			for (int k = 0; k < assessment_temp.size(); k++) {
				assessment_sum[k] += assessment_temp[k];
				if (j == (students.size() - 1))
					assessment_sum[k] /= assessment_temp.size();
			}
			assessments.insert(std::make_pair(_courses[i], assessment_sum));
		}
	}
	return assessments;
}

void DepartmentHead::calcSalary(int* _degree_base_pay, int _max_assesment_addition) const {
	std::map<int, Professor*> professors = getDepartmentProfessors();
	for (std::map<int, Professor*>::iterator it = professors.begin(); it != professors.end(); it++) {
		Faculty* faculty = dynamic_cast<Faculty*> (it->second);
		int salary = 0;
		if (faculty) {
			salary = _degree_base_pay[faculty->getDegree()] + (calculateProfessorAssessmentSum(it->second) / 5) * _max_assesment_addition;
		}
		else {
			salary = _degree_base_pay[0] + (calculateProfessorAssessmentSum(it->second) / 5) * _max_assesment_addition;
		}
	}

}
