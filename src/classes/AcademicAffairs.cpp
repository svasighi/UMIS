#include "../include/AcademicAffairs.h"

std::string AcademicAffairsStaff::getCareer() const {
	return career;
}

void AcademicAffairsStaff::setCareer(std::string _career) {
	career = _career;
}

void AcademicAffairsStaff::setStudents(std::vector<Student*> _students) {
	students = _students;
}

std::vector<Student*> AcademicAffairsStaff::getStudents() const {
	return students;
}
