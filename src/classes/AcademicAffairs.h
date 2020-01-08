#include <iostream>
#include "..\models\AcademicAffairsModel.cpp"
<<<<<<< HEAD
=======
#include "User.h"
>>>>>>> 10f3851f879d1ecd7d4591616906b693a1ca8344

class AcademicAffairsStaff :public User{
    std::vector<Studnet*> students;

};
class WholeAcademicAffairsStaff :public AcademicAffairsStaff{
// list of all students 
    std::vector<Presented_Course*> courses;
public:
    void ChangeDepartmentHead(Professor prof); //forward definitions
};
