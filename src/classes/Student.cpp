#include <stdexcept>
#include "../include/Student.h"

MyCourse::MyCourse(char _status)
	: score(-1.0F), status(_status), is_objector(false) {}

void MyCourse::setScore(float _score) {
	score = _score;
}

float MyCourse::getScore() const {
	return score;
}

void MyCourse::setStatus(char _status) {
	status = _status;
}

char MyCourse::getStatus() const {
	return status;
}

void MyCourse::setAssessmentAnswers(std::vector<char> _assessment_answers) {
	assessment_answers = _assessment_answers;
}

std::vector<char> MyCourse::getAssessmentAnswers() const {
	return assessment_answers;
}

void MyCourse::setReview(std::string _review) {
	review = _review;
}

std::string MyCourse::getReview() const {
	return review;
}

void MyCourse::setIsObjector(bool _is_objector) {
	is_objector = _is_objector;
}

bool MyCourse::getIsObjector() const {
	return is_objector;
}

void MyCourse::setObjectionText(std::string _objection_text) {
	objection_text = _objection_text;
}

std::string MyCourse::getObjectionText() const {
	return objection_text;
}

void MyCourse::setObjectionReplyText(std::string _objection_reply_text) {
	objection_reply_text = _objection_reply_text;
}

std::string MyCourse::getObjectionReplyText() const {
	return objection_reply_text;
}




MyTerm::MyTerm(int _no)
	: no(_no), status(MyTerm::created) {}

void MyTerm::setno(int _no) {
	no = _no;
}

int MyTerm::getno() const {
	return no;
}

void MyTerm::setStatus(char _status) {
	status = _status;
}

char MyTerm::getStatus() const {
	return status;
}

void MyTerm::setEnrollmentBeginTime(Time _enrollment_begin_time) {
	enrollment_begin_time = _enrollment_begin_time;
}

Time MyTerm::getEnrollmentBeginTime() const {
	return enrollment_begin_time;
}

void MyTerm::setExceptions(std::map<EnrollmentError*, char> _exceptions) {
	exceptions = _exceptions;
}

std::map<EnrollmentError*, char> MyTerm::getExceptions() const {
	return exceptions;
}

void MyTerm::addException(EnrollmentError* exception) {
	exceptions[exception] = 0;
}

void MyTerm::removeException(EnrollmentError* exception) {
	exceptions.erase(exception);
}

void MyTerm::setExceptionStatus(EnrollmentError* exception, char _status) {
	if (exceptions.count(exception) == 0)
		throw std::invalid_argument("exception not found");
	exceptions[exception] = _status;
}

char MyTerm::getExceptionStatus(EnrollmentError* exception) const {
	if (exceptions.count(exception) == 0)
		throw std::invalid_argument("exception not found");
	return exceptions.at(exception);
}

void MyTerm::setCourses(std::map<Presented_Course*, MyCourse> _courses) {
	courses = _courses;
}

std::map<Presented_Course*, MyCourse> MyTerm::getCourses() const {
	return courses;
}

std::vector<Presented_Course*> MyTerm::getCoursesWithoutResult() const {
	std::vector<Presented_Course*> keys;
	keys.reserve(courses.size());
	std::transform(courses.begin(), courses.end(), std::back_inserter(keys),
		[](const auto& pair) {
			return pair.first;
		});
	return keys;
}

int MyTerm::numberofCourses() const {
	return courses.size();
}

int MyTerm::numberofCoursesWithStatus(char _status) const {
	int n = 0;
	for (const auto& x : courses) {
		if (x.second.getStatus() == _status) {
			n++;
		}
	}
	return n;
}

int MyTerm::numberofCredits() const {
	int n = 0;
	for (const auto& x : courses) {
		n += x.first->getCredit();
	}
	return n;
}

int MyTerm::numberofCreditsWithStatus(char _status) const {
	int n = 0;
	for (const auto& x : courses) {
		if (x.second.getStatus() == _status) {
			n += x.first->getCredit();
		}
	}
	return n;
}

void MyTerm::addCourse(Presented_Course* course, char _status) {
	courses[course] = MyCourse(_status);
}

