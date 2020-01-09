#include "../include/AcademicAffairs.h"
#include "../models/AcademicAffairsModel.cpp"
#include "../classes/Student.cpp"
#include <vector>


std::vector<Student *> AcademicAffairsStaff::getStudents(){
    AcademicAffairsModel AAmodel;
    return AAmodel.getStudentsbyDepartment(departmentcode);
}
