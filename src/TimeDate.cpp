#include <stdexcept>
#include "TimeDate.h"

std::vector<std::string> Date::monthName = { "Farvardin","Ordibehesht","Khordad","Tir","Mordad","Shahrivar","Mehr","Aban","Azar","Dey","Bahman","Esfand" };

Date::Date(int _year, int _month, int _day) {
	setDate(_year, _month, _day);
}

void Date::setDate(int _year, int _month, int _day) {
	if (_month > 12 || _month < 1)
		throw std::invalid_argument("Month must be 1-12");
	if (_day > 31 || _day < 1)
		throw std::invalid_argument("Day must be 1-31");
	if (_month > 6 && _day == 31)
		throw std::invalid_argument("Day can't be 31 in autumn and winter");
	year = _year;
	month = _month;
	day = _day;
}

std::string Date::getDate(int mode) const {
	std::string temp;
	switch (mode) {
	case 0:
		temp = std::to_string(year) + "/" + std::to_string(month) + "/" + std::to_string(day);
		break;
	case 1:
		temp = std::to_string(year % 100) + "/" + std::to_string(month) + "/" + std::to_string(day);
		break;
	case 2:
		temp = std::to_string(year) + " " + monthName[month - 1] + " " + std::to_string(day);
		break;
	case 3:
		temp = std::to_string(year % 100) + " " + monthName[month - 1] + " " + std::to_string(day);
		break;
	default:
		break;
	}
	return temp;
};

int Date::getYear() const {
	return year;
}

int Date::getMonth() const {
	return month;
}

int Date::getDay() const {
	return day;
}

bool Date::operator==(const Date& right) const {
	if (this->year == right.year && this->month == right.month && this->day == right.day) {
		return true;
	}
	return false;
}

bool Date::operator>(const Date& right) const {
	if (this->year > right.year)
		return true;
	if (this->year < right.year)
		return false;
	if (this->month > right.month)
		return true;
	if (this->month < right.month)
		return false;
	if (this->day > right.day)
		return true;
	return false;
}

bool Date::operator<(const Date& right) const {
	if (this->year < right.year)
		return true;
	if (this->year > right.year)
		return false;
	if (this->month < right.month)
		return true;
	if (this->month > right.month)
		return false;
	if (this->day < right.day)
		return true;
	return false;
}

bool Date::operator!=(const Date& right) const {
	if (this->year == right.year && this->month == right.month && this->day == right.day) {
		return false;
	}
	return true;
}

bool Date::operator>=(const Date& right) const {
	if (this->year > right.year)
		return true;
	if (this->year < right.year)
		return false;
	if (this->month > right.month)
		return true;
	if (this->month < right.month)
		return false;
	if (this->day > right.day)
		return true;
	if (this->day < right.day)
		return false;
	return true;
}

bool Date::operator<=(const Date& right) const {
	if (this->year < right.year)
		return true;
	if (this->year > right.year)
		return false;
	if (this->month < right.month)
		return true;
	if (this->month > right.month)
		return false;
	if (this->day < right.day)
		return true;
	if (this->day > right.day)
		return false;
	return true;
}




Time::Time(int _hour, int _minute, int _second) {
	setTime(_hour, _minute, _second);
}

void Time::setTime(int _hour, int _minute, int _second) {
	if (_hour < 0 || _hour > 23)
		throw std::invalid_argument("Hour must be 0-23");
	if (_minute < 0 || _minute > 59)
		throw std::invalid_argument("Minute must be 0-59");
	if (_second < 0 || _second > 59)
		throw std::invalid_argument("Second must be 0-59");
	hour = _hour;
	minute = _minute;
	second = _second;
}

std::string Time::getTime(int mode) const {
	std::string temp;
	if (mode == 0 || mode == 24) {
		temp = std::to_string(hour) + ":" + std::to_string(minute) + ":" + std::to_string(second);
	}
	else if (mode == 1 || mode == 12) {
		temp = std::to_string(((hour == 0 || hour == 12) ? 12 : hour % 12)) + ":" + std::to_string(minute) + ":" + std::to_string(second) + " " + (hour < 12 ? "AM" : "PM");
	}
	else if (mode == 2) {
		temp = std::to_string(hour) + (minute != 0 ? ":" + std::to_string(minute) : "");
	}
	return temp;
}

