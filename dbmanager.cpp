#include "dbmanager.h"
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <math.h>
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
bool DbManager::addCourse(const int& departmentcode, const int& groupcode,const int& coursecode, const int& credit, const QString& name, const int& type)
{
    bool success = false;
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO courses (departmentcode, groupcode, coursecode, credit, name, type) VALUES (:departmentcode,:groupcode,:coursecode,:credit,:name,:type)");
    query.bindValue(":departmentcode", departmentcode);
    query.bindValue(":groupcode", groupcode);
    query.bindValue(":coursecode", coursecode);
    query.bindValue(":credit", credit);
    query.bindValue(":name", name);
    query.bindValue(":type", type);
    if (query.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "addCourse error:  "
            << query.lastError();
    }

    return success;
}
bool DbManager::courseExistByCode(int departmentcode,int groupcode ,int coursecode){
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM courses WHERE departmentcode = :departmentcode AND groupcode = :groupcode AND coursecode = :coursecode");
    query.bindValue(":departmentcode", departmentcode);
    query.bindValue(":groupcode", groupcode);
    query.bindValue(":coursecode", coursecode);

    if (query.exec())
    {
        if (query.next())
        {
            return true;
        }
    }
    return false;
}
bool DbManager::deleteCourseByCode(int departmentcode,int groupcode ,int coursecode){
    if (courseExistByCode(departmentcode ,groupcode ,coursecode))
    {
        QSqlQuery query(m_db);
        query.prepare("DELETE FROM courses WHERE departmentcode = :departmentcode AND groupcode = :groupcode AND coursecode = :coursecode");
        query.bindValue(":departmentcode", departmentcode);
        query.bindValue(":groupcode", groupcode);
        query.bindValue(":coursecode", coursecode);
        bool success = query.exec();

        if (!success)
        {
            qDebug() << "removeCourse error: "
                << query.lastError();
            return false;
        }
        return true;
    }
}
Course* DbManager::getCourseByCode(int departmentcode,int groupcode ,int coursecode){
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM courses WHERE departmentcode = :departmentcode AND groupcode = :groupcode AND coursecode = :coursecode");
    query.bindValue(":departmentcode", departmentcode);
    query.bindValue(":groupcode", groupcode);
    query.bindValue(":coursecode", coursecode);

    if (!query.exec())
    {
        qWarning() << __FUNCTION__ << ":" << __LINE__ << "Failed to fetch course";
        qWarning() << __FUNCTION__ << ":" << __LINE__ << m_db.databaseName();
    }
    if (query.next())
    {
        int departmentcode = query.value(1).toInt();
        int groupcode = query.value(2).toInt();
        int coursecode = query.value(3).toInt();
        int credit = query.value(4).toInt();
        QString name = query.value(5).toString();
        int type = query.value(6).toInt();

        Course* CourseTemp = new Course(departmentcode, groupcode, coursecode, credit, name.toStdString(), type);
        return CourseTemp;

    }
}
std::vector<Course*> DbManager::allCourse(void){
    std::vector<Course*> courses;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM courses");

    while (query.next())
    {
        int departmentcode = query.value(1).toInt();
        int groupcode = query.value(2).toInt();
        int coursecode = query.value(3).toInt();
        int credit = query.value(4).toInt();
        QString name = query.value(5).toString();
        int type = query.value(6).toInt();

        Course* CourseTemp = new Course(departmentcode, groupcode, coursecode, credit, name.toStdString(), type);
        courses.push_back(CourseTemp);
    }
    return courses;
}
std::vector<Course*> DbManager::getCourseByDepartment(int departmentcode){
    std::vector<Course*> courses;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM courses WHERE departmentcode = :departmentcode");
    query.bindValue(":departmentcode", departmentcode);
    while (query.next())
    {
        int departmentcode = query.value(1).toInt();
        int groupcode = query.value(2).toInt();
        int coursecode = query.value(3).toInt();
        int credit = query.value(4).toInt();
        QString name = query.value(5).toString();
        int type = query.value(6).toInt();

        Course* CourseTemp = new Course(departmentcode, groupcode, coursecode, credit, name.toStdString(), type);
        courses.push_back(CourseTemp);
    }
    return courses;
}
std::vector<Course*> DbManager::getCourseByGroup(int departmentcode , int groupcode){

    std::vector<Course*> courses;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM courses WHERE departmentcode = :departmentcode AND groupcode = :groupcode ");
    query.bindValue(":departmentcode", departmentcode);
    query.bindValue(":groupcode", groupcode);

    while (query.next())
    {
        int departmentcode = query.value(1).toInt();
        int groupcode = query.value(2).toInt();
        int coursecode = query.value(3).toInt();
        int credit = query.value(4).toInt();
        QString name = query.value(5).toString();
        int type = query.value(6).toInt();

        Course* CourseTemp = new Course(departmentcode, groupcode, coursecode, credit, name.toStdString(), type);
        courses.push_back(CourseTemp);
    }
    return courses;
}

