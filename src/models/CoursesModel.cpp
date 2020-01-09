#include <sqlite3.h>
#include"BaseModel.cpp"
#include<vector>


class CoursesModel :public BaseModel{
public:
    std::vector<Course*> getAllCourses()const{} //forward definition 
    int getFee(void)const{}
};