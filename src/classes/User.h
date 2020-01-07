#ifndef USER_H
#define USER_H

#include <string>

// .............................FIELD......................................
class Field { 
    int ID;
    std::string fieldname;
public:
    inline void setID(int _fieldID){ ID = _fieldID;}
    inline std::string getID(void) const {return ID;}
    inline void setFieldName(std::string _fieldname){fieldname = _fieldname;}
    inline std::string getFieldName(void) const {return fieldname;}
};
// .............................USER......................................

class User
{
private:
    unsigned int ID;
    std::string first_name;
    std::string last_name;
    std::string password;
    Field field;
public:
    User(){}; // it won't do anything :)
    ~User(){}; // it won't do anything :)
    void setID(const unsigned);
    inline unsigned int getID(void) const {return ID;}
    void setFirstName(const std::string); //forward definition
    std::string getFirstName(void) const {return first_name;}
    void setLastName(const std::string); //forward definition
    std::string getLastName(void) const {return last_name;}
    void setField(const Field); //forward definition
    Field getField(void) const {return field;};    
    void setPassword(const std::string); //forward definition
    void std::string getPassword(void) const {return password;}
    void CheckPassword(); //forward definition
    virtual void ChangePassword(); //forward definition
};

#endif // USER_H