void MyTerm::removeCourse(Presented_Course* course) {
	courses.erase(course);
}

bool MyTerm::haveCourse(Course* course) const {
	for (const auto& c : courses) {
		if (c.first->haveSameID(course)) {
			return true;
		}
	}
	return false;
}

bool MyTerm::haveCourseWithStatus(Course* course, char _status) const {
	for (const auto& c : courses) {
		if (c.first->haveSameID(course) && c.second.getStatus() == _status) {
			return true;
		}
	}
	return false;
}

void MyTerm::setCourseProperties(Presented_Course* course, MyCourse properties) {
	if (courses.count(course) == 0)
		throw std::invalid_argument("course not found");
	courses[course] = properties;
}

MyCourse MyTerm::getCourseProperties(Presented_Course* course) const {
	if (courses.count(course) == 0)
		throw std::invalid_argument("course not found");
	return courses.at(course);
}

void MyTerm::setScoreofCourse(Presented_Course* course, float _score) {
	if (courses.count(course) == 0)
		throw std::invalid_argument("course not found");
	courses[course].setScore(_score);
}

void MyTerm::setStatusofCourse(Presented_Course* course, char _status) {
	if (courses.count(course) == 0)
		throw std::invalid_argument("course not found");
	courses[course].setStatus(_status);
}

void MyTerm::setAssessmentAnswersofCourse(Presented_Course* course, std::vector<char> answers) {
	if (courses.count(course) == 0)
		throw std::invalid_argument("course not found");
	courses[course].setAssessmentAnswers(answers);
}

void MyTerm::setReviewofCourse(Presented_Course* course, std::string review) {
	if (courses.count(course) == 0)
		throw std::invalid_argument("course not found");
	courses[course].setReview(review);
}

void MyTerm::setIsObjectorofCourse(Presented_Course* course, bool is_objector) {
	if (courses.count(course) == 0)
		throw std::invalid_argument("course not found");
	courses[course].setIsObjector(is_objector);
}

void MyTerm::setObjectionTextofCourse(Presented_Course* course, std::string objection_text) {
	if (courses.count(course) == 0)
		throw std::invalid_argument("course not found");
	courses[course].setObjectionText(objection_text);
}

void MyTerm::setObjectionReplyTextofCourse(Presented_Course* course, std::string objection_reply_text) {
	if (courses.count(course) == 0)
		throw std::invalid_argument("course not found");
	courses[course].setObjectionReplyText(objection_reply_text);
}




Student::Student()
	: type(Student::unknown), grade(-1.0F), supervisor(nullptr) {}

Student::Student(int _username, std::string _password, std::string _firstname, std::string _lastname, int _departmentcode, char _type, std::string _field)
	: type(_type), field(_field), grade(-1.0F), supervisor(nullptr), User(_username, _password,_firstname, _lastname, _departmentcode) {}

void Student::setType(char _type) {
	type = _type;
}

char Student::getType() const {
	return type;
}

void Student::setField(std::string _field) {
	field = _field;
}

std::string Student::getField() const {
	return field;
}

void Student::setGrade(float _grade) {
	grade = _grade;
}

float Student::getGrade() const {
	return grade;
}

void Student::setSupervisor(Faculty* _supervisor) {
	supervisor = _supervisor;
}

Faculty* Student::getSupervisor() const {
	return supervisor;
}

void Student::setTerms(std::map<int, MyTerm> _terms) {
	terms = _terms;
}

std::map<int, MyTerm> Student::getTerms() const {
	return terms;
}

int Student::numberofTermsonProbation() const {
	int n = 0;
	for (const auto& x : terms) {
		if (x.second.getStatus() == MyTerm::on_probation) {
			n++;
		}
	}
	return n;
}

int Student::numberofAllCreditsWithStatus(char _status) const {
	int n = 0;
	for (const auto& x : terms) {
		n += x.second.numberofCreditsWithStatus(_status);
	}
	return n;
}

bool Student::haveCourse(Course* course) const {
	for (const auto& t : terms) {
		for (const auto& c : t.second.getCourses()) {
			if (c.first->haveSameID(course)) {
				return true;
			}
		}
	}
	return false;
}

