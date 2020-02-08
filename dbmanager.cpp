#include "dbmanager.h"
#include <QDir>
#include <QFile>
#include <QMessageBox>

DbManager::DbManager()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE", "Connection");
    QString db_path = QDir::currentPath();
    db_path = db_path + QString("/university.db");
    m_db.setDatabaseName(db_path);
    if (m_db.isOpen())
    {
        QMessageBox msgBox;
        qDebug() << "opened";
    }
    else
    {
        if (!m_db.open())
            qDebug() << m_db.lastError();
    }
}

DbManager::~DbManager()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

bool DbManager::deleteProfessor(int username)
{
    if (ProfessorExist(username))
    {
        QSqlQuery query(m_db);
        query.prepare("DELETE FROM professors WHERE username = (:username)");
        query.bindValue(":username", username);
        bool success = query.exec();

        if (!success)
        {
            qDebug() << "removeProf error: "
                << query.lastError();
            return false;
        }
        return true;
    }
}

Professor* DbManager::getProfessor(int username)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM professors WHERE username = :username ");
    query.bindValue(":username", username);
    if (!query.exec())
    {
        qWarning() << __FUNCTION__ << ":" << __LINE__ << "Failed to fetch professors";
        qWarning() << __FUNCTION__ << ":" << __LINE__ << m_db.databaseName();
    }
    if (query.next())
    {
        int username = username;
        QString password = query.value(2).toString();
        QString firstname = query.value(3).toString();
        QString lastname = query.value(4).toString();
        int departmentcode = query.value(5).toInt();
        int groupcode = query.value(6).toInt();
        QString object_type = query.value(7).toString();
        int is_supervisor = query.value(8).toInt();
        int degree = query.value(9).toInt();
        if (object_type == "faculty")
        {
            Faculty* ProfessorTemp = new Faculty(username, password.toStdString(), firstname.toStdString(), lastname.toStdString(), departmentcode, groupcode, is_supervisor, degree);
            return dynamic_cast<Professor*> (ProfessorTemp);
        }
        else if (object_type == "adjunctprofessor")
        {
            AdjunctProfessor* ProfessorTemp = new AdjunctProfessor(username, password.toStdString(), firstname.toStdString(), lastname.toStdString(), departmentcode, groupcode);

            return dynamic_cast<Professor*> (ProfessorTemp);
        }
        else if (object_type == "groupmanager")
        {
            GroupManager* ProfessorTemp = new GroupManager(username, password.toStdString(), firstname.toStdString(), lastname.toStdString(), departmentcode, groupcode, is_supervisor, degree);
            return dynamic_cast<Professor*> (ProfessorTemp);
        }
        else if (object_type == "departmentacademicassistant")
        {
            //
        }
        else if (object_type == "departmenthead")
        {
            DepartmentHead* ProfessorTemp = new DepartmentHead(username, lastname.toStdString(), password.toStdString(), lastname.toStdString(), departmentcode, groupcode, is_supervisor, degree);
            return dynamic_cast<Professor*> (ProfessorTemp);
        }

    }
}

bool DbManager::addProfessor(int username, const QString& password, const QString& firstname, const QString& lastname, const int& departmentcode, const int& groupcode, const QString& object_type, const int& is_supervisor, const int& degree)
{
    bool success = false;
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO professors (username,password,firstname,lastname,departmentcode,groupcode,object_type,is_supervisor,degree) VALUES (:username,:password,:firstname,:lastname,:departmentcode,:groupcode,:object_type,:is_supervisor,:degree)");
    query.bindValue(":username", username);
    query.bindValue(":password", QString(QCryptographicHash::hash((password.toUtf8()), QCryptographicHash::Md5).toHex()));
    query.bindValue(":firstname", firstname);
    query.bindValue(":lastname", lastname);
    query.bindValue(":departmentcode", departmentcode);
    query.bindValue(":groupcode", groupcode);
    query.bindValue(":object_type", object_type);
    query.bindValue(":is_supervisor", is_supervisor);
    query.bindValue(":degree", degree);
    if (query.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "addProfessor error:  "
            << query.lastError();
    }

    return success;
}

bool DbManager::ProfessorExist(int username)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT username FROM professors WHERE username = (:username)");
    query.bindValue(":username", username);

    if (query.exec())
    {
        if (query.next())
        {
            return true;
        }
    }
    return false;
}

