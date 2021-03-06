#include "User.h"

User::User()
	: username(0), departmentcode(0), groupcode(0) {}

User::User(int _username, std::string _password, std::string _firstname, std::string _lastname, short _departmentcode, short _groupcode)
    : username(_username), password(_password), firstname(_firstname), lastname(_lastname), departmentcode(_departmentcode), groupcode(_groupcode) {}

void User::setUserName(int _username) {
	username = _username;
}

int User::getUserName(void) const {
	return username;
}

void User::setPassword(std::string _password) {
    password = _password;
}

std::string User::getPassword(void) const {
	return password;
}

bool User::checkPassword(std::string _password) const {
    if (_password == getPassword()) {
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

void User::setDepartmentCode(short _departmentcode) {
	departmentcode = _departmentcode;
}

short User::getDepartmentCode(void) const {
	return departmentcode;
}

void User::setGroupCode(short _groupcode) {
	groupcode = _groupcode;
}

short User::getGroupCode(void) const {
	return groupcode;
}
