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
public:
	static constexpr char passed_before = 0;
	static constexpr char taken_same_course = 1;
	static constexpr char not_passed_prerequisite = 2;
	static constexpr char not_taken_corequisite = 3;
	static constexpr char course_time_overlap = 4;
	static constexpr char exam_time_overlap = 5;
	static constexpr char full_capacity = 6;
};

class PassedBefore : public EnrollmentError {
	Course* source;
public:
	PassedBefore(Course* _source = nullptr);
	void setSource(Course* _source);
	Course* getSource() const;
	std::string what() const;
};

class TakenSameCourse : public EnrollmentError {
	PresentedCourse* source;
	PresentedCourse* destination;
public:
	TakenSameCourse(PresentedCourse* _source = nullptr, PresentedCourse* _destination = nullptr);
	void setSource(PresentedCourse* _source);
	PresentedCourse* getSource() const;
	void setDestination(PresentedCourse* _destination);
	PresentedCourse* getDestination() const;
	std::string what() const;
};

class NotPassedPrerequisite : public EnrollmentError {
protected:
	PresentedCourse* source;
	Course* destination;
public:
	NotPassedPrerequisite(PresentedCourse* _source = nullptr, Course* _destination = nullptr);
	void setSource(PresentedCourse* _source);
	PresentedCourse* getSource() const;
	void setDestination(Course* _destination);
	Course* getDestination() const;
	std::string what() const;
	static bool haveExceptionWithStatus(const std::map<EnrollmentError*, char>& exceptions, PresentedCourse* _source, Course* _destination, char status);
};

class NotTakenCorequisite : public EnrollmentError {
protected:
	PresentedCourse* source;
	Course* destination;
public:
	NotTakenCorequisite(PresentedCourse* _source = nullptr, Course* _destination = nullptr);
	void setSource(PresentedCourse* _source);
	PresentedCourse* getSource() const;
	void setDestination(Course* _destination);
	Course* getDestination() const;
	std::string what() const;
	static bool haveExceptionWithStatus(const std::map<EnrollmentError*, char>& exceptions, PresentedCourse* _source, Course* _destination, char status);
};

class CourseTimeOverlap : public EnrollmentError {
protected:
	PresentedCourse* source;
	PresentedCourse* destination;
public:
	CourseTimeOverlap(PresentedCourse* _source = nullptr, PresentedCourse* _destination = nullptr);
	void setSource(PresentedCourse* _source);
	PresentedCourse* getSource() const;
	void setDestination(PresentedCourse* _destination);
	PresentedCourse* getDestination() const;
	std::string what() const;
	static bool haveExceptionWithStatus(const std::map<EnrollmentError*, char>& exceptions, PresentedCourse* _source, PresentedCourse* _destination, char status);
};

class ExamTimeOverlap : public EnrollmentError {
protected:
	PresentedCourse* source;
	PresentedCourse* destination;
public:
	ExamTimeOverlap(PresentedCourse* _source = nullptr, PresentedCourse* _destination = nullptr);
	void setSource(PresentedCourse* _source);
	PresentedCourse* getSource() const;
	void setDestination(PresentedCourse* _destination);
	PresentedCourse* getDestination() const;
	std::string what() const;
	static bool haveExceptionWithStatus(const std::map<EnrollmentError*, char>& exceptions, PresentedCourse* _source, PresentedCourse* _destination, char status);
};

class FullCapacity : public EnrollmentError {
	PresentedCourse* source;
public:
	FullCapacity(PresentedCourse* _source = nullptr);
	void setSource(PresentedCourse* _source);
	PresentedCourse* getSource() const;
	std::string what() const;
	static bool haveExceptionWithStatus(const std::map<EnrollmentError*, char>& exceptions, PresentedCourse* _source, char status);
};

#endif // ENROLLMENTERROR_H
