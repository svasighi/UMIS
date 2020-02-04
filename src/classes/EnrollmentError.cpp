#include "../include/EnrollmentError.h"

EnrollmentError::EnrollmentError(short _errorcode)
	: errorcode(_errorcode) {}

short EnrollmentError::getErrorCode() const {
	return errorcode;
}




PassedBefore::PassedBefore(Presented_Course* _source)
	: source(_source), EnrollmentError(EnrollmentError::passed_before) {}

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
	: source(_source), destination(_destination), EnrollmentError(EnrollmentError::not_passed_prerequisite) {}

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
	: source(_source), destination(_destination), EnrollmentError(EnrollmentError::not_taken_corequisite) {}

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
	: source(_source), destination(_destination), EnrollmentError(EnrollmentError::course_time_overlap) {}

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
	: source(_source), destination(_destination), EnrollmentError(EnrollmentError::exam_time_overlap) {}

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
	: source(_source), EnrollmentError(EnrollmentError::full_capacity) {}

void FullCapacity::setSource(Presented_Course* _source) {
	source = _source;
}

Presented_Course* FullCapacity::getSource() const {
	return source;
}

std::string FullCapacity::what() const {
	return "Error #" + std::to_string(errorcode) + " : Course number " + std::to_string(source->getCompleteID()) + " has full capacity";
}



bool NotPassedPrerequisite::haveExceptionWithStatus(const std::map<EnrollmentError*, char>& exceptions, Presented_Course* _source, Course* _destination, char status) {
	for (const auto& exc : exceptions) {
		if (exc.first->getErrorCode() == EnrollmentError::not_passed_prerequisite) {
			NotPassedPrerequisite* e = dynamic_cast<NotPassedPrerequisite*>(exc.first);
			if (e->getSource()->isSameWith(_source) && e->getDestination()->haveSameID(_destination) && exc.second == status) {
				return true;
			}
		}
	}
	return false;
}

bool NotTakenCorequisite::haveExceptionWithStatus(const std::map<EnrollmentError*, char>& exceptions, Presented_Course* _source, Course* _destination, char status) {
	for (const auto& exc : exceptions) {
		if (exc.first->getErrorCode() == EnrollmentError::not_taken_corequisite) {
			NotTakenCorequisite* e = dynamic_cast<NotTakenCorequisite*>(exc.first);
			if (e->getSource()->isSameWith(_source) && e->getDestination()->haveSameID(_destination) && exc.second == status) {
				return true;
			}
		}
	}
	return false;
}

bool CourseTimeOverlap::haveExceptionWithStatus(const std::map<EnrollmentError*, char>& exceptions, Presented_Course* _source, Presented_Course* _destination, char status) {
	for (const auto& exc : exceptions) {
		if (exc.first->getErrorCode() == EnrollmentError::course_time_overlap) {
			CourseTimeOverlap* e = dynamic_cast<CourseTimeOverlap*>(exc.first);
			if (e->getSource()->isSameWith(_source) && e->getDestination()->isSameWith(_destination) && exc.second == status) {
				return true;
			}
		}
	}
	return false;
}

bool ExamTimeOverlap::haveExceptionWithStatus(const std::map<EnrollmentError*, char>& exceptions, Presented_Course* _source, Presented_Course* _destination, char status) {
	for (const auto& exc : exceptions) {
		if (exc.first->getErrorCode() == EnrollmentError::exam_time_overlap) {
			ExamTimeOverlap* e = dynamic_cast<ExamTimeOverlap*>(exc.first);
			if (e->getSource()->isSameWith(_source) && e->getDestination()->isSameWith(_destination) && exc.second == status) {
				return true;
			}
		}
	}
	return false;
}

bool FullCapacity::haveExceptionWithStatus(const std::map<EnrollmentError*, char>& exceptions, Presented_Course* _source, char status) {
	for (const auto& exc : exceptions) {
		if (exc.first->getErrorCode() == EnrollmentError::full_capacity) {
			if (dynamic_cast<FullCapacity*>(exc.first)->getSource()->isSameWith(_source) && exc.second == status) {
				return true;
			}
		}
	}
	return false;
}
