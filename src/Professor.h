#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>
#include "User.h"
#include "Course.h"
#include "Student.h"
#include "AcademicAffairs.h"

class Professor : virtual public User {
protected:
    std::vector<PresentedCourse*> courses; //list of presented courses
public:
    Professor() {}
    Professor(int _username, std::string _password, std::string _firstname, std::string _lastname, short _departmentcode, short _groupcode = 0)
        : User(_username, _password, _firstname, _lastname, _departmentcode) {
        groupcode = _groupcode;
    }
    void setCourses(const std::vector<PresentedCourse*>&);
    std::vector<PresentedCourse*> getCourses(void) const;
    void addCourse(PresentedCourse*);
    void removeCourse(PresentedCourse*);
    void replyToObjecton(Student*, PresentedCourse*, std::string);
    std::string viewObjectonReply(Student*, PresentedCourse*) const;
};

class AdjunctProfessor : public Professor {
public:
    AdjunctProfessor() {}
        AdjunctProfessor(int _username, std::string _password, std::string _firstname, std::string _lastname, short _departmentcode , short _groupcode)
                        :User(_username, _password, _firstname, _lastname, _departmentcode) {
            groupcode = _groupcode;
        }
    bool changePassword(std::string current_pass, std::string new_pass);
};

class Faculty : public Professor {
protected:
    int degree;
    bool is_supervisor;
    std::vector<Student*> supervised_students;
public:
    Faculty()
        : degree(0), is_supervisor(false) {}
    Faculty(int _username, std::string _password, std::string _firstname, std::string _lastname, short _departmentcode, short _groupcode = 0, int _degree = 0, bool _is_supervisor = false)
        : degree(_degree), is_supervisor(_is_supervisor), User(_username, _password, _firstname, _lastname, _departmentcode, _groupcode) {
        groupcode = _groupcode;
    }
    void setDegree(int);
    int getDegree(void) const;
    void setAsSupervisor(bool = true);
    bool getisSupervisor(void) const;
    void setSupervisedStudents(const std::vector<Student*>&);
    std::vector<Student*> getSupervisedStudents(void) const;
    void addSupervisedStudent(Student*);
    void removeSupervisedStudent(Student*);
    //void applyEnrollment(Student*);
    bool changePassword(std::string current_pass, std::string new_pass);
};

class GroupManager : public Faculty {
    //PreEnrollment_Stats
    std::map<int, Course*> group_courses;
    std::map<int, PresentedCourse*> group_presentedcourses;
public:
        GroupManager(){}
        GroupManager(int _username, std::string _password, std::string _firstname, std::string _lastname, short _departmentcode, short _groupcode = 0, int _degree = 0, bool _is_supervisor = false )
           : Faculty ( _username, _password, _firstname, _lastname, _departmentcode, _groupcode, _degree, _is_supervisor ){}
        void setGroupCourses( std::map<int, Course*> );
    std::map<int, Course*> getGroupCourses();
    void setGroupPresentedCourses(std::map<int, PresentedCourse*>);
    std::map<int, PresentedCourse*>  getGroupPresentedCourses();
    bool addGroupCourse(short coursecode, std::string name, char credit, char type, std::vector<Course*> prerequisites, std::vector<Course*> corequisites);
    bool deleteGroupCourse(Course*);
    void deleteAllGroupCourses();
    bool addGroupPresentedCourse(Course* course, int term_no, char group_no, Professor* course_professor, int capacity,
        CourseTime course_time = CourseTime(), std::string course_location = "", ExamTime finalexam_time = ExamTime(), std::string finalexam_location = "");
    bool deleteGroupPresentedCourse(PresentedCourse*);
    void deleteAllGroupPresentedCourses();
};

// .............................DepartmentAcademicAssistant......................................
class DepartmentAcademicAssistant : public Faculty, public DepartmentAcademicAffairsStaff {

public:
    DepartmentAcademicAssistant() {}
};

class DepartmentHead : public Faculty {
    std::map<int, Professor*> professors;
public:
    DepartmentHead(Faculty*);
        DepartmentHead(int _username, std::string _password, std::string _firstname, std::string _lastname, short _departmentcode, short _groupcode = 0, int _degree = 0, bool _is_supervisor = false )
                : Faculty ( _username, _password, _firstname, _lastname, _departmentcode, _groupcode, _degree, _is_supervisor ){}
        void setDepartmentProfessors(std::map<int, Professor*>);
    std::map<int, Professor*> getDepartmentProfessors(void) const;
    void addFaculty(int, std::string, std::string, std::string);
    void addAdjunctProfessor(int, std::string, std::string, std::string ,int);
    void deleteProfessor(Professor*);
    int calculateProfessorAssessmentSum(Professor*) const;
    std::map<PresentedCourse*, std::vector<char>> ProfessorAssessment(Professor*) const;
    void calcSalary(int*, int) const;
    //void addDepartmentAcademicAffairsStaff(int, std::string, std::string, std::string);
    //void changeToFacutly(Professor*);
    //void changeToGroupManager(Faculty*);
};

#endif // PROFESSOR_H
