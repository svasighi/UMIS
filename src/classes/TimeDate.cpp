#include "TimeDate.h"

Time::Time() {

}

Time::Time(int _year, int _month, int _day, int _hour, int _minute)
	: year(_year), month(_month), day(_day), hour(_hour), minute(_minute)
{

}

void Time::setDate(int _year, int _month, int _day) {
	year = _year;
	month = _month;
	day = _day;
}

void Time::setTime(int _hour, int _minute) {
	hour = _hour;
	minute = _minute;
}

int Time::getYear() const {
	return year;
}

int Time::getMonth() const {
	return month;
}

int Time::getDay() const {
	return day;
}

int Time::getHour() const {
	return hour;
}

int Time::getMinute() const {
	return minute;
}




Course_Time::Course_Time() {

}

Course_Time::Course_Time(std::vector<std::string> _wday, int _hhi, int _mmi, int _hho, int _mmo)
	: wday(_wday), hhi(_hhi), mmi(_mmi), hho(_hho), mmo(_mmo)
{

}

void Course_Time::setDay(std::vector<std::string> _wday) {
	wday = _wday;
}

std::vector<std::string> Course_Time::getDay() const {
	return wday;
}

void Course_Time::setTime(int _hhi, int _mmi, int _hho, int _mmo) {
	hhi = _hhi;
	mmi = _mmi;
	hho = _hho;
	mmo = _mmo;
}

int Course_Time::gethhi() const {
	return hhi;
}

int Course_Time::getmmi() const {
	return mmi;
}

int Course_Time::gethho() const {
	return hho;
}

int Course_Time::getmmo() const {
	return mmo;
}
