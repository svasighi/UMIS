#pragma once
#include <string>
#include <vector>

class Time {
	int year, month, day;
	int hour, minute, second;
public:
	Time();
	Time(int _year, int _month, int _day, int _hour, int _minute, int _second);
	void setDate(int _year, int _month, int _day);
	void setTime(int _hour, int _minute, int _second);
	void getDate(int& _year, int& _month, int& _day);
	void getTime(int& _hour, int& _minute, int& _second);
};

class Course_Time {
	std::vector<std::string> wday;
	int hh1, mm1;
	int hh2, mm2;
public:
	Course_Time();
	Course_Time(std::vector<std::string> _wday, int _hh1, int _mm1, int _hh2, int _mm2);
	void setDay(std::vector<std::string> _wday);
	void setTime(int _hh1, int _mm1, int _hh2, int _mm2);
	std::vector<std::string> getDay();
	void getTime(int& _hh1, int& _mm1, int& _hh2, int& _mm2);
};