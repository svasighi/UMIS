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

void Faculty::setDegree(int _degree) {
	degree = _degree;
}

int Faculty::getDegree(void) const {
	return degree;
}

void Faculty::setAsSupervisor(void) {
	this->is_supervisor = true;
}

bool Faculty::isSupervisor(void) const {
	return is_supervisor;
}

void Faculty::setAsHead(void) {
	this->is_head = true;
}

bool Faculty::isHead(void) const {
	return is_head;
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

void Faculty::applyEnrollment(Student _student) {} //forward definition

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
// returns an int <= 5 which shows each professor assessment
int DepartmentHead::ProfessorAssessment(Professor _professor){
		
}

void DepartmentHead::addProfessor(int _username, std::string _password, std::string _firstname, std::string _lastname, int _departmentcode){

	Professor professor(_username ,md5(_password) ,_firstname ,_lastname ,_departmentcode);
	BinaryFile <Professor>binary_file((char*) "../storage/Professors.dat" );
	binary_file.AddRecord(professor);
}

void DepartmentHead::calcSalary(int* _degree_base_pay ,int _max_assesment_addition ){
	BinaryFile <Professor>binary_file((char*) "../storage/Professors.dat");
	std::vector<Professor*> professors = binary_file.FetchAllRecords();
	for(int i = 0 ; i < professors.size(); i++){
		Faculty* faculty = dynamic_cast<Faculty*> (professors[i]);
		int salary = 0;
		if(faculty){
			salary = _degree_base_pay[(*faculty).getDegree()] + (ProfessorAssessment(*professors[i]) / 5) * _max_assesment_addition;
		}else{
			salary = _degree_base_pay[0] + (ProfessorAssessment(*professors[i]) / 5) * _max_assesment_addition;
		}
		BinaryFile <std::string>salaries((char*) "../storage/Professors.dat");
		salaries.AddRecord( to_string((*professors[i]).getUserName()) + to_string(salary));
	}
}