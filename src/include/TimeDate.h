#ifndef TIMEDATE_H
#define TIMEDATE_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

class Date {
protected:
	int year, month, day;
public:
	Date(int _year = 1300, int _month = 1, int _day = 1);
	void setDate(int _year, int _month, int _day);
	std::string getDate(int mode) const;
	int getYear() const;
	int getMonth() const;
	int getDay() const;
	bool operator==(const Date&) const;
	bool operator>(const Date&) const;
	bool operator<(const Date&) const;
	bool operator!=(const Date&) const;
	bool operator>=(const Date&) const;
	bool operator<=(const Date&) const;
private:
	static std::vector<std::string> monthName;
};

class Time {
protected:
	int hour, minute, second;
public:
	Time(int _hour = 0, int _minute = 0, int _second = 0);
	void setTime(int _hour, int _minute, int _second);
	std::string getTime(int mode) const;
	void setHour(int _hour);
	int getHour() const;
	void setMinute(int _minute);
	int getMinute() const;
	void setSecond(int _second);
	int getSecond() const;
	bool operator==(const Time&) const;
	bool operator>(const Time&) const;
	bool operator<(const Time&) const;
	bool operator!=(const Time&) const;
	bool operator>=(const Time&) const;
	bool operator<=(const Time&) const;
};

class TimeDate {
protected:
	Date date;
	Time time;
public:
	TimeDate();
	TimeDate(int _year, int _month, int _day, int _hour, int _minute, int _second);
	TimeDate(const Date& _date, const Time& _time);
	void setDate(const Date& _date);
	Date getDate();
	void setTime(const Time& _time);
	Time getTime() const;
	bool operator==(const TimeDate&) const;
	bool operator>(const TimeDate&) const;
	bool operator<(const TimeDate&) const;
	bool operator!=(const TimeDate&) const;
	bool operator>=(const TimeDate&) const;
	bool operator<=(const TimeDate&) const;
};

class TimePeriod {
	Time start;
	Time finish;
public:
	TimePeriod();
	TimePeriod(const Time& _start, const Time& _finish);
	void setPeriod(const Time& _start, const Time& _finish);
	Time getStart() const;
	Time getFinish() const;
	bool haveOverlapWith(const TimePeriod&) const;
	bool operator==(const TimePeriod&) const;
};

class CourseTime {
protected:
	std::multimap<char, TimePeriod> times;
public:
	CourseTime();
	CourseTime(const std::multimap<char, TimePeriod>& _times);
	CourseTime(const std::set<char>& days, const Time& start, const Time& finish);
	void setTimes(const std::multimap<char, TimePeriod>& _times);
	std::multimap<char, TimePeriod> getTimes() const;
	void addTime(char day, const TimePeriod& time);
	void addTime(char day, const Time& start, const Time& finish);
	void removeTime(char day, const TimePeriod& time);
	void removeDay(char day);
	bool haveOverlapWith(const CourseTime&) const;
private:
	static std::vector<std::string> weekdayName;
};

class ExamTime {
protected:
	Date date;
	TimePeriod time;
public:
	ExamTime();
	ExamTime(const Date& _date, const TimePeriod& _time);
	ExamTime(const Date& _date, const Time& _start, const Time& _finish);
	void setDate(const Date& _date);
	Date getDate() const;
	void setTime(const TimePeriod& _time);
	void setTime(const Time& _start, const Time& _finish);
	TimePeriod getTime() const;
	bool haveOverlapWith(const ExamTime&) const;
};

#endif // TIMEDATE_H
