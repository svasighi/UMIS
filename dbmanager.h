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

private:
    QSqlDatabase m_db;
};
#endif // DBMANAGER_H
