#ifndef DBMANAGER_H
#define DBMANAGER_H
#include<qdebug.h>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <vector>

#include <src/include/User.h>
#include <src/classes/User.cpp>
#include <src/include/Professor.h>
#include <memory>

class DbManager
{
public:
    DbManager(const QString& path);
    bool addUser(const QString& name);
    bool UserExist(int);
    bool deleteUser(const int);
    std::pair<QString, std::unique_ptr<User>> getUser(int username);
    // professor
    bool addProfessor(const QString& name);
    bool ProfessorExist(int);
    bool deleteProfessor(const int);
    std::pair<QString, std::unique_ptr<User>> getProfessor(int);
    std::vector<std::unique_ptr<Professor>> allProfessors(void);

private:
    QSqlDatabase m_db;
};
#endif // DBMANAGER_H