bool Student::haveCourseWithStatus(Course* course, char _status) const {
	for (const auto& t : terms) {
		for (const auto& c : t.second.getCourses()) {
			if (c.first->haveSameID(course) && c.second.getStatus() == _status) {
				return true;
			}
		}
	}
	return false;
}

bool Student::haveCourseWithStatus(short department_id, short group_id, short course_id, char _status) const {
	for (const auto& t : terms) {
		for (const auto& c : t.second.getCourses()) {
			if (c.first->getCourse_id() == department_id && c.first->getGroup_id() == group_id
				&& c.first->getDepartment_id() == course_id && c.second.getStatus() == _status) {
				return true;
			}
		}
	}
	return false;
}

std::vector<std::unique_ptr<EnrollmentError>> Student::checkEnrollment(int term_no, std::vector<Presented_Course*> courses)
{
	std::vector<std::unique_ptr<EnrollmentError>> errors;
	std::map<EnrollmentError*, char> exceptions = terms[term_no].getExceptions();
	for (const auto& course : courses)
	{
		if (this->haveCourseWithStatus(course, MyCourse::passed)) {
			errors.push_back(std::unique_ptr<EnrollmentError>(new PassedBefore(course)));
		}
		if (course->getEnrolledNumber() >= course->getCapacity()) {
			if (FullCapacity::haveExceptionWithStatus(exceptions, course, 2) == false) {
				errors.push_back(std::unique_ptr<EnrollmentError>(new FullCapacity(course)));
			}
		}
		for (const auto& preR : course->getPrerequisites()) {
			if (this->haveCourseWithStatus(preR, MyCourse::passed) == false) {
				if (NotPassedPrerequisite::haveExceptionWithStatus(exceptions, course, preR, 2) == false) {
					errors.push_back(std::unique_ptr<EnrollmentError>(new NotPassedPrerequisite(course, preR)));
				}
			}
		}
		for (const auto& coR : course->getCorequisites()) {
			if (coR->searchSameIDin(courses) == false && this->getTerm(term_no).haveCourse(coR) == false && this->haveCourseWithStatus(coR, MyCourse::passed) == false) {
				if (NotTakenCorequisite::haveExceptionWithStatus(exceptions, course, coR, 2) == false) {
					errors.push_back(std::unique_ptr<EnrollmentError>(new NotTakenCorequisite(course, coR)));
				}
			}
		}
		for (const auto& c : courses) {
			if (c->getCourseTime().haveOverlapWith(course->getCourseTime())) {
				if (CourseTimeOverlap::haveExceptionWithStatus(exceptions, course, c, 2) == false) {
					errors.push_back(std::unique_ptr<EnrollmentError>(new CourseTimeOverlap(course, c)));
				}
			}
			if (c->getFinalExamTime().haveOverlapWith(course->getFinalExamTime())) {
				if (ExamTimeOverlap::haveExceptionWithStatus(exceptions, course, c, 2) == false) {
					errors.push_back(std::unique_ptr<EnrollmentError>(new ExamTimeOverlap(course, c)));
				}
			}
		}
	}
	return errors;
}

std::vector<std::unique_ptr<EnrollmentError>> Student::commitEnrollment(int term_no, std::vector<Presented_Course*> courses) {
	std::vector<std::unique_ptr<EnrollmentError>> temp = checkEnrollment(term_no, courses);
	if (temp.empty()) {
		for (const auto& c : courses) {
			terms[term_no].addCourse(c, MyCourse::enrolled);
		}
	}
	return temp;
}

void Student::addTerm(MyTerm term) {
	terms[term.getno()] = term;
}

void Student::addTerm(int term_no) {
	terms[term_no] = MyTerm();
}

void Student::setTerm(int term_no, MyTerm term) {
	terms[term_no] = term;
}

MyTerm Student::getTerm(int term_no) const {
	return terms.at(term_no);
}

void Student::setTermStatus(int term_no, char _status) {
	terms[term_no].setStatus(_status);
}

char Student::getTermStatus(int term_no) const {
	return terms.at(term_no).getStatus();
}