void Time::setHour(int _hour) {
	if (_hour < 0 || _hour > 23)
		throw std::invalid_argument("Hour must be 0-23");
	hour = _hour;
}

int Time::getHour() const {
	return hour;
}

void Time::setMinute(int _minute) {
	if (_minute < 0 || _minute > 59)
		throw std::invalid_argument("Minute must be 0-59");
	minute = _minute;
}

int Time::getMinute() const {
	return minute;
}

void Time::setSecond(int _second) {
	if (_second < 0 || _second > 59)
		throw std::invalid_argument("Second must be 0-59");
	second = _second;
}

int Time::getSecond() const {
	return second;
}

bool Time::operator==(const Time& right) const {
	if (this->hour == right.hour && this->minute == right.minute && this->second == right.second) {
		return true;
	}
	return false;
}

bool Time::operator>(const Time& right) const {
	if (this->hour > right.hour)
		return true;
	if (this->hour < right.hour)
		return false;
	if (this->minute > right.minute)
		return true;
	if (this->minute < right.minute)
		return false;
	if (this->second > right.second)
		return true;
	return false;
}

bool Time::operator<(const Time& right) const {
	if (this->hour < right.hour)
		return true;
	if (this->hour > right.hour)
		return false;
	if (this->minute < right.minute)
		return true;
	if (this->minute > right.minute)
		return false;
	if (this->second < right.second)
		return true;
	return false;
}

bool Time::operator!=(const Time& right) const {
	if (this->hour == right.hour && this->minute == right.minute && this->second == right.second) {
		return false;
	}
	return true;
}

bool Time::operator>=(const Time& right) const {
	if (this->hour > right.hour)
		return true;
	if (this->hour < right.hour)
		return false;
	if (this->minute > right.minute)
		return true;
	if (this->minute < right.minute)
		return false;
	if (this->second > right.second)
		return true;
	if (this->second < right.second)
		return false;
	return true;
}

bool Time::operator<=(const Time& right) const {
	if (this->hour < right.hour)
		return true;
	if (this->hour > right.hour)
		return false;
	if (this->minute < right.minute)
		return true;
	if (this->minute > right.minute)
		return false;
	if (this->second < right.second)
		return true;
	if (this->second > right.second)
		return false;
	return true;
}




TimeDate::TimeDate() {}

TimeDate::TimeDate(int _year, int _month, int _day, int _hour, int _minute, int _second)
	: date(Date(_year, _month, _day)), time(Time(_hour, _minute, _second)) {}

TimeDate::TimeDate(const Date& _date, const Time& _time)
	: date(_date), time(_time) {}

void TimeDate::setDate(const Date& _date) {
	date = _date;
}

Date TimeDate::getDate() {
	return date;
}

void TimeDate::setTime(const Time& _time) {
	time = _time;
}

Time TimeDate::getTime() const {
	return time;
}

bool TimeDate::operator==(const TimeDate& right) const {
	if (this->date == right.date && this->time == right.time) {
		return true;
	}
	return false;
}

bool TimeDate::operator>(const TimeDate& right) const {
	if (this->date > right.date)
		return true;
	if (this->date < right.date)
		return false;
	if (this->time > right.time)
		return true;
	return false;
}

bool TimeDate::operator<(const TimeDate& right) const {
	if (this->date < right.date)
		return true;
	if (this->date > right.date)
		return false;
	if (this->time < right.time)
		return true;
	return false;
}

bool TimeDate::operator!=(const TimeDate& right) const {
	if (this->date == right.date && this->time == right.time) {
		return false;
	}
	return true;
}

bool TimeDate::operator>=(const TimeDate& right) const {
	if (this->date > right.date)
		return true;
	if (this->date < right.date)
		return false;
	if (this->time > right.time)
		return true;
	if (this->time < right.time)
		return false;
	return true;
}

