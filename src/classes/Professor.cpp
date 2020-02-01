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
int DepartmentHead::CalculateProfessorAssessmentSum(Professor* _professor) const {
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

std::vector<Professor*> DepartmentHead::getProfessors() const {
	return professors;
}

void DepartmentHead::setProfessors(std::vector<Professor*> _professors) {
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
			assessments.insert(std::pair<Presented_Course*, std::vector<char>>(courses[i], assessment_sum));
		}
	 }
}

void DepartmentHead::addProfessor(int _username, std::string _password, std::string _firstname, std::string _lastname) {

	Professor * professor = new Professor(_username, md5(_password), _firstname, _lastname, this->departmentcode);
	BinaryFile <Professor>binary_file((char*) "../storage/Professors.dat");
	binary_file.AddRecord(*professor);
	professors.push_back(professor);
}
void DepartmentHead::deleteProfessor(Professor* _professor)  {
	BinaryFile <Professor>binary_file((char*) "../storage/Professors.dat");
	binary_file.DeleteRecordByID(_professor->getUserName());
	professors.erase(find(professors.begin(), professors.end(), _professor));
}
void DepartmentHead::ReadAllProfessors()  {
	std::vector<Professor*> department_professors;
	BinaryFile <Professor>binary_file((char*) "../storage/Professors.dat");
	std::vector<Professor*> professors = binary_file.FetchAllRecords();
	for (int i = 0; i < professors.size(); i++) {
		if (professors[i]->getDepartmentCode() == departmentcode && professors[i]->getUserName() != username )
			department_professors.push_back(professors[i]);
	}
	setProfessors(department_professors);
}
void DepartmentHead::calcSalary(int* _degree_base_pay, int _max_assesment_addition) const {
	BinaryFile <Professor>binary_file((char*) "../storage/Professors.dat");
	std::vector<Professor*> professors = binary_file.FetchAllRecords();
	for (int i = 0; i < professors.size(); i++) {
		Faculty* faculty = dynamic_cast<Faculty*> (professors[i]);
		int salary = 0;
		if (faculty) {
			salary = _degree_base_pay[faculty->getDegree()] + (CalculateProfessorAssessmentSum(*professors[i]) / 5) * _max_assesment_addition;
		} else {
			salary = _degree_base_pay[0] + (CalculateProfessorAssessmentSum(*professors[i]) / 5) * _max_assesment_addition;
		}
		BinaryFile <std::string>salaries((char*) "../storage/Professors.dat");
		salaries.AddRecord(std::to_string(professors[i]->getUserName()) + std::to_string(salary));
	}
}
