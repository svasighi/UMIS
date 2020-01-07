#include <iostream>
#include "..\models\AcademicAffairsModel.cpp"
#include "User.h"

class AcademicAffairsStaff :public User{
    std::vector<Studnet*> students;

};
class WholeAcademicAffairsStaff :public AcademicAffairsStaff{
// list of all students 
    std::vector<Presented_Course*> courses;
public:
    void ChangeDepartmentHead(Professor prof); //forward definitions
};
