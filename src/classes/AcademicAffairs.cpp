#include "../include/AcademicAffairs.h"

std::string AcademicAffairsStaff::getCareer() const {
	return career;
}

void AcademicAffairsStaff::setCareer(std::string _career) {
	career = _career;
}

void AcademicAffairsStaff::setStudents(std::map<int,Student*> _students) {
	students = _students;
}

std::map<int,Student*> AcademicAffairsStaff::getStudents() const {
	return students;
}
void TopAcademicAffairsStaff::changeDepartmentHead(){

}
void TopAcademicAffairsStaff::readAllStudents() {
	std::map<int,Student*> TempStudents;
	BinaryFile<Student> binary_file((char*) "../storage/Students.dat");
	std::vector<Student*> student = binary_file.FetchAllRecords();
	
	for (int i = 0; i < student.size(); i++) {
		TempStudents.insert(std::pair(student[i]->getUserName(),student[i]));
	}
	setStudents(TempStudents);
}