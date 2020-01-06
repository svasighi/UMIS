#include <iostream>
#include "AcademicAffairs.h"
 
class Professor{

};
// it's gonna be ad
class AdjunctProfessor : public Professor { 

};

class Faculty : public AdjunctProfessor{

};
class DepartmentHead : public Faculty{

};
class DepartmentAcademicAffairsStaff :public AcademicAffairsStaff{

};

int main(){

}