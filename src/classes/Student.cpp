#include <stdexcept>
#include "../include/Student.h"

MyCourse::MyCourse(char _status)
	: score(-1.0F), status(_status), is_objector(false) {}

void MyCourse::setScore(float _score) {
	if (_score > 20 || _score < 0)
		throw std::invalid_argument("score must be 0-20");
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

void MyCourse::setAssessmentAnswers(const std::vector<char>& _assessment_answers) {
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




MyTerm::MyTerm(int _no, char _status)
	: no(_no), status(_status) {}

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

void MyTerm::setPreliminaryCourses(const std::vector<Course*>& _preliminary_courses) {
	if (this->status == MyTerm::created) {
		preliminary_courses = _preliminary_courses;
	}
}

std::vector<Course*> MyTerm::getPreliminaryCourses() const {
	return preliminary_courses;
}

void MyTerm::addPreliminaryCourse(Course* course) {
	if (this->status == MyTerm::created) {
		if (std::find(preliminary_courses.begin(), preliminary_courses.end(), course) == preliminary_courses.end()) {
			preliminary_courses.push_back(course);
		}
	}
}

void MyTerm::removePreliminaryCourse(Course* course) {
	if (this->status == MyTerm::created) {
		preliminary_courses.erase(std::find(preliminary_courses.begin(), preliminary_courses.end(), course));
	}
}

void MyTerm::setCourses(const std::map<Presented_Course*, MyCourse>& _courses) {
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

void MyTerm::setCourseProperties(Presented_Course* course, const MyCourse& properties) {
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

void MyTerm::setAssessmentAnswersofCourse(Presented_Course* course, const std::vector<char>& answers) {
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
	: type(Student::day), grade(-1.0F), supervisor(nullptr) {}

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

void Student::updateGrade() {
	float sum = 0;
	int number_of_credits = 0;
	for (const auto& t : terms) {
		for (const auto& c : t.second.getCourses()) {
			if (c.second.getStatus() == MyCourse::passed || c.second.getStatus() == MyCourse::refused) {
				sum += c.second.getScore() * c.first->getCredit();
				number_of_credits += c.first->getCredit();
			}
		}
	}
	grade = sum / number_of_credits;
}

void Student::setGrade(float _grade) {
	if (_grade > 20 || _grade < 0)
		throw std::invalid_argument("grade must be 0-20");
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

void Student::setTerms(const std::map<int, MyTerm>& _terms) {
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

std::vector<std::unique_ptr<EnrollmentError>> Student::checkEnrollment(int term_no, const std::map<Presented_Course*, char>& enroll_courses)
{
	std::vector<std::unique_ptr<EnrollmentError>> errors;
	std::map<EnrollmentError*, char> exceptions = terms[term_no].getExceptions();
	std::map<Presented_Course*, char> courses;
	std::vector<Course*> keys;
	for (const auto& c : enroll_courses) {
		if (c.second == ENROLL || c.second == WAIT) {
			courses.insert(std::make_pair(c.first, c.second));
			keys.push_back(c.first);
		}
	}
	for (const auto& course : courses)
	{
		if (this->haveCourseWithStatus(course.first, MyCourse::passed)) {
			errors.push_back(std::unique_ptr<EnrollmentError>(new PassedBefore(course.first)));
		}

		if (course.first->getEnrolledNumber() >= course.first->getCapacity() && course.second == ENROLL) {
			if (FullCapacity::haveExceptionWithStatus(exceptions, course.first, 2) == false) {
				errors.push_back(std::unique_ptr<EnrollmentError>(new FullCapacity(course.first)));
			}
		}

		for (const auto& preR : course.first->getPrerequisites()) {
			if (this->haveCourseWithStatus(preR, MyCourse::passed) == false) {
				if (NotPassedPrerequisite::haveExceptionWithStatus(exceptions, course.first, preR, 2) == false) {
					errors.push_back(std::unique_ptr<EnrollmentError>(new NotPassedPrerequisite(course.first, preR)));
				}
			}
		}

		for (const auto& coR : course.first->getCorequisites()) {
			if (coR->searchSameIDin(keys) == false && this->haveCourseWithStatus(coR, MyCourse::passed) == false) {
				if (NotTakenCorequisite::haveExceptionWithStatus(exceptions, course.first, coR, 2) == false) {
					errors.push_back(std::unique_ptr<EnrollmentError>(new NotTakenCorequisite(course.first, coR)));
				}
			}
		}

		for (const auto& c : courses) {
			if (c != course) {
				if (c.first->haveSameID(course.first)) {
					errors.push_back(std::unique_ptr<EnrollmentError>(new TakenSameCourse(course.first, c.first)));
				}

				if (c.first->getCourseTime().haveOverlapWith(course.first->getCourseTime())) {
					if (CourseTimeOverlap::haveExceptionWithStatus(exceptions, course.first, c.first, 2) == false) {
						errors.push_back(std::unique_ptr<EnrollmentError>(new CourseTimeOverlap(course.first, c.first)));
					}
				}

				if (c.first->getFinalExamTime().haveOverlapWith(course.first->getFinalExamTime())) {
					if (ExamTimeOverlap::haveExceptionWithStatus(exceptions, course.first, c.first, 2) == false) {
						errors.push_back(std::unique_ptr<EnrollmentError>(new ExamTimeOverlap(course.first, c.first)));
					}
				}
			}
		}
	}
	return errors;
}

std::vector<std::unique_ptr<EnrollmentError>> Student::commitEnrollment(int term_no, const std::map<Presented_Course*, char>& enroll_courses) {
	std::vector<std::unique_ptr<EnrollmentError>> temp = checkEnrollment(term_no, enroll_courses);
	if (terms.count(term_no) == 0) {
		this->addTerm(term_no, MyTerm::enrollment_in_action);
	}
	// (terms.at(term_no).getStatus() == MyTerm::enrollment_in_action);
	if (temp.empty()) {
		for (const auto& c : enroll_courses) {
			if (c.second == ENROLL){
				terms[term_no].addCourse(c.first, MyCourse::enrolled);
				c.first->addStudent(this);
				c.first->addEnrolledNumber();
			}
			else if (c.second == WAIT) {
				if (c.first->getEnrolledNumber() < c.first->getCapacity()) {
					terms[term_no].addCourse(c.first, MyCourse::enrolled);
					c.first->addStudent(this);
					c.first->addEnrolledNumber();
				}
				else {
					terms[term_no].addCourse(c.first, MyCourse::waiting);
					c.first->addStudent(this);
					c.first->addWaitingNumber();
				}
			}
			else if (c.second == REMOVE) {
				terms[term_no].removeCourse(c.first);
				c.first->removeStudent(this);
				if (this->terms.at(term_no).getCourseProperties(c.first).getStatus() == MyCourse::enrolled) {
					c.first->addEnrolledNumber(-1);
				}
				else if (this->terms.at(term_no).getCourseProperties(c.first).getStatus() == MyCourse::waiting) {
					c.first->addWaitingNumber(-1);
				}
			}
		}
	}
	return temp;
}

std::vector<std::unique_ptr<EnrollmentError>> Student::checkPreliminaryEnrollment(int term_no, const std::vector<Course*>& preliminary_courses) {
	std::vector<std::unique_ptr<EnrollmentError>> errors;
	for (const auto& course : preliminary_courses) {
		if (this->haveCourseWithStatus(course, MyCourse::passed)) {
			errors.push_back(std::unique_ptr<EnrollmentError>(new PassedBefore(course)));
		}
	}
	return errors;
}

std::vector<std::unique_ptr<EnrollmentError>> Student::commitPreliminaryEnrollment(int term_no, const std::vector<Course*>& preliminary_courses) {
	std::vector<std::unique_ptr<EnrollmentError>> temp = checkPreliminaryEnrollment(term_no, preliminary_courses);
	if (terms.count(term_no) == 0) {
		this->addTerm(term_no, MyTerm::created);
	}
	if (temp.empty() && terms.at(term_no).getStatus() == MyTerm::created) {
		terms[term_no].setPreliminaryCourses(preliminary_courses);
	}
	return temp;
}

void Student::addTerm(MyTerm term) {
	terms[term.getno()] = term;
}

void Student::addTerm(int term_no, char _status) {
	terms[term_no] = MyTerm(term_no, _status);
}

MyTerm Student::getTerm(int term_no) const {
	if (terms.count(term_no) == 0)
		throw std::invalid_argument("term not found");
	return terms.at(term_no);
}

void Student::setTermStatus(int term_no, char _status) {
	if (terms.count(term_no) == 0)
		throw std::invalid_argument("term not found");
	terms[term_no].setStatus(_status);
}

char Student::getTermStatus(int term_no) const {
	if (terms.count(term_no) == 0)
		throw std::invalid_argument("term not found");
	return terms.at(term_no).getStatus();
}

void Student::setTermEnrollmentBeginTime(int term_no, Time enrollment_begin_time) {
	if (terms.count(term_no) == 0)
		throw std::invalid_argument("term not found");
	terms[term_no].setEnrollmentBeginTime(enrollment_begin_time);
}

void Student::addException(int term_no, EnrollmentError* exception) {
	if (terms.count(term_no) == 0)
		throw std::invalid_argument("term not found");
	terms[term_no].addException(exception);
}

void Student::removeException(int term_no, EnrollmentError* exception) {
	if (terms.count(term_no) == 0)
		throw std::invalid_argument("term not found");
	terms[term_no].removeException(exception);
}

void Student::setExceptionStatus(int term_no, EnrollmentError* exception, char _status) {
	if (terms.count(term_no) == 0)
		throw std::invalid_argument("term not found");
	terms[term_no].setExceptionStatus(exception, _status);
}

std::map<Presented_Course*, MyCourse> Student::getTermCourses(int term_no) const {
	if (terms.count(term_no) == 0)
		throw std::invalid_argument("term not found");
	return terms.at(term_no).getCourses();
}

std::vector<Presented_Course*> Student::getTermCoursesWithoutResult(int term_no) const {
	if (terms.count(term_no) == 0)
		throw std::invalid_argument("term not found");
	return terms.at(term_no).getCoursesWithoutResult();
}

void Student::addCourse(Presented_Course* course, char _status) {
	if (terms.count(course->getTerm_no()) == 0)
		throw std::invalid_argument("term not found");
	terms[course->getTerm_no()].addCourse(course, _status);
}

void Student::removeCourse(Presented_Course* course) {
	if (terms.count(course->getTerm_no()) == 0)
		throw std::invalid_argument("term not found");
	terms[course->getTerm_no()].removeCourse(course);
}

void Student::setCourseProperties(Presented_Course* course, const MyCourse& properties) {
	if (terms.count(course->getTerm_no()) == 0)
		throw std::invalid_argument("term not found");
	terms[course->getTerm_no()].setCourseProperties(course, properties);
}

MyCourse Student::getCourseProperties(Presented_Course* course) const {
	if (terms.count(course->getTerm_no()) == 0)
		throw std::invalid_argument("term not found");
	return terms.at(course->getTerm_no()).getCourseProperties(course);
}

void Student::setScoreofCourse(Presented_Course* course, float _score) {
	if (terms.count(course->getTerm_no()) == 0)
		throw std::invalid_argument("term not found");
	terms[course->getTerm_no()].setScoreofCourse(course, _score);
}

float Student::getScoreofCourse(Presented_Course* course) const {
	if (terms.count(course->getTerm_no()) == 0)
		throw std::invalid_argument("term not found");
	return terms.at(course->getTerm_no()).getCourseProperties(course).getScore();
}

void Student::setStatusofCourse(Presented_Course* course, char _status) {
	if (terms.count(course->getTerm_no()) == 0)
		throw std::invalid_argument("term not found");
	terms[course->getTerm_no()].setStatusofCourse(course, _status);
}

char Student::getStatusofCourse(Presented_Course* course) const {
	if (terms.count(course->getTerm_no()) == 0)
		throw std::invalid_argument("term not found");
	return terms.at(course->getTerm_no()).getCourseProperties(course).getStatus();
}

void Student::setAssessmentAnswersofCourse(Presented_Course* course, std::vector<char> answers) {
	if (terms.count(course->getTerm_no()) == 0)
		throw std::invalid_argument("term not found");
	terms[course->getTerm_no()].setAssessmentAnswersofCourse(course, answers);
}

std::vector<char> Student::getAssessmentAnswersofCourse(Presented_Course* course) const {
	if (terms.count(course->getTerm_no()) == 0)
		throw std::invalid_argument("term not found");
	return terms.at(course->getTerm_no()).getCourseProperties(course).getAssessmentAnswers();
}

void Student::setReviewofCourse(Presented_Course* course, std::string review) {
	if (terms.count(course->getTerm_no()) == 0)
		throw std::invalid_argument("term not found");
	terms[course->getTerm_no()].setReviewofCourse(course, review);
}

std::string Student::getReviewofCourse(Presented_Course* course) const {
	if (terms.count(course->getTerm_no()) == 0)
		throw std::invalid_argument("term not found");
	return terms.at(course->getTerm_no()).getCourseProperties(course).getReview();
}

void Student::setIsObjectorofCourse(Presented_Course* course, bool is_objector) {
	if (terms.count(course->getTerm_no()) == 0)
		throw std::invalid_argument("term not found");
	terms[course->getTerm_no()].setIsObjectorofCourse(course, is_objector);
}

bool Student::getIsObjectorofCourse(Presented_Course* course) const {
	if (terms.count(course->getTerm_no()) == 0)
		throw std::invalid_argument("term not found");
	return terms.at(course->getTerm_no()).getCourseProperties(course).getIsObjector();
}

void Student::setObjectionTextofCourse(Presented_Course* course, std::string objection_text) {
	if (terms.count(course->getTerm_no()) == 0)
		throw std::invalid_argument("term not found");
	terms[course->getTerm_no()].setObjectionTextofCourse(course, objection_text);
}

std::string Student::getObjectionTextofCourse(Presented_Course* course) const {
	if (terms.count(course->getTerm_no()) == 0)
		throw std::invalid_argument("term not found");
	return terms.at(course->getTerm_no()).getCourseProperties(course).getObjectionText();
}

void Student::setObjectionReplyTextofCourse(Presented_Course* course, std::string objection_reply_text) {
	if (terms.count(course->getTerm_no()) == 0)
		throw std::invalid_argument("term not found");
	terms[course->getTerm_no()].setObjectionReplyTextofCourse(course, objection_reply_text);
}

std::string Student::getObjectionReplyTextofCourse(Presented_Course* course) const {
	if (terms.count(course->getTerm_no()) == 0)
		throw std::invalid_argument("term not found");
	return terms.at(course->getTerm_no()).getCourseProperties(course).getObjectionReplyText();
}

int Student::computeTuition(int term_no) {
	if (terms.count(term_no) == 0)
		throw std::invalid_argument("term not found");
	if (type == Student::day)
		return 0;
	return terms[term_no].numberofCredits();// * credit_fee[type] + const_tuition;
}
