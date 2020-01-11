#include "../include/AcademicAffairs.h"
#include "../models/AcademicAffairsModel.cpp"
#include "../classes/Student.cpp"
#include "../classes/Course.cpp"
#include <vector>

std::vector<Student*> AcademicAffairsStaff::getStudents(void) {
    return students;
}

void AcademicAffairsStaff::setStudents(std::vector<Student*> _students) {
   students = _students; 
}

void AcademicAffairsStaff::setCareer(std::string _career) {
    career = _career;
}

std::string AcademicAffairsStaff::getCareer(void) {
    return career;
}