bool DbManager::addPresentedCourse(const int& course_id, const int& course_professor_id,const int& capacity, const int& enrolled_number, const int& waiting_number, const int& group_number, const int& term_number, std::vector<Course*> corequisit, std::vector<Course*> prerequisit)
{
    QString prerequisit_string;
    for(int i = 0 ; i < prerequisit.size() ; i++)
    {
        prerequisit_string += prerequisit[i]->getCourseID() + ";";
    }
    QString corequisit_string;
    for(int i = 0 ; i < corequisit.size() ; i++)
    {
        corequisit_string += corequisit[i]->getCourseID() + ";";
    }

    bool success = false;
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO presented_courses (course_id, course_professor_id, capacity, enrolled_number, waiting_number, group_number , term_number , corequisit , preriqisit) VALUES (:course_id,:course_professor_id,:capacity,:enrolled_number,:waiting_number,:group_number ,:term_number ,:corequisit ,:preriqisit)");
    query.bindValue(":course_id", course_id);
    query.bindValue(":course_professor_id", course_professor_id);
    query.bindValue(":capacity", capacity);
    query.bindValue(":enrolled_number", enrolled_number);
    query.bindValue(":waiting_number", group_number);
    query.bindValue(":term_number", term_number);
    query.bindValue(":corequisit", corequisit_string.toUtf8());
    query.bindValue(":prerequisit", prerequisit_string.toUtf8());
    if (query.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "addPresentedCourse error:  "
            << query.lastError();
    }

    return success;
}

