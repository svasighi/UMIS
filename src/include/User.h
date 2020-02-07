#ifndef USER_H
#define USER_H

#include <string>

class User {
protected:
	int username;
	std::string password;
	std::string firstname;
	std::string lastname;
	short departmentcode;
	short groupcode;
public:
	User();
	User(int _username, std::string _password, std::string _firstname = "", std::string _lastname = "", short _departmentcode = 0, short _groupcode = 0);
	void setUserName(int _username);
	int getUserName(void) const;
	void setPassword(std::string _password);
	bool checkPassword(std::string _password) const;
	virtual void changePassword(std::string current_pass, std::string new_pass) = 0;
	std::string getPassword(void) const;
	void setFirstName(std::string _firstname);
	std::string getFirstName(void) const;
	void setLastName(std::string _lastname);
	std::string getLastName(void) const;
	void setDepartmentCode(short _departmentcode);
	short getDepartmentCode(void) const;
	void setGroupCode(short _groupcode);
	short getGroupCode(void) const;
};

#endif // USER_H
