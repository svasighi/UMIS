#include "../include/AcademicAffairs.h"
#include "../include/Professor.h"

std::string AcademicAffairsStaff::getCareer() const {
	return career;
}

void AcademicAffairsStaff::setCareer(std::string _career) {
	career = _career;
}

void AcademicAffairsStaff::setStudents(std::map<int, Student*> _students) {
	students = _students;
}

std::map<int, Student*> AcademicAffairsStaff::getStudents() const {
	return students;
}
void TopAcademicAffairsStaff::changeDepartmentHead(Faculty* _faculty) {
	bool done = false;
	std::map<int, Professor* > _professors; ////////////////////////////////////////// = Professor::readAllProfessors();
	DepartmentHead* current_departmenthead = nullptr;
	for (std::map<int, Professor* >::iterator it = _professors.begin(); it != _professors.end(); it++) {

		current_departmenthead = dynamic_cast<DepartmentHead*> (it->second);
		if (current_departmenthead) {
			Faculty* new_faculty = dynamic_cast<Faculty*> (current_departmenthead);
			if (new_faculty)
			{
				DepartmentHead* new_departmenthead = dynamic_cast<DepartmentHead*> (_faculty);
				//BinaryFile<Professor> binary_file((char*) "../storage/Professors.dat");
				//binary_file.UpdateRecord(*new_departmenthead);
				//binary_file.UpdateRecord(*new_faculty);
			}
		}
		done = true;
	}
	if (done == false) {
		DepartmentHead* new_departmenthead = dynamic_cast<DepartmentHead*> (_faculty);
		//BinaryFile<Professor> binary_file((char*) "../storage/Professors.dat");
		//binary_file.UpdateRecord(*new_departmenthead);
	}
}

