#ifndef Time_H
#define Time_H

#include <string>
#include <vector>

class Time {
	int year, month, day;
	int hour, minute;
public:
	Time();
	Time(int _year, int _month, int _day, int _hour, int _minute);
	void setDate(int _year, int _month, int _day);
	void setTime(int _hour, int _minute);
	int getYear();
	int getMonth();
	int getDay();
	int getHour();
	int getMinute();
};

class Course_Time {
	std::vector<std::string> wday;
	int hhi, mmi;
	int hho, mmo;
public:
	Course_Time();
	Course_Time(std::vector<std::string> _wday, int _hhi, int _mmi, int _hho, int _mmo);
	void setDay(std::vector<std::string> _wday);
	std::vector<std::string> getDay();
	void setTime(int _hhi, int _mmi, int _hho, int _mmo);
	int gethhi();
	int getmmi();
	int gethho();
	int getmmo();
};
#endif // Time_H