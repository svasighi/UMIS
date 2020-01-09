#include "User.h"

User::User() {

}

void User::setUserName(int _username) {
	username = _username;
}

int User::getUserName() const {
	return username;
}

void User::setPassword(std::string _password) {
	password = _password;
}

std::string User::getPassword() {
	return password;
}

void User::setFirstName(std::string _firstname) {
	firstname = _firstname;
}

std::string User::getFirstName() const {
	return firstname;
}

void User::setLastName(std::string _lastname) {
	lastname = _lastname;
}

std::string User::getLastName() const {
	return lastname;
}