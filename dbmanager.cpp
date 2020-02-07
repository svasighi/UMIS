#include "dbmanager.h"

DbManager::DbManager(const QString& path)
{
   m_db = QSqlDatabase::addDatabase("QSQLITE");
   m_db.setDatabaseName(path);

   if (!m_db.open())
   {
      qDebug() << "Error: connection with database fail";
   }
   else
   {
      qDebug() << "Database: connection ok";
   }
}

bool DbManager::addUser(const QString& name)
{
   bool success = false;
   QSqlQuery query;
   query.prepare("INSERT INTO people (name) VALUES (:name)");
   query.bindValue(":name", name);
   if(query.exec())
   {
       success = true;
   }
   else
   {
        qDebug() << "addPerson error:  "
                 << query.lastError();
   }

   return success;
}
bool DbManager::UserExist(int username){
    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE username = (:username)");
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
bool DbManager::deleteUser(int username){
    if (UserExist(username))
    {
       QSqlQuery query;
       query.prepare("DELETE FROM users WHERE username = (:username)");
       query.bindValue(":username", username);
       bool success = query.exec();

       if(!success)
       {
           qDebug() << "removePerson error: "
                    << query.lastError();
           return false;
       }
       return true;
    }
}
/*
std::pair<QString, std::unique_ptr<User>> DbManager::getUser(int username){
    UserFactory uf;

    QSqlQuery query;
    query.prepare("SELECT username , password, firstname, lastname, departmentcode, groupcode , type FROM users WHERE username = (:username)");
    query.bindValue(":username", username);

    if (query.next()) {
        int username = query.value(0).toInt();
        QString password = query.value(1).toString();
        QString firstname = query.value(2).toString();
        QString lastname = query.value(3).toString();
        int departmentcode = query.value(4).toInt();
        int groupcode = query.value(5).toInt();
        QString type = query.value(6).toString();

        std::unique_ptr<User> tempuser = uf.create(type.toLocal8Bit().constData());

        tempuser->setUserName(username);
        tempuser->setPassword(lastname.toLocal8Bit().constData());
        tempuser->setFirstName(password.toLocal8Bit().constData());
        tempuser->setLastName(lastname.toLocal8Bit().constData());
        tempuser->setDepartmentCode(departmentcode);
        tempuser->setGroupCode(groupcode);
        std::pair<QString, std::unique_ptr<User>> spair;
        spair = std::make_pair(type, tempuser);
        return spair;
    }
}
*/
// professor d0b63845e6aa07489a797146420b8b15

bool DbManager::addProfessor(const QString& name){
    bool success = false;
    QSqlQuery query;
    query.prepare("INSERT INTO people (name) VALUES (:name)");
    query.bindValue(":name", name);
    if(query.exec())
    {
        success = true;
    }
    else
    {
         qDebug() << "addPerson error:  "
                  << query.lastError();
    }

    return success;
}
bool DbManager::ProfessorExist(int user_id){
    QSqlQuery query;
    query.prepare("SELECT user_id FROM Faculties WHERE user_id = (:user_id)");
    query.bindValue(":user_id", user_id);

    if (query.exec())
    {
       if (query.next())
       {
        return true;
       }
    }
    return false;
}
/*
bool DbManager::deleteProfessor(const int user_id){
    if (UserExist(user_id))
    {
       QSqlQuery query;
       query.prepare("DELETE FROM Faculties WHERE user_id = (:user_id)");
       query.bindValue(":user_id", user_id);
       bool success = query.exec();

       if(!success)
       {
           qDebug() << "removePerson error: "
                    << query.lastError();
           return false;
       }
       return true;
    }
}

std::vector<std::unique_ptr<Professor>> DbManager::allProfessors(void){
    std::vector<std::unique_ptr<Professor>> professors;
    QSqlQuery query;
    query.prepare("SELECT is_supervisor , degree , user_id FROM Faculties");

    while (query.next()) {
        if(UserExist(query.value(2).toInt()))
        {
            std::pair<QString, std::unique_ptr<User>> temp_user = getUser(query.value(2).toInt());
            if(temp_user.first == "adjunctprofessor")
            {
                std::unique_ptr<Professor> adjunct(new AdjunctProfessor(temp_user.second->getUserName() ,temp_user.second->getPassword() ,temp_user.second->getFirstName() ,temp_user.second->getLastName() , temp_user.second->getDepartmentCode() ));
                professors.push_back(adjunct);

            }
            else if(temp_user.first == "faculty")
            {
                Faculty* faculty = new Faculty(temp_user.second->getUserName() ,temp_user.second->getPassword() ,temp_user.second->getFirstName() ,temp_user.second->getLastName() , temp_user.second->getDepartmentCode() );
                faculty->setDegree(query.value(1).toInt());
                if(query.value(0).toInt())
                    faculty->setAsSupervisor();
                std::unique_ptr<Professor> ft(faculty);
                professors.push_back(ft);

            }

        }
    }
    query.prepare("SELECT is_supervisor , degree , user_id FROM AdjunctProfessors");
    while (query.next()) {
        if(UserExist(query.value(2).toInt()))
        {
            std::pair temp_user = getUser(query.value(2).toInt());
            if(temp_user.first == "adjunctprofessor")
            {
                std::unique_ptr<Professor> adjunct(new AdjunctProfessor(temp_user.second->getUserName() ,temp_user.second->getPassword() ,temp_user.second->getFirstName() ,temp_user.second->getLastName() , temp_user.second->getDepartmentCode() ));
                professors.push_back(adjunct);

            }
            else if(temp_user.first == "faculty")
            {
                Faculty* faculty = new Faculty(temp_user.second->getUserName() ,temp_user.second->getPassword() ,temp_user.second->getFirstName() ,temp_user.second->getLastName() , temp_user.second->getDepartmentCode() );
                faculty->setDegree(query.value(1).toInt());
                if(query.value(0).toInt())
                    faculty->setAsSupervisor();
                std::unique_ptr<Professor> ft(faculty);
                professors.push_back(ft);

            }

        }
    }
    return professors;
}

std::pair<QString, std::unique_ptr<User>> DbManager::getProfessor(int user_id){
    UserFactory uf;

    QSqlQuery query;
    query.prepare("SELECT is_supervisor , degree , user_id FROM faculties");
    query.bindValue(":username", user_id);

    if (query.next()) {
        int username = query.value(0).toInt();
        QString password = query.value(1).toString();
        QString firstname = query.value(2).toString();
        QString lastname = query.value(3).toString();
        int departmentcode = query.value(4).toInt();
        int groupcode = query.value(5).toInt();
        QString type = query.value(6).toString();

        std::unique_ptr<User> tempuser = uf.create(type.toLocal8Bit().constData());

        tempuser->setUserName(username);
        tempuser->setPassword(lastname.toLocal8Bit().constData());
        tempuser->setFirstName(password.toLocal8Bit().constData());
        tempuser->setLastName(lastname.toLocal8Bit().constData());
        tempuser->setDepartmentCode(departmentcode);
        tempuser->setGroupCode(groupcode);
        std::pair <QString,std::unique_ptr<User>> spair;
        spair = std::make_pair( type.toLocal8Bit().constData(), tempuser);
        return spair;
    }
}
*/
