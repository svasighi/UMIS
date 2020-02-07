#include "../include/Professor.h"

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

void Faculty::applyEnrollment(Student* _student) {} //forward definition

std::map<int, PresentedCourse*> GroupManager::getGroupCourses() {
	return group_courses;
}

void GroupManager::setGroupCourses(std::map<int, PresentedCourse*> _group_courses) {
	group_courses = _group_courses;
}

void GroupManager::createGroupCourse(int _course_id, std::string _name, int _credit, int _type, int _term_no, int _group_no, Professor* _course_professor, int _capacity, std::vector<Course*> prerequisites, std::vector<Course*> corequisites) {

	Course* temp_course = nullptr;
	PresentedCourse* temp_PresentedCourse = nullptr;
	//BinaryFile<Course> binary_file((char*) "../storage/Professors.dat");
	std::map<int, Course*> allcourses;/////////////////////////// = Course::readAllCourses();

	for (std::map<int, Course*>::iterator it = allcourses.begin(); it != allcourses.end(); it++) {
		if (groupcode == (it->second)->getGroupCode() && departmentcode == (it->second)->getDepartmentCode() && _course_id == (it->second)->getCourseCode())
		{
			temp_course = (it->second);
			break;
		}
	}
	if (!temp_course) {
		temp_course = new Course(departmentcode, groupcode, _course_id, _credit, _name, _type);
		temp_course->setCorequisites(corequisites);
		temp_course->setPrerequisites(prerequisites);
	}
	else {
		PresentedCourse* temp_PresentedCourse = new PresentedCourse(temp_course, _term_no, _group_no, _course_professor, _capacity);
		group_courses.insert(std::make_pair(temp_PresentedCourse->getCourseID(), temp_PresentedCourse));
	}
}
void GroupManager::deleteGroupCourse(PresentedCourse* _course) {
	//std::map<int, Course*> allcourses;////////////////////////////// = Course::readAllCourses();
	//BinaryFile<Course> binary_file((char*) "../storage/Courses.dat");
	//binary_file.DeleteRecord(*_course);
	if (group_courses.count(_course->getCourseID())) {
		group_courses.erase(_course->getCourseID());
	}
}
void GroupManager::updateGroupCourse(PresentedCourse* _course) {
	//BinaryFile <PresentedCourse>binary_file((char*) "storage/Courses.dat" );
	//binary_file.UpdateRecord(_course);
	if (group_courses.count(_course->getCourseID())) {
		group_courses.erase(_course->getCourseID());
	}
	group_courses.insert(std::make_pair(_course->getCourseID(), _course));
}

DepartmentHead::DepartmentHead(Faculty* _faculty) {
	username = _faculty->getUserName();
	firstname = _faculty->getFirstName();
	lastname = _faculty->getLastName();
	degree = _faculty->getDegree();
	departmentcode = _faculty->getDepartmentCode();
	password = _faculty->getPassword();
	courses = _faculty->getCourses();
	supervised_students = _faculty->getSupervisedStudents();
	is_supervisor = _faculty->getisSupervisor();
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

std::map<int, Professor*> DepartmentHead::getDepartmentProfessors(void) const {
	return professors;
}

void DepartmentHead::setDepartmentProfessors(std::map<int, Professor*> _professors) {
	professors = _professors;
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

void DepartmentHead::addFaculty(int _username, std::string _password, std::string _firstname, std::string _lastname) {
	Professor* faculty = new Faculty(_username, _password, _firstname, _lastname, this->departmentcode);
	//BinaryFile<Professor> binary_file((char*) "../storage/Professors.dat");
	//binary_file.AddRecord(*professor);
	professors.insert(std::make_pair(faculty->getUserName(), faculty));
}

void DepartmentHead::addAdjunctProfessor(int _username, std::string _password, std::string _firstname, std::string _lastname) {
	std::unique_ptr<AdjunctProfessor> adjunct_professor(new AdjunctProfessor(_username, _password, _firstname, _lastname, this->departmentcode));
	// professors.insert(std::make_pair(adjunct_professor->getUserName(), adjunct_professor));
}
void DepartmentHead::addDepartmentAcademicAffairsStaff(int, std::string, std::string, std::string) {}

void DepartmentHead::changeToFacutly(Professor*) {}
void DepartmentHead::changeToGroupManager(Faculty*) {}



void DepartmentHead::deleteProfessor(Professor* _professor) {
	//	BinaryFile<Professor> binary_file((char*) "../storage/Professors.dat");
		//binary_file.DeleteRecord(*_professor);
	if (professors.count(_professor->getUserName())) {
		professors.erase(_professor->getUserName());
	}
}


//std::vector<Professor*> DepartmentHead::getDepartmentProfessors(void);
//void DepartmentHead::getDepartmentProfessors(std::vector<Professor*>);


void DepartmentHead::readAllDepartmentProfessors() {
	std::map<int, Professor*> department_professors;

	//BinaryFile<Professor> binary_file((char*) "../storage/Professors.dat");
	//std::vector<Professor*> professors = binary_file.FetchAllRecords();
	for (int i = 0; i < professors.size(); i++) {
		if (professors[i]->getDepartmentCode() == departmentcode && professors[i]->getUserName() != username)
		;//  department_professors.insert(std::make_pair(professors[i]->getUserName(),professors[i]));
	}
	setDepartmentProfessors(department_professors);
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
		//	BinaryFile<std::string> salaries((char*) "../storage/Salaries.dat");
		//	salaries.AddRecord(std::to_string(it->second->getUserName()) + std::to_string(salary));
	}

}
