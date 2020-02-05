#include "../include/Professor.h"

void Professor::setCourses(std::vector<Presented_Course*> _courses) {
	courses = _courses;
}

std::vector<Presented_Course*> Professor::getCourses(void) const {
	return courses;
}

void Professor::addCourse(Presented_Course* course) {
	courses.push_back(course);
}

void Professor::removeCourse(Presented_Course* course) {
	courses.erase(find(courses.begin(), courses.end(), course));
}
void Professor::replyToObjecton(Student* _student,Presented_Course* _course, std::string _objection_reply_text){
	_student->setObjectionReplyTextofCourse(_course ,_objection_reply_text);
		
}
std::string Professor::viewObjectonReply(Student* _student,Presented_Course* _course) const{
	
	return	_student->getObjectionReplyTextofCourse(_course);
}
 std::map<int,Professor*>  Professor::readAllProfessors(void){
	std::map<int,Professor*> TempProfessors;
	
	BinaryFile<Professor> binary_file((char*) "../storage/Professors.dat");
	std::vector<Professor*> professors = binary_file.FetchAllRecords();
	
	for (int i = 0; i < professors.size(); i++) {
		TempProfessors.insert(std::make_pair(professors[i]->getUserName(),professors[i]));
	}
	return TempProfessors;	
}

void Faculty::setDegree(int _degree) {
	degree = _degree;
}

int Faculty::getDegree(void) const {
	return degree;
}

void Faculty::setAsSupervisor(void) {
	this->is_supervisor = true;
}

bool Faculty::getisSupervisor(void) const {
	return is_supervisor;
}

void Faculty::setSupervisedStudents(std::vector<Student*> _supervised_students) {
	supervised_students = _supervised_students;
}

std::vector<Student*> Faculty::getSupervisedStudents(void) const {
	return supervised_students;
}

void Faculty::addSupervisedStudents(Student* _supervised_student) {
	supervised_students.push_back(_supervised_student);
}

void Faculty::removeSupervisedStudents(Student* _supervised_student) {
	supervised_students.erase(find(supervised_students.begin(), supervised_students.end(), _supervised_student));
}

void Faculty::applyEnrollment(Student* _student) {} //forward definition


std::map<int,Presented_Course*> GroupManager::getGroupCourses(){
	return group_courses;
}
void GroupManager::setGroupCourses(std::map<int,Presented_Course*> _group_courses){
	group_courses = _group_courses;
}
void GroupManager::createGroupCourse(int _course_id ,std::string _name, int _credit, int _type, int _term_no, int _group_no, Professor* _course_professor, int _capacity , std::vector<Course*> prerequisites, std::vector<Course*> corequisites){
	
	Course* temp_course = nullptr;
	Presented_Course* temp_presented_course = nullptr;
	BinaryFile<Course> binary_file((char*) "../storage/Professors.dat");
	std::map<int, Course*> allcourses = Course::readAllCourses();

	for(std::map<int, Course*>::iterator it = allcourses.begin(); it != allcourses.end(); it++) {
		if( groupcode == (it->second)->getGroup_id() &&  departmentcode == (it->second)->getDepartment_id()  && _course_id == (it->second)->getCourse_id())
		{
			temp_course = (it->second);
			break;
		}
	}
	if(!temp_course){
		temp_course = new Course(departmentcode, groupcode, _course_id, _credit, _name, _type);
		temp_course->setCorequisites(corequisites);
		temp_course->setPrerequisites(prerequisites);
	}else{
		Presented_Course* temp_presented_course = new Presented_Course(temp_course,_term_no, _group_no,_course_professor,_capacity);
		group_courses.insert(std::make_pair(std::stoi(std::to_string(temp_presented_course->getDepartment_id()) + std::to_string(temp_presented_course->getGroup_id()) + std::to_string(temp_presented_course->getCourse_id())) , temp_presented_course));
	}
}
void GroupManager::deleteGroupCourse(Presented_Course* _course){
	
	std::map<int, Course*> allcourses = Course::readAllCourses();

	BinaryFile<Course> binary_file((char*) "../storage/Courses.dat");
	binary_file.DeleteRecord(*_course);
	group_courses.erase(std::stoi(std::to_string(_course->getDepartment_id()) + std::to_string(_course->getGroup_id()) + std::to_string(_course->getCourse_id())));
}
void GroupManager::updateGroupCourse(Presented_Course* _course){
	
	BinaryFile <Presented_Course>binary_file((char*) "storage/Courses.dat" );
	binary_file.UpdateRecord(_course);
	group_courses.erase(_course->getCourse_id());
	group_courses.insert(std::make_pair(std::stoi(std::to_string(_course->getDepartment_id()) + std::to_string(_course->getGroup_id()) + std::to_string(_course->getCourse_id())) , _course));
}