bool DbManager::deletePresentedCourseByCode(const int& course_id ,const int& course_professor_id,const int& term_number)
{
    if (presentedCourseExistbyCode(course_id ,course_professor_id ,term_number))
    {
        QSqlQuery query(m_db);
        query.prepare("DELETE FROM presented_courses WHERE course_id = :course_id AND course_professor_id = :course_professor_id AND term_number = :term_number");
        query.bindValue(":course_id", course_id);
        query.bindValue(":course_professor_id", course_professor_id);
        query.bindValue(":term_number", term_number);
        bool success = query.exec();

        if (!success)
        {
            qDebug() << "removePresentedCourse error: "
                << query.lastError();
            return false;
        }
        return true;
    }
}
bool DbManager::presentedCourseExistbyCode(const int& course_id ,const int& course_professor_id,const int& term_number)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM presented_courses WHERE course_id = :course_id AND course_professor_id = :course_professor_id AND term_number = :term_number");
    query.bindValue(":course_id", course_id);
    query.bindValue(":course_professor_id", course_professor_id);
    query.bindValue(":term_number", term_number);

    if (query.exec())
    {
        if (query.next())
        {
            return true;
        }
    }
    return false;
}
PresentedCourse* DbManager::getPresentedCourseByCode(const int& course_id ,const int& course_professor_id ,const int& term_number)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM presented_courses WHERE course_id = :course_id AND course_professor_id = :course_professor_id AND term_number = :term_number");
    query.bindValue(":course_id", course_id);
    query.bindValue(":course_professor_id", course_professor_id);
    query.bindValue(":term_number", term_number);

    if (!query.exec())
    {
        qWarning() << __FUNCTION__ << ":" << __LINE__ << "Failed to fetch course";
        qWarning() << __FUNCTION__ << ":" << __LINE__ << m_db.databaseName();
    }
    if (query.next())
    {
        int course_id = query.value(1).toInt();
        int course_professor_id = query.value(2).toInt();
        int capacity = query.value(3).toInt();
        int enrolled_number = query.value(4).toInt();
        int waiting_number = query.value(4).toInt();
        int group_number = query.value(4).toInt();
        int term_number = query.value(6).toInt();
        int length = QString(course_id).length();
        Course* corurse_temp = getCourseByCode( course_id / (int) pow(10 , length - 2) , course_id % (int) pow(10 , length - 2) / (int) pow(10 , length - 2),course_id % (int) pow(10 , length - 2) % (int) pow(10 , length - 2) );
        Professor* professor_temp = getProfessor(course_professor_id);
        PresentedCourse* PresentedCourseTemp = new PresentedCourse(corurse_temp ,term_number ,group_number , professor_temp ,capacity);
        PresentedCourseTemp->setEnrolledNumber(enrolled_number);
        PresentedCourseTemp->setWaitingNumber(waiting_number);

        QStringList corequisit_list = query.value(5).toString().split(';');
        QStringList prerequisit_list = query.value(5).toString().split(';');
        for(int i =0 ; i < corequisit_list.count();i++)
        {
           int length = corequisit_list.at(i).length();

            Course* coCoursTemp = getCourseByCode( corequisit_list.at(i).toInt() / (int) pow(10 , length - 2) , corequisit_list.at(i).toInt() % (int) pow(10 , length - 2) / (int) pow(10 , length - 2),corequisit_list.at(i).toInt() % (int) pow(10 , length - 2) % (int) pow(10 , length - 2) );
            PresentedCourseTemp->addCorequisite(coCoursTemp);
        }
        for(int i =0 ; i < prerequisit_list.count();i++)
        {
           int length = prerequisit_list.at(i).length();

            Course* preCoursTemp = getCourseByCode( prerequisit_list.at(i).toInt() / (int) pow(10 , length - 2) , prerequisit_list.at(i).toInt() % (int) pow(10 , length - 2) / (int) pow(10 , length - 2),prerequisit_list.at(i).toInt() % (int) pow(10 , length - 2) % (int) pow(10 , length - 2) );
            PresentedCourseTemp->addPrerequisite(preCoursTemp);
        }
        return PresentedCourseTemp;

    }
}
std::vector<PresentedCourse*> DbManager::allPresentedCourse(void){

    std::vector<PresentedCourse*> presentedcourses;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM presented_courses");

    if (!query.exec())
    {
        qWarning() << __FUNCTION__ << ":" << __LINE__ << "Failed to fetch course";
        qWarning() << __FUNCTION__ << ":" << __LINE__ << m_db.databaseName();
    }
    if (query.next())
    {
        int course_id = query.value(1).toInt();
        int course_professor_id = query.value(2).toInt();
        int capacity = query.value(3).toInt();
        int enrolled_number = query.value(4).toInt();
        int waiting_number = query.value(4).toInt();
        int group_number = query.value(4).toInt();
        int term_number = query.value(6).toInt();
        int length = QString(course_id).length();
        Course* corurse_temp = getCourseByCode( course_id / (int) pow(10 , length - 2) , course_id % (int) pow(10 , length - 2) / (int) pow(10 , length - 2),course_id % (int) pow(10 , length - 2) % (int) pow(10 , length - 2) );
        Professor* professor_temp = getProfessor(course_professor_id);
        PresentedCourse* PresentedCourseTemp = new PresentedCourse(corurse_temp ,term_number ,group_number , professor_temp ,capacity);
        PresentedCourseTemp->setEnrolledNumber(enrolled_number);
        PresentedCourseTemp->setWaitingNumber(waiting_number);
        presentedcourses.push_back(PresentedCourseTemp);
        QStringList corequisit_list = query.value(5).toString().split(';');
        QStringList prerequisit_list = query.value(5).toString().split(';');
        for(int i =0 ; i < corequisit_list.count();i++)
        {
           int length = corequisit_list.at(i).length();

            Course* coCoursTemp = getCourseByCode( corequisit_list.at(i).toInt() / (int) pow(10 , length - 2) , corequisit_list.at(i).toInt() % (int) pow(10 , length - 2) / (int) pow(10 , length - 2),corequisit_list.at(i).toInt() % (int) pow(10 , length - 2) % (int) pow(10 , length - 2) );
            PresentedCourseTemp->addCorequisite(coCoursTemp);
        }
        for(int i =0 ; i < prerequisit_list.count();i++)
        {
           int length = prerequisit_list.at(i).length();

            Course* preCoursTemp = getCourseByCode( prerequisit_list.at(i).toInt() / (int) pow(10 , length - 2) , prerequisit_list.at(i).toInt() % (int) pow(10 , length - 2) / (int) pow(10 , length - 2),prerequisit_list.at(i).toInt() % (int) pow(10 , length - 2) % (int) pow(10 , length - 2) );
            PresentedCourseTemp->addPrerequisite(preCoursTemp);
        }

    }
    return presentedcourses;

}
std::vector<PresentedCourse*> DbManager::getPresentedCourseByCourseId(const int& _course_id ,const int& _term_number){
    std::vector<PresentedCourse*> presentedcourses;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM presented_courses WHERE course_id = :course_id AND term_number = :term_number");
    query.bindValue(":course_id", _course_id);
    query.bindValue(":term_number", _term_number);
    if (!query.exec())
    {
        qWarning() << __FUNCTION__ << ":" << __LINE__ << "Failed to fetch course";
        qWarning() << __FUNCTION__ << ":" << __LINE__ << m_db.databaseName();
    }
    if (query.next())
    {
        int course_id = query.value(1).toInt();
        int course_professor_id = query.value(2).toInt();
        int capacity = query.value(3).toInt();
        int enrolled_number = query.value(4).toInt();
        int waiting_number = query.value(4).toInt();
        int group_number = query.value(4).toInt();
        int term_number = query.value(6).toInt();
        int length = QString(course_id).length();
        Course* corurse_temp = getCourseByCode( course_id / (int) pow(10 , length - 2) , course_id % (int) pow(10 , length - 2) / (int) pow(10 , length - 2),course_id % (int) pow(10 , length - 2) % (int) pow(10 , length - 2) );
        Professor* professor_temp = getProfessor(course_professor_id);
        PresentedCourse* PresentedCourseTemp = new PresentedCourse(corurse_temp ,term_number ,group_number , professor_temp ,capacity);
        PresentedCourseTemp->setEnrolledNumber(enrolled_number);
        PresentedCourseTemp->setWaitingNumber(waiting_number);
        presentedcourses.push_back(PresentedCourseTemp);
        QStringList corequisit_list = query.value(5).toString().split(';');
        QStringList prerequisit_list = query.value(5).toString().split(';');
        for(int i =0 ; i < corequisit_list.count();i++)
        {
           int length = corequisit_list.at(i).length();

            Course* coCoursTemp = getCourseByCode( corequisit_list.at(i).toInt() / (int) pow(10 , length - 2) , corequisit_list.at(i).toInt() % (int) pow(10 , length - 2) / (int) pow(10 , length - 2),corequisit_list.at(i).toInt() % (int) pow(10 , length - 2) % (int) pow(10 , length - 2) );
            PresentedCourseTemp->addCorequisite(coCoursTemp);
        }
        for(int i =0 ; i < prerequisit_list.count();i++)
        {
           int length = prerequisit_list.at(i).length();

            Course* preCoursTemp = getCourseByCode( prerequisit_list.at(i).toInt() / (int) pow(10 , length - 2) , prerequisit_list.at(i).toInt() % (int) pow(10 , length - 2) / (int) pow(10 , length - 2),prerequisit_list.at(i).toInt() % (int) pow(10 , length - 2) % (int) pow(10 , length - 2) );
            PresentedCourseTemp->addPrerequisite(preCoursTemp);
        }

    }
    return presentedcourses;
}
std::vector<PresentedCourse*> DbManager::getPresentedCourseByCourseProfessorId(const int& course_professor_id ,const int& term_number){
    std::vector<PresentedCourse*> presentedcourses;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM presented_courses WHERE course_professor_id = :course_professor_id AND term_number = :term_number");
    query.bindValue(":course_professor_id", course_professor_id);
    query.bindValue(":term_number", term_number);
    if (!query.exec())
    {
        qWarning() << __FUNCTION__ << ":" << __LINE__ << "Failed to fetch course";
        qWarning() << __FUNCTION__ << ":" << __LINE__ << m_db.databaseName();
    }
    if (query.next())
    {
        int course_id = query.value(1).toInt();
        int course_professor_id = query.value(2).toInt();
        int capacity = query.value(3).toInt();
        int enrolled_number = query.value(4).toInt();
        int waiting_number = query.value(4).toInt();
        int group_number = query.value(4).toInt();
        int term_number = query.value(6).toInt();
        int length = QString(course_id).length();
        Course* corurse_temp = getCourseByCode( course_id / (int) pow(10 , length - 2) , course_id % (int) pow(10 , length - 2) / (int) pow(10 , length - 2),course_id % (int) pow(10 , length - 2) % (int) pow(10 , length - 2) );
        Professor* professor_temp = getProfessor(course_professor_id);
        PresentedCourse* PresentedCourseTemp = new PresentedCourse(corurse_temp ,term_number ,group_number , professor_temp ,capacity);
        PresentedCourseTemp->setEnrolledNumber(enrolled_number);
        PresentedCourseTemp->setWaitingNumber(waiting_number);
        presentedcourses.push_back(PresentedCourseTemp);
        QStringList corequisit_list = query.value(5).toString().split(';');
        QStringList prerequisit_list = query.value(5).toString().split(';');
        for(int i =0 ; i < corequisit_list.count();i++)
        {
           int length = corequisit_list.at(i).length();

            Course* coCoursTemp = getCourseByCode( corequisit_list.at(i).toInt() / (int) pow(10 , length - 2) , corequisit_list.at(i).toInt() % (int) pow(10 , length - 2) / (int) pow(10 , length - 2),corequisit_list.at(i).toInt() % (int) pow(10 , length - 2) % (int) pow(10 , length - 2) );
            PresentedCourseTemp->addCorequisite(coCoursTemp);
        }
        for(int i =0 ; i < prerequisit_list.count();i++)
        {
           int length = prerequisit_list.at(i).length();

            Course* preCoursTemp = getCourseByCode( prerequisit_list.at(i).toInt() / (int) pow(10 , length - 2) , prerequisit_list.at(i).toInt() % (int) pow(10 , length - 2) / (int) pow(10 , length - 2),prerequisit_list.at(i).toInt() % (int) pow(10 , length - 2) % (int) pow(10 , length - 2) );
            PresentedCourseTemp->addPrerequisite(preCoursTemp);
        }

    }
    return presentedcourses;
}
