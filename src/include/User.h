#ifndef USER_H
#define USER_H

#include <string>

class User {
protected:
    int username;
    std::string password;
    std::string firstname;
    std::string lastname;
    int departmentcode;
public:
    User();
    void setUserName(int _username);
    int getUserName(void) const;
    void setPassword(std::string _password);
     std::string getPassword(void);
    void setFirstName(std::string _firstname);
    std::string getFirstName(void) const;
    void setLastName(std::string _lastname);
    std::string getLastName(void) const;
    void setDepartmentCode(int);
    int getDepartmentCode(void) const;
    void checkPassword(void);
    virtual void changePassword(std::string current_pass, std::string new_pass); //forward definition
};

#endif // USER_H
