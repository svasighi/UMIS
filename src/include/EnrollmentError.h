#ifndef ENROLLMENTERROR_H
#define ENROLLMENTERROR_H

#include <string>
#include "Course.h"

class EnrollmentError {
protected:
	short errorcode;
public:
	EnrollmentError(short _errorcode);
	short getErrorCode() const;
	virtual std::string what() const = 0;
};

class PassedBefore : public EnrollmentError {
	Presented_Course* source;
public:
	PassedBefore(Presented_Course* _source = nullptr);
	void setSource(Presented_Course* _source);
	Presented_Course* getSource() const;
	std::string what() const;
};

class NotPassedPrerequisite : public EnrollmentError {
protected:
	Presented_Course* source;
	Course* destination;
public:
	NotPassedPrerequisite(Presented_Course* _source = nullptr, Course* _destination = nullptr);
	void setSource(Presented_Course* _source);
	Presented_Course* getSource() const;
	void setDestination(Course* _destination);
	Course* getDestination() const;
	std::string what() const;
};

class NotTakenCorequisite : public EnrollmentError {
protected:
	Presented_Course* source;
	Course* destination;
public:
	NotTakenCorequisite(Presented_Course* _source = nullptr, Course* _destination = nullptr);
	void setSource(Presented_Course* _source);
	Presented_Course* getSource() const;
	void setDestination(Course* _destination);
	Course* getDestination() const;
	std::string what() const;
};

class CourseTimeOverlap : public EnrollmentError {
protected:
	Presented_Course* source;
	Presented_Course* destination;
public:
	CourseTimeOverlap(Presented_Course* _source = nullptr, Presented_Course* _destination = nullptr);
	void setSource(Presented_Course* _source);
	Presented_Course* getSource() const;
	void setDestination(Presented_Course* _destination);
	Presented_Course* getDestination() const;
	std::string what() const;
};

class ExamTimeOverlap : public EnrollmentError {
protected:
	Presented_Course* source;
	Presented_Course* destination;
public:
	ExamTimeOverlap(Presented_Course* _source = nullptr, Presented_Course* _destination = nullptr);
	void setSource(Presented_Course* _source);
	Presented_Course* getSource() const;
	void setDestination(Presented_Course* _destination);
	Presented_Course* getDestination() const;
	std::string what() const;
};

class FullCapacity : public EnrollmentError {
	Presented_Course* source;
public:
	FullCapacity(Presented_Course* _source = nullptr);
	void setSource(Presented_Course* _source);
	Presented_Course* getSource() const;
	std::string what() const;
};

#endif // ENROLLMENTERROE_H