std::vector<Professor*> DbManager::allProfessors(void)
{
    std::vector<Professor*> professors;
    QSqlQuery query(m_db);
    query.prepare("SELECT username, password, firstname, lastname, departmentcode, groupcode, object_type, is_supervisor, degree FROM professors");

    while (query.next())
    {
        int username = query.value(0).toInt();
        QString password = query.value(1).toString();
        QString firstname = query.value(2).toString();
        QString lastname = query.value(3).toString();
        int departmentcode = query.value(4).toInt();
        int groupcode = query.value(5).toInt();
        QString object_type = query.value(6).toString();
        int is_supervisor = query.value(7).toInt();
        int degree = query.value(8).toInt();

        if (object_type == "adjunctprofessor")
        {
            AdjunctProfessor* adjunct = new AdjunctProfessor(username, password.toStdString(), firstname.toStdString(), lastname.toStdString(), departmentcode, groupcode);
            professors.push_back(adjunct);

        }
        else if (object_type == "faculty")
        {
            Faculty* faculty = new Faculty(username, password.toStdString(), firstname.toStdString(), lastname.toStdString(), departmentcode, groupcode, is_supervisor, degree);
            faculty->setDegree(query.value(1).toInt());
            if (query.value(0).toInt())
                faculty->setAsSupervisor(true);
            professors.push_back(faculty);
        }
        else if (object_type == "groupmanager")
        {
            GroupManager* groupmanager = new GroupManager(username, password.toStdString(), firstname.toStdString(), lastname.toStdString(), departmentcode, groupcode, is_supervisor, degree);
            groupmanager->setDegree(query.value(1).toInt());
            if (query.value(0).toInt())
                groupmanager->setAsSupervisor();
            professors.push_back(groupmanager);
        }
        else if (object_type == "departmentacademicassistant")
        {
            /*
               DepartmentAcademicAssistant* departmentacademicassistant = new DepartmentAcademicAssistant(username, password.toStdString(), firstname.toStdString(), lastname.toStdString(), departmentcode, groupcode, is_supervisor, degree);
               departmentacademicassistant->setDegree(query.value(1).toInt());
               if(query.value(0).toInt())
                   departmentacademicassistant->setAsSupervisor();
               professors.push_back(departmentacademicassistant);
           */
        }
        else if (object_type == "departmenthead")
        {
            DepartmentHead* departmenthead = new DepartmentHead(username, password.toStdString(), firstname.toStdString(), lastname.toStdString(), departmentcode, groupcode, is_supervisor, degree);
            departmenthead->setDegree(query.value(1).toInt());
            if (query.value(0).toInt())
                departmenthead->setAsSupervisor();
            professors.push_back(departmenthead);
        }
    }
    return professors;
}

Student* DbManager::getStudent(int username)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM students WHERE username = :username ");
    query.bindValue(":username", username);
    if (!query.exec())
    {
        qWarning() << __FUNCTION__ << ":" << __LINE__ << "Failed to fetch students";
        qWarning() << __FUNCTION__ << ":" << __LINE__ << m_db.databaseName();
    }
    if (query.next())
    {
        int username = username;
        QString password = query.value(2).toString();
        QString firstname = query.value(3).toString();
        QString lastname = query.value(4).toString();
        int departmentcode = query.value(5).toInt();
        int groupcode = query.value(6).toInt();
        int type = query.value(7).toInt();
        QString field = query.value(8).toString();
        Student* StudentTemp = new Student(username, password.toStdString(), firstname.toStdString(), lastname.toStdString(), departmentcode, type, field.toStdString(), groupcode);
        return StudentTemp;

    }
}

bool DbManager::addStudent(int username, const QString& password, const QString& firstname, const QString& lastname, const int& departmentcode, const int& groupcode, const int& type, const QString& field)
{
    bool success = false;
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO students (username, password, firstname, lastname, departmentcode, groupcode, type, field) VALUES (:username,:password,:firstname,:lastname,:departmentcode,:groupcode,:type,:field)");
    query.bindValue(":username", username);
    query.bindValue(":password", QString(QCryptographicHash::hash((password.toUtf8()), QCryptographicHash::Md5).toHex()));
    query.bindValue(":firstname", firstname);
    query.bindValue(":lastname", lastname);
    query.bindValue(":departmentcode", departmentcode);
    query.bindValue(":groupcode", groupcode);
    query.bindValue(":type", type);
    query.bindValue(":field", field);
    if (query.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "addProfessor error:  "
            << query.lastError();
    }

    return success;
}

bool DbManager::StudentExist(int username)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT username FROM students WHERE username = (:username)");
    query.bindValue(":username", username);

    if (query.exec())
    {
        if (query.next())
        {
            return true;
        }
    }
    return false;
}

std::vector<Student*> DbManager::allStudents(void)
{
    std::vector<Student*> students;
    QSqlQuery query(m_db);
    query.prepare("SELECT username, password, firstname,lastname, departmentcode, groupcode, type, field FROM students");

    while (query.next())
    {
        int username = query.value(1).toInt();
        QString password = query.value(2).toString();
        QString firstname = query.value(3).toString();
        QString lastname = query.value(4).toString();
        int departmentcode = query.value(5).toInt();
        int groupcode = query.value(6).toInt();
        int type = query.value(7).toInt();
        QString field = query.value(8).toString();

        Student* stu = new Student(username, password.toStdString(), firstname.toStdString(), lastname.toStdString(), departmentcode, type, field.toStdString(), groupcode);
        students.push_back(stu);
    }
    return students;
}
