#include "../include/Professor.h"


	void Professor::setCourses(std::vector<Presented_Course*> _courses) {
		courses = _courses;
	}
	std::vector<Presented_Course*> Professor::getCourses() const {
		return courses;
	}
    void Professor::addCourse(Presented_Course* course) {
		courses.push_back(course);
	}
    void Professor::removeCourse(Presented_Course* course) {
		courses.erase(find(courses.begin(), courses.end(), course));
	}
    int Faculty::getDegree (void) const{
        return degree;
    }
	void Faculty::setDegree(const int _degree){
        degree = _degree;
    }
	bool Faculty::isSupervisor (void) const{
        return isSupervisor;
    }
	void Faculty::setAsSupervisor(void){
        this->isSupervisor = true;
    }
	bool Faculty::isHead (void) const{
        return isHead;
    }
	void Faculty::setAsHead(void){
        this->isHead = true;
    }
    void Faculty::setSupervised_Students(std::vector<Student*> _supervised_students) {
        supervised_students = _supervised_students;
    }
	std::vector<Student*> Faculty::getSupervised_Students(void) const{
        return supervised_students;
    }
	void Faculty::addSupervised_Students(Student* _supervised_student){
        supervised_students.push_back(_supervised_student);
    }
	void Faculty::removeSupervised_Students(Student* _supervised_student){
        supervised_students.erase(find(supervised_students.begin(), supervised_students.end(), _supervised_student));
	}
    void Faculty::applyEnrollment(Student _student){} //forward definition