#pragma once
#include <string>

class User {
protected:
	std::string username;
	std::string password;
	std::string firstName;
	std::string lastName;
public:
	void setPassword(std::string _password);
};