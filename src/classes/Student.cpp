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
void MyCourse::setObjectonReplyText(std::string _objection_reply_text) {
	objection_reply_text = _objection_reply_text;
}

std::string MyCourse::getObjectonReplyText() const {
	return  objection_reply_text;
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

int MyTerm::numberofCredits() const {
	int n = 0;
	for (const auto& x : courses) {
		n += x.first->getCredit();
	}
	return n;
}

void MyTerm::addCourse(Presented_Course* course) {
	courses[course] = MyCourse();
}

void MyTerm::removeCourse(Presented_Course* course) {
	courses.erase(course);
}

void MyTerm::setCourseProperties(Presented_Course* course, MyCourse properties) {
	courses[course] = properties;
}

MyCourse MyTerm::getCourseProperties(Presented_Course* course) const {
	if (courses.count(course) == 0)
		throw std::invalid_argument("course not found");
	return courses.at(course);
}

void MyTerm::setScoreofCourse(Presented_Course* course, float score) {
	courses[course].setScore(score);
}

void MyTerm::setStatusofCourse(Presented_Course* course, char status) {
	courses[course].setStatus(status);
}

void MyTerm::setAssessmentAnswersofCourse(Presented_Course* course, std::vector<char> answers) {
	courses[course].setAssessmentAnswers(answers);
}

void MyTerm::setReviewofCourse(Presented_Course* course, std::string review) {
	courses[course].setReview(review);
}

void MyTerm::setIsObjectorofCourse(Presented_Course* course, bool is_objector) {
	courses[course].setIsObjector(is_objector);
}

void MyTerm::setObjectionTextofCourse(Presented_Course* course, std::string objection_text) {
	courses[course].setObjectionText(objection_text);
}

void MyTerm::setObjectionReplyTextofCourse(Presented_Course* course, std::string objection_reply_text) {
	courses[course].setObjectonReplyText(objection_reply_text);
}

Student::Student()
	: grade(-1.0F), supervisor(nullptr) {}

Student::Student(int _username, std::string _password, std::string _firstname, std::string _lastname, int _departmentcode, std::string _field)
	: field(_field), grade(-1.0F), supervisor(nullptr), User(_username, _password,_firstname, _lastname, _departmentcode) {}

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

void Student::setTermStatus(int term_no, char status) {
	terms[term_no].setStatus(status);
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
	std::map<Presented_Course*, MyCourse>* m = &terms.at(term_no).getCourses();
	std::vector<Presented_Course*> keys;
	keys.reserve(m->size());
	transform(m->begin(), m->end(), std::back_inserter(keys),
		[](const auto& pair) {
			return pair.first;
		});
	return keys;
}

int Student::numberofCredits(int term_no) const {
	return terms.at(term_no).numberofCredits();
}

void Student::addCourse(Presented_Course* course) {
	terms[course->getTerm_no()].addCourse(course);
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

void Student::setScoreofCourse(Presented_Course* course, float score) {
	terms[course->getTerm_no()].setScoreofCourse(course, score);
}

float Student::getScoreofCourse(Presented_Course* course) const {
	return terms.at(course->getTerm_no()).getCourseProperties(course).getScore();
}

void Student::setStatusofCourse(Presented_Course* course, char status) {
	terms[course->getTerm_no()].setStatusofCourse(course, status);
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

std::string Student::getObjectionReplyTextofCourse(Presented_Course* course) const{
	return terms.at(course->getTerm_no()).getCourseProperties(course).getObjectorReplyText();
}



Tuition_Student::Tuition_Student(char _type)
	: type(_type) {}

void Tuition_Student::setType(char _type) {
	type = _type;
}

char Tuition_Student::getType() const {
	return type;
}

int Tuition_Student::computeTuition(int term_no) {
	return terms[term_no].numberofCredits();// * credit_fee[type] + const_tuition;
}
