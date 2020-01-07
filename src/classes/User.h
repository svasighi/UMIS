#include <iostream>
#include <string>

#ifndef USER_H
#define USER_H

// .............................FIELD......................................
class Field{ 
    int ID;
    std::string FieldName;
public:
    inline void SetID(int FieldID){ ID = FieldID;}
    inline std::String GetID(void) const {FieldName = fieldname;}
    inline void SetFieldName(std::String fieldname){FieldName = fieldname;}
    inline std::String GetFieldName(void) const {FieldName = fieldname;}
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
    void SetID(const unsigned);
    inline unsigned GetID(void) const {return ID;};
    void Setfirst_name(const std::string); //forward definition
    std::string Getfirst_name(void) const {return first_name;};
    void Setlast_name(const std::string); //forward definition
    std::string Getlast_name(void) const {return last_name;};
    void SetField(const Field); //forward definition
    Field GetField(void) const {return field;};    
    virtual void SetPassword(const std::string); //forward definition
    virtual void CheckPassword(); //forward definition
    virtual void ChangePassword(); //forward definition
};

#endif
