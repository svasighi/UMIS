#include "../include/User.h"
#include "../include/md5.h"

User::User()
	: username(0), departmentcode(0) {}

User::User(int _username, std::string _password, std::string _firstname, std::string _lastname, int _departmentcode)
	: username(_username), password(md5(_password)), firstname(_firstname), lastname(_lastname), departmentcode(_departmentcode) {}

void User::setUserName(int _username) {
	username = _username;
}

int User::getUserName(void) const {
	return username;
}

void User::setPassword(std::string _password) {
	password = md5(_password);
}

std::string User::getPassword(void) const {
	return password;
}

bool User::checkPassword(std::string _password) const {
	if (md5(_password) == getPassword()) {
		return true;
	}
	else {
		return false;
	}
} 

void User::setFirstName(std::string _firstname) {
	firstname = _firstname;
}

std::string User::getFirstName(void) const {
	return firstname;
}

void User::setLastName(std::string _lastname) {
	lastname = _lastname;
}

std::string User::getLastName(void) const {
	return lastname;
}

void User::setDepartmentCode(int _departmentcode) {
	departmentcode = _departmentcode;
}

int User::getDepartmentCode(void) const {
	return departmentcode;
}
