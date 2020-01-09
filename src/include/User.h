#ifndef USER_H
#define USER_H

#include <string>

class User {
protected:
    int username;
    std::string password;
    std::string firstname;
    std::string lastname;
public:
    User();
    void setUserName(int _username);
    int getUserName() const;
    void setPassword(std::string _password);
     std::string getPassword();
    void setFirstName(std::string _firstname);
    std::string getFirstName() const;
    void setLastName(std::string _lastname);
    std::string getLastName() const;
    void checkPassword();
    virtual void changePassword(std::string current_pass, std::string new_pass); //forward definition
};

#endif // USER_H
