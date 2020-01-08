#ifndef USER_H
#define USER_H

#include <string>

// .............................FIELD......................................
class Field { 
    int ID;
    std::string FieldName;
public:
    inline void setID(int FieldID) { ID = FieldID;}
    inline std::string getID(void) const {return FieldName;}
    inline void setFieldName(std::string fieldname) {FieldName = fieldname;}
    inline std::string setFieldName(void) const {return FieldName;}
};
// .............................USER......................................

class User
{
private:
    unsigned int user_name;
    std::string first_name;
    std::string last_name;
    std::string password;
    Field field;
public:
    User(){}; // it won't do anything :)
    ~User(){}; // it won't do anything :)
    void setUserName(const unsigned int _username);
    unsigned int getUserName(void) const {return user_name;}
    void setFirstName(const std::string); //forward definition
    std::string getFirstName(void) const {return first_name;}
    void setLastName(const std::string); //forward definition
    std::string getLastName(void) const {return last_name;}
    void setField(const Field); //forward definition
    Field getField(void) const {return field;}
    void setPassword(const std::string); //forward definition
    void CheckPassword(); //forward definition
    virtual void ChangePassword(); //forward definition
};

#endif // USER_H
