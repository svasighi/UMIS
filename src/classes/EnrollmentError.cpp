#include "../include/EnrollmentError.h"

EnrollmentError::EnrollmentError(short _errorcode)
	: errorcode(_errorcode) {}

short EnrollmentError::getErrorCode() const {
	return errorcode;
}




PassedBefore::PassedBefore(Course* _source)
	: source(_source), EnrollmentError(EnrollmentError::passed_before) {}

void PassedBefore::setSource(Course* _source) {
	source = _source;
}

Course* PassedBefore::getSource() const {
	return source;
}

std::string PassedBefore::what() const {
	return "Error #" + std::to_string(errorcode) + " : course number " + std::to_string(source->getCourseID()) + " passed before";
}




TakenSameCourse::TakenSameCourse(PresentedCourse* _source, PresentedCourse* _destination)
	: source(_source), destination(_destination), EnrollmentError(EnrollmentError::taken_same_course) {}

void TakenSameCourse::setSource(PresentedCourse* _source) {
	source = _source;
}

PresentedCourse* TakenSameCourse::getSource() const {
	return source;
}

void TakenSameCourse::setDestination(PresentedCourse* _destination) {
	destination = _destination;
}

PresentedCourse* TakenSameCourse::getDestination() const {
	return destination;
}

std::string TakenSameCourse::what() const {
	return "Error #" + std::to_string(errorcode) + " : course number " + std::to_string(source->getCourseID()) + "  is same as course number " + std::to_string(destination->getCourseID());
}




NotPassedPrerequisite::NotPassedPrerequisite(PresentedCourse* _source, Course* _destination)
	: source(_source), destination(_destination), EnrollmentError(EnrollmentError::not_passed_prerequisite) {}

void NotPassedPrerequisite::setSource(PresentedCourse* _source) {
	source = _source;
}

PresentedCourse* NotPassedPrerequisite::getSource() const {
	return source;
}

void NotPassedPrerequisite::setDestination(Course* _destination) {
	destination = _destination;
}

Course* NotPassedPrerequisite::getDestination() const {
	return destination;
}

std::string NotPassedPrerequisite::what() const {
	return "Error #" + std::to_string(errorcode) + " : not passing prerequisite course with number " + std::to_string(destination->getCourseID()) + " for course number " + std::to_string(source->getCourseID());
}




NotTakenCorequisite::NotTakenCorequisite(PresentedCourse* _source, Course* _destination)
	: source(_source), destination(_destination), EnrollmentError(EnrollmentError::not_taken_corequisite) {}

void NotTakenCorequisite::setSource(PresentedCourse* _source) {
	source = _source;
}

PresentedCourse* NotTakenCorequisite::getSource() const {
	return source;
}

void NotTakenCorequisite::setDestination(Course* _destination) {
	destination = _destination;
}

Course* NotTakenCorequisite::getDestination() const {
	return destination;
}

std::string NotTakenCorequisite::what() const {
	return "Error #" + std::to_string(errorcode) + " : not passing or taking corequisite course with number " + std::to_string(destination->getCourseID()) + " for course number " + std::to_string(source->getCourseID());
}




CourseTimeOverlap::CourseTimeOverlap(PresentedCourse* _source, PresentedCourse* _destination)
	: source(_source), destination(_destination), EnrollmentError(EnrollmentError::course_time_overlap) {}

void CourseTimeOverlap::setSource(PresentedCourse* _source) {
	source = _source;
}

PresentedCourse* CourseTimeOverlap::getSource() const {
	return source;
}

void CourseTimeOverlap::setDestination(PresentedCourse* _destination) {
	destination = _destination;
}

PresentedCourse* CourseTimeOverlap::getDestination() const {
	return destination;
}

std::string CourseTimeOverlap::what() const {
	return "Error #" + std::to_string(errorcode) + " : course number " + std::to_string(source->getCourseID()) + " has presentation time overlap with course number " + std::to_string(destination->getCourseID());
}




ExamTimeOverlap::ExamTimeOverlap(PresentedCourse* _source, PresentedCourse* _destination)
	: source(_source), destination(_destination), EnrollmentError(EnrollmentError::exam_time_overlap) {}

void ExamTimeOverlap::setSource(PresentedCourse* _source) {
	source = _source;
}

PresentedCourse* ExamTimeOverlap::getSource() const {
	return source;
}

void ExamTimeOverlap::setDestination(PresentedCourse* _destination) {
	destination = _destination;
}

PresentedCourse* ExamTimeOverlap::getDestination() const {
	return destination;
}

std::string ExamTimeOverlap::what() const {
	return "Error #" + std::to_string(errorcode) + " : Course number " + std::to_string(source->getCourseID()) + " has finalexam time overlap with course number " + std::to_string(destination->getCourseID());
}




FullCapacity::FullCapacity(PresentedCourse* _source)
	: source(_source), EnrollmentError(EnrollmentError::full_capacity) {}

void FullCapacity::setSource(PresentedCourse* _source) {
	source = _source;
}

PresentedCourse* FullCapacity::getSource() const {
	return source;
}

std::string FullCapacity::what() const {
	return "Error #" + std::to_string(errorcode) + " : course number " + std::to_string(source->getCourseID()) + " has full capacity";
}



bool NotPassedPrerequisite::haveExceptionWithStatus(const std::map<EnrollmentError*, char>& exceptions, PresentedCourse* _source, Course* _destination, char status) {
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

bool NotTakenCorequisite::haveExceptionWithStatus(const std::map<EnrollmentError*, char>& exceptions, PresentedCourse* _source, Course* _destination, char status) {
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

bool CourseTimeOverlap::haveExceptionWithStatus(const std::map<EnrollmentError*, char>& exceptions, PresentedCourse* _source, PresentedCourse* _destination, char status) {
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

bool ExamTimeOverlap::haveExceptionWithStatus(const std::map<EnrollmentError*, char>& exceptions, PresentedCourse* _source, PresentedCourse* _destination, char status) {
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

bool FullCapacity::haveExceptionWithStatus(const std::map<EnrollmentError*, char>& exceptions, PresentedCourse* _source, char status) {
	for (const auto& exc : exceptions) {
		if (exc.first->getErrorCode() == EnrollmentError::full_capacity) {
			if (dynamic_cast<FullCapacity*>(exc.first)->getSource()->isSameWith(_source) && exc.second == status) {
				return true;
			}
		}
	}
	return false;
}
