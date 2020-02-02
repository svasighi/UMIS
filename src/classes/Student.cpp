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
	: no(_no), status(0) {}

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

void MyTerm::setCourses(std::map<Presented_Course*, MyCourse> _courses) {
	courses = _courses;
}

std::map<Presented_Course*, MyCourse> MyTerm::getCourses() const {
	return courses;
}

std::vector<Presented_Course*> MyTerm::getCoursesWithoutResult() const {
	std::vector<Presented_Course*> keys;
	keys.reserve(courses.size());
	transform(courses.begin(), courses.end(), std::back_inserter(keys),
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

bool MyTerm::hasCourse(Presented_Course* course) const {
	return courses.count(course);
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
	: type(-1), grade(-1.0F), supervisor(nullptr) {}

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
		if (x.second.getStatus() == 7) {
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

std::map<Presented_Course*, MyCourse> Student::getTermCourses(int term_no) const {
	return terms.at(term_no).getCourses();
}

std::vector<Presented_Course*> Student::getTermCoursesWithoutResult(int term_no) const {
	return terms.at(term_no).getCoursesWithoutResult();
}

int Student::numberofCourses(int term_no) const {
	return terms.at(term_no).numberofCourses();
}

int Student::numberofCoursesWithStatus(int term_no, char _status) const {
	return terms.at(term_no).numberofCoursesWithStatus(_status);
}

int Student::numberofCredits(int term_no) const {
	return terms.at(term_no).numberofCredits();
}

int Student::numberofCreditsWithStatus(int term_no, char _status) const {
	return terms.at(term_no).numberofCreditsWithStatus(_status);
}

void Student::addCourse(Presented_Course* course, char _status) {
	terms[course->getTerm_no()].addCourse(course, _status);
	// course->addStudent(this);
}

void Student::removeCourse(Presented_Course* course) {
	terms[course->getTerm_no()].removeCourse(course);
	// course->removeStudent(this);
}

bool Student::hasCourse(Presented_Course* course) const {
	return terms.at(course->getTerm_no()).hasCourse(course);
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
	if (type == 3)
		return 0;
	return terms[term_no].numberofCredits();// * credit_fee[type] + const_tuition;
}
