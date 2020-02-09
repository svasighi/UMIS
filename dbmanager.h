#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QCryptographicHash>
#include "variables.h"

class DbManager
{
public:
    DbManager();
    ~DbManager();
    bool addProfessor(int username, const QString& password, const QString& firstname, const QString& lastname, const int& departmentcode, const int& groupcode, const QString& object_type, const int& is_supervisor, const int& degree);
    bool ProfessorExist(int);
    bool deleteProfessor(const int);
    Professor* getProfessor(int);
    std::vector<Professor*> allProfessors(void);

    bool addStudent(int username, const QString& password, const QString& firstname, const QString& lastname, const int& departmentcode, const int& groupcode, const int& type, const QString& field );
    bool StudentExist(int);
    bool deleteStudent(const int);
    Student* getStudent(int);
    std::vector<Student*> allStudents(void);

    bool addCourse(const int& departmentcode, const int& groupcode,const int& coursecode, const int& credit, const QString& name, const int& type);
    bool courseExistByCode(int ,int ,int);
    bool deleteCourseByCode(int ,int ,int);
    Course* getCourseByCode(int ,int ,int);
    std::vector<Course*> allCourse(void);
    std::vector<Course*> getCourseByDepartment(int department);
    std::vector<Course*> getCourseByGroup(int departmentcode , int groupcode);

    bool addPresentedCourse(const int& course_id, const int& course_professor_id,const int& capacity, const int& enrolled_number, const int& waiting_number, const int& group_number, const int& term_number, std::vector<Course*> corequisit, std::vector<Course*> preriqisit);
    bool deletePresentedCourseByCode(const int& course_id ,const int& course_professor_id,const int& term_number);
    bool presentedCourseExistbyCode(const int& course_id ,const int& course_professor_id,const int& term_number);
    PresentedCourse* getPresentedCourseByCode(const int& course_id ,const int& course_professor_id ,const int& term_number);
    std::vector<PresentedCourse*> allPresentedCourse(void);
    std::vector<PresentedCourse*> getPresentedCourseByCourseId(const int& course_id ,const int& term_number);
    std::vector<PresentedCourse*> getPresentedCourseByCourseProfessorId(const int& course_professor_id ,const int& term_number);
    std::vector<PresentedCourse*> getPresentedCourseByDepartment(const int& departmentcode ,const int& term_number);

private:
    QSqlDatabase m_db;
};
#endif // DBMANAGER_H