void Student::setTermEnrollmentBeginTime(int term_no, Time enrollment_begin_time) {
	terms[term_no].setEnrollmentBeginTime(enrollment_begin_time);
}

Time Student::getTermEnrollmentBeginTime(int term_no) const {
	return terms.at(term_no).getEnrollmentBeginTime();
}

void Student::addException(int term_no, EnrollmentError* exception) {
	terms[term_no].addException(exception);
}

void Student::removeException(int term_no, EnrollmentError* exception) {
	terms[term_no].removeException(exception);
}

void Student::setExceptionStatus(int term_no, EnrollmentError* exception, char _status) {
	terms[term_no].setExceptionStatus(exception, _status);
}

std::map<Presented_Course*, MyCourse> Student::getTermCourses(int term_no) const {
	return terms.at(term_no).getCourses();
}

std::vector<Presented_Course*> Student::getTermCoursesWithoutResult(int term_no) const {
	return terms.at(term_no).getCoursesWithoutResult();
}

void Student::addCourse(Presented_Course* course, char _status) {
	terms[course->getTerm_no()].addCourse(course, _status);
	// course->addStudent(this);
}

void Student::removeCourse(Presented_Course* course) {
	terms[course->getTerm_no()].removeCourse(course);
	// course->removeStudent(this);
}

void Student::setCourseProperties(Presented_Course* course, MyCourse properties) {
	terms[course->getTerm_no()].setCourseProperties(course, properties);
}

MyCourse Student::getCourseProperties(Presented_Course* course) const {
	return terms.at(course->getTerm_no()).getCourseProperties(course);
}

void Student::setScoreofCourse(Presented_Course* course, float _score) {
	terms[course->getTerm_no()].setScoreofCourse(course, _score);
}

float Student::getScoreofCourse(Presented_Course* course) const {
	return terms.at(course->getTerm_no()).getCourseProperties(course).getScore();
}

void Student::setStatusofCourse(Presented_Course* course, char _status) {
	terms[course->getTerm_no()].setStatusofCourse(course, _status);
}

char Student::getStatusofCourse(Presented_Course* course) const {
	return terms.at(course->getTerm_no()).getCourseProperties(course).getStatus();
}

void Student::setAssessmentAnswersofCourse(Presented_Course* course, std::vector<char> answers) {
	terms[course->getTerm_no()].setAssessmentAnswersofCourse(course, answers);
}

std::vector<char> Student::getAssessmentAnswersofCourse(Presented_Course* course) const {
	return terms.at(course->getTerm_no()).getCourseProperties(course).getAssessmentAnswers();
}

void Student::setReviewofCourse(Presented_Course* course, std::string review) {
	terms[course->getTerm_no()].setReviewofCourse(course, review);
}

std::string Student::getReviewofCourse(Presented_Course* course) const {
	return terms.at(course->getTerm_no()).getCourseProperties(course).getReview();
}

void Student::setIsObjectorofCourse(Presented_Course* course, bool is_objector) {
	terms[course->getTerm_no()].setIsObjectorofCourse(course, is_objector);
}

bool Student::getIsObjectorofCourse(Presented_Course* course) const {
	return terms.at(course->getTerm_no()).getCourseProperties(course).getIsObjector();
}

void Student::setObjectionTextofCourse(Presented_Course* course, std::string objection_text) {
	terms[course->getTerm_no()].setObjectionTextofCourse(course, objection_text);
}

std::string Student::getObjectionTextofCourse(Presented_Course* course) const {
	return terms.at(course->getTerm_no()).getCourseProperties(course).getObjectionText();
}

void Student::setObjectionReplyTextofCourse(Presented_Course* course, std::string objection_reply_text) {
	terms[course->getTerm_no()].setObjectionReplyTextofCourse(course, objection_reply_text);
}

std::string Student::getObjectionReplyTextofCourse(Presented_Course* course) const {
	return terms.at(course->getTerm_no()).getCourseProperties(course).getObjectionReplyText();
}

int Student::computeTuition(int term_no) {
	if (type == Student::day)
		return 0;
	return terms[term_no].numberofCredits();// * credit_fee[type] + const_tuition;
}
