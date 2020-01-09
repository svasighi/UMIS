#include <sqlite3.h>
#include"BaseModel.cpp"



class AcademicAffairsModel :public BaseModel{
public:
    std::vector<Student*> getStudentsbyDepartment(int _department_id)const{} //forward definition 
    int getFee(void)const{}
};