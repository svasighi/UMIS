#include "../include/EnrollmentError.h"

EnrollmentError::EnrollmentError(short _errorcode)
	: errorcode(_errorcode) {}

short EnrollmentError::getErrorCode() const {
	return errorcode;
}




PassedBefore::PassedBefore(Presented_Course* _source)
	: source(_source), EnrollmentError(1) {}

void PassedBefore::setSource(Presented_Course* _source) {
	source = _source;
}

Presented_Course* PassedBefore::getSource() const {
	return source;
}

std::string PassedBefore::what() const {
	return "Error #" + std::to_string(errorcode) + " : Course number " + std::to_string(source->getCompleteID()) + " passed before";
}




NotPassedPrerequisite::NotPassedPrerequisite(Presented_Course* _source, Course* _destination)
	: source(_source), destination(_destination), EnrollmentError(2) {}

void NotPassedPrerequisite::setSource(Presented_Course* _source) {
	source = _source;
}

Presented_Course* NotPassedPrerequisite::getSource() const {
	return source;
}

void NotPassedPrerequisite::setDestination(Course* _destination) {
	destination = _destination;
}

Course* NotPassedPrerequisite::getDestination() const {
	return destination;
}

std::string NotPassedPrerequisite::what() const {
	return "Error #" + std::to_string(errorcode) + " : Not passing prerequisite course with number " + std::to_string(destination->getCompleteID()) + " for course number " + std::to_string(source->getCompleteID());
}




NotTakenCorequisite::NotTakenCorequisite(Presented_Course* _source, Course* _destination)
	: source(_source), destination(_destination), EnrollmentError(3) {}

void NotTakenCorequisite::setSource(Presented_Course* _source) {
	source = _source;
}

Presented_Course* NotTakenCorequisite::getSource() const {
	return source;
}

void NotTakenCorequisite::setDestination(Course* _destination) {
	destination = _destination;
}

Course* NotTakenCorequisite::getDestination() const {
	return destination;
}

std::string NotTakenCorequisite::what() const {
	return "Error #" + std::to_string(errorcode) + " : Not passing or taking corequisite course with number " + std::to_string(destination->getCompleteID()) + " for course number " + std::to_string(source->getCompleteID());
}




CourseTimeOverlap::CourseTimeOverlap(Presented_Course* _source, Presented_Course* _destination)
	: source(_source), destination(_destination), EnrollmentError(4) {}

void CourseTimeOverlap::setSource(Presented_Course* _source) {
	source = _source;
}

Presented_Course* CourseTimeOverlap::getSource() const {
	return source;
}

void CourseTimeOverlap::setDestination(Presented_Course* _destination) {
	destination = _destination;
}

Presented_Course* CourseTimeOverlap::getDestination() const {
	return destination;
}

std::string CourseTimeOverlap::what() const {
	return "Error #" + std::to_string(errorcode) + " : Course number " + std::to_string(source->getCompleteID()) + " has presentation time overlap with course number " + std::to_string(destination->getCompleteID());
}




ExamTimeOverlap::ExamTimeOverlap(Presented_Course* _source, Presented_Course* _destination)
	: source(_source), destination(_destination), EnrollmentError(5) {}

void ExamTimeOverlap::setSource(Presented_Course* _source) {
	source = _source;
}

Presented_Course* ExamTimeOverlap::getSource() const {
	return source;
}

void ExamTimeOverlap::setDestination(Presented_Course* _destination) {
	destination = _destination;
}

Presented_Course* ExamTimeOverlap::getDestination() const {
	return destination;
}

std::string ExamTimeOverlap::what() const {
	return "Error #" + std::to_string(errorcode) + " : Course number " + std::to_string(source->getCompleteID()) + " has finalexam time overlap with course number " + std::to_string(destination->getCompleteID());
}




FullCapacity::FullCapacity(Presented_Course* _source)
	: source(_source), EnrollmentError(6) {}

void FullCapacity::setSource(Presented_Course* _source) {
	source = _source;
}

Presented_Course* FullCapacity::getSource() const {
	return source;
}

std::string FullCapacity::what() const {
	return "Error #" + std::to_string(errorcode) + " : Course number " + std::to_string(source->getCompleteID()) + " has full capacity";
}
