#ifndef TIMEDATE_H
#define TIMEDATE_H

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
	int getYear() const;
	int getMonth() const;
	int getDay() const;
	int getHour() const;
	int getMinute() const;
};

class Course_Time {
	std::vector<std::string> wday;
	int hhi, mmi;
	int hho, mmo;
public:
	Course_Time();
	Course_Time(std::vector<std::string> _wday, int _hhi, int _mmi, int _hho, int _mmo);
	void setDay(std::vector<std::string> _wday);
	std::vector<std::string> getDay() const;
	void setTime(int _hhi, int _mmi, int _hho, int _mmo);
	int gethhi() const;
	int getmmi() const;
	int gethho() const;
	int getmmo() const;
};

#endif // TIMEDATE_H