DepartmentHead::DepartmentHead(Faculty* _faculty)
{
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
	std::vector<Presented_Course*> courses = _professor->getCourses();
	int students_count = 0 , assessments_sum;
	 for (int i = 0; i < courses.size(); i++) {
		std::vector<Student*> students = courses[i]->getCourseStudents();
		for (int j = 0 ; j < students.size(); j++) {
			std::vector<char> assessment = students[j]->getAssessmentAnswersofCourse(courses[i]);
			int temp = 0;
			for (int k = 0; k < assessment.size(); k++)
				temp += assessment[k];
			assessments_sum += (temp / assessment.size());
			students_count++;			
		}
	 }
	 return assessments_sum / students_count;
}

std::map<int,Professor*> DepartmentHead::getDepartmentProfessors(void) const {
	return professors;
}

void DepartmentHead::setDepartmentProfessors(std::map<int,Professor*> _professors) {
	professors = _professors;
}

std::map<Presented_Course*, std::vector<char>> DepartmentHead::ProfessorAssessment(Professor* _professor) const {
	std::vector<Presented_Course*> courses = _professor->getCourses();
	std::map<Presented_Course*, std::vector<char>> assessments;
	 for (int i = 0; i < courses.size(); i++) {
		std::vector<Student*> students = courses[i]->getCourseStudents();
		
		for (int j = 0; j < students.size(); j++) {
			std::vector<char> assessment_sum;
			std::vector<char> assessment_temp = students[j]->getAssessmentAnswersofCourse(courses[i]);
			for (int k = 0; k < assessment_temp.size(); k++) {
				assessment_sum[k] += assessment_temp[k];
				if (j == (students.size() - 1))
					assessment_sum[k] /= assessment_temp.size();
			}
			assessments.insert(std::make_pair<Presented_Course*, std::vector<char>>(courses[i], assessment_sum));
		}
	 }
}
void DepartmentHead::addAdjunctProfessor(int _username, std::string _password, std::string _firstname, std::string _lastname){
	Professor * professor = new AdjunctProfessor(_username, _password, _firstname, _lastname, this->departmentcode);
	BinaryFile<Professor> binary_file((char*) "../storage/AdjunctProfessors.dat");
	binary_file.AddRecord(*professor);
	professors.insert(std::make_pair(professor->getUserName(),professor));
}
void DepartmentHead::addDepartmentAcademicAffairsStaff(int, std::string, std::string, std::string){}

void DepartmentHead::changeToFacutly(Professor*){}
void DepartmentHead::changeToGroupManager(Faculty*){}
void DepartmentHead::addProfessor(int _username, std::string _password, std::string _firstname, std::string _lastname) {

	Professor * professor = new Professor(_username, _password, _firstname, _lastname, this->departmentcode);
	BinaryFile<Professor> binary_file((char*) "../storage/Professors.dat");
	binary_file.AddRecord(*professor);
	professors.insert(std::make_pair(professor->getUserName(),professor));
}

void DepartmentHead::deleteProfessor(Professor* _professor) {
	BinaryFile<Professor> binary_file((char*) "../storage/Professors.dat");
	binary_file.DeleteRecord(*_professor);
	professors.erase(find(professors.begin(), professors.end(), _professor));
}
	std::vector<Professor*> getDepartmentProfessors(void);
	void getDepartmentProfessors(std::vector<Professor*>);
void DepartmentHead::readAllDepartmentProfessors() {
	std::map<int,Professor*> department_professors;
	
	BinaryFile<Professor> binary_file((char*) "../storage/Professors.dat");
	std::vector<Professor*> professors = binary_file.FetchAllRecords();
	for (int i = 0; i < professors.size(); i++) {
		if (professors[i]->getDepartmentCode() == departmentcode && professors[i]->getUserName() != username )
			department_professors.insert(std::make_pair(professors[i]->getUserName(),professors[i]));
	}
	setDepartmentProfessors(department_professors);
}

void DepartmentHead::calcSalary(int* _degree_base_pay, int _max_assesment_addition) const {
	std::map<int,Professor*> professors = getDepartmentProfessors();
	for(std::map<int,Professor*>::iterator it = professors.begin(); it != professors.end(); it++) {
		Faculty* faculty = dynamic_cast<Faculty*> (it->second);
		int salary = 0;
		if (faculty) {
			salary = _degree_base_pay[faculty->getDegree()] + (calculateProfessorAssessmentSum(it->second) / 5) * _max_assesment_addition;
		} else {
			salary = _degree_base_pay[0] + (calculateProfessorAssessmentSum(it->second) / 5) * _max_assesment_addition;
		}
		BinaryFile<std::string> salaries((char*) "../storage/Salaries.dat");
		salaries.AddRecord(std::to_string(it->second->getUserName()) + std::to_string(salary));
	}
	
}

void DepartmentAcademicAffairsStaff::setCourses(std::vector<Course*> _courses) {
	courses = _courses;
}

std::vector<Course*> DepartmentAcademicAffairsStaff::getCourses(void) const {
	return courses;
}

void DepartmentAcademicAffairsStaff::setPresentedCourses(std::vector<Presented_Course*> _presented_courses) {
	presented_courses = _presented_courses;
}

std::vector<Presented_Course*> DepartmentAcademicAffairsStaff::getPresentedCourses(void) const {
	return presented_courses;
}