bool TimeDate::operator<=(const TimeDate& right) const {
	if (this->date < right.date)
		return true;
	if (this->date > right.date)
		return false;
	if (this->time < right.time)
		return true;
	if (this->time > right.time)
		return false;
	return true;
}




TimePeriod::TimePeriod() {}

TimePeriod::TimePeriod(const Time& _start, const Time& _finish) {
	setPeriod(_start, _finish);
}

void TimePeriod::setPeriod(const Time& _start, const Time& _finish) {
	if (_start > _finish)
		throw std::invalid_argument("start must be less than finish");
	start = _start;
	finish = _finish;
}

Time TimePeriod::getStart() const {
	return start;
}

Time TimePeriod::getFinish() const {
	return finish;
}

bool TimePeriod::haveOverlapWith(const TimePeriod& right) const {
	if (this->start < right.finish && right.start < this->finish) {
		return true;
	}
	return false;
}

bool TimePeriod::operator==(const TimePeriod& right) const {
	if (this->start == right.start && this->finish == right.finish) {
		return true;
	}
	return false;
}




std::vector<std::string> CourseTime::weekdayName = { "Saturday","Sunday","Monday","Tuesday","Wednesday","Thursday","Friday" };

CourseTime::CourseTime() {}

CourseTime::CourseTime(const std::multimap<char, TimePeriod>& _times) {
	setTimes(_times);
}

CourseTime::CourseTime(const std::set<char>& days, const Time& start, const Time& finish) {
	for (const auto& day : days) {
		times.insert(std::make_pair(day, TimePeriod(start, finish)));
	}
}

void CourseTime::setTimes(const std::multimap<char, TimePeriod>& _times) {
	for (auto it1 = _times.begin(); it1 != _times.end(); it1++) {
		for (auto it2 = std::next(it1, 1); it2 != _times.end(); it2++) {
			if (it1->first == it2->first && it1->second.haveOverlapWith(it2->second)) {
				throw std::invalid_argument("your input times have overlap");
			}
		}
	}
	times = _times;
}

std::multimap<char, TimePeriod> CourseTime::getTimes() const {
	return times;
}

void CourseTime::addTime(char day, const TimePeriod& time) {
	for (auto it = times.begin(); it != times.end(); it++) {
		if (day == it->first && time.haveOverlapWith(it->second)) {
			throw std::invalid_argument("your input time has overlap with one of the previous times");
		}
	}
	times.insert(std::make_pair(day, time));
}

void CourseTime::addTime(char day, const Time& start, const Time& finish) {
	addTime(day, TimePeriod(start, finish));
}

void CourseTime::removeTime(char day, const TimePeriod& time) {
	auto iterpair = times.equal_range(day);
	for (auto it = iterpair.first; it != iterpair.second; it++) {
		if (it->second == time) {
			times.erase(it);
			break;
		}
	}
}

void CourseTime::removeDay(char day) {
	if (times.count(day) != 0) {
		times.erase(day);
	}
}

bool CourseTime::haveOverlapWith(const CourseTime& right) const {
	for (const auto& t1 : this->times) {
		for (const auto& t2 : right.times) {
			if (t1.first == t2.first && t1.second.haveOverlapWith(t2.second)) {
				return true;
			}
		}
	}
	return false;
}




ExamTime::ExamTime() {}

ExamTime::ExamTime(const Date& _date, const TimePeriod& _time)
	: date(_date), time(_time) {}

ExamTime::ExamTime(const Date& _date, const Time& _start, const Time& _finish)
	: date(_date), time(TimePeriod(_start, _finish)) {}

void ExamTime::setDate(const Date& _date) {
	date = _date;
}

Date ExamTime::getDate() const {
	return date;
}

void ExamTime::setTime(const TimePeriod& _time) {
	time = _time;
}

void ExamTime::setTime(const Time& _start, const Time& _finish) {
	time = TimePeriod(_start, _finish);
}

TimePeriod ExamTime::getTime() const {
	return time;
}

bool ExamTime::haveOverlapWith(const ExamTime& right) const {
	if (this->date == right.date && this->time.haveOverlapWith(right.time)) {
		return true;
	}
	return false;
}
