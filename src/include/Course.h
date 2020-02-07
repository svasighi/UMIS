#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "TimeDate.h"

class Professor;
class Student;

class Course {
protected:
	short departmentcode;
	short groupcode;
	short coursecode;
	char credit;
	std::string name;
	char type;
	// type:
	//-1 : unknown
	// 0 : core(basic) course
	// 1 : general course
	// 2 : required(main) course
	// 3 : Specialized course
	// 4 : elective(optional) course
	std::vector<Course*> prerequisites;
	std::vector<Course*> corequisites;
public:
	Course();
	Course(short _departmentcode, short _groupcode, short _coursecode, char _credit = 0, std::string _name = "", char _type = -1);
	void setDepartmentCode(short _departmentcode);
	short getDepartmentCode() const;
	void setGroupCode(short _groupcode);
	short getGroupCode() const;
	void setCourseCode(short _coursecode);
	short getCourseCode() const;
	void setCredit(char _credit);
	char getCredit() const;
	void setName(std::string _name);
	std::string getName() const;
	void setType(char _type);
	char getType() const;
	void setPrerequisites(const std::vector<Course*>& _prerequisites);
	std::vector<Course*> getPrerequisites() const;
	void addPrerequisite(Course* course);
	void removePrerequisite(Course* course);
	void setCorequisites(const std::vector<Course*>& _corequisites);
	std::vector<Course*> getCorequisites() const;
	void addCorequisite(Course* course);
	void removeCorequisite(Course* course);
	bool haveSameID(Course* course) const;
	bool searchSameIDin(const std::vector<Course*>&) const;
	int getCourseID() const;
};

class PresentedCourse : public Course {
protected:
	int term_no;
	char group_no;
	Professor* course_professor;
	std::vector<Student*> course_students;
	int capacity;
	int enrolled_number;
	int waiting_number;
	CourseTime course_time;
	std::string course_location;
	ExamTime finalexam_time;
	std::string finalexam_location;
public:
	PresentedCourse();
	PresentedCourse(Course* course, int _term_no = 0, char _group_no = 0, Professor* _course_professor = nullptr, int _capacity = 0);
	void setTerm_no(int _term_no);
	int getTerm_no() const;
	void setGroup_no(char _group_no);
	char getGroup_no() const;
	void setCourseProfessor(Professor* _course_professor);
	Professor* getCourseProfessor() const;
	void setCourseStudents(const std::vector<Student*>& _course_students);
	std::vector<Student*> getCourseStudents() const;
	void addStudent(Student* student);
	void removeStudent(Student* student);
	int getNumberofStudents() const;
	int getNumberofStudentsWithCourseStatus(char _status) const;
	void setCapacity(int _capacity);
	int getCapacity() const;
	void updateEnrolledAndWaitingNumbers();
	void setEnrolledNumber(int _enrolled_number);
	void addEnrolledNumber(int = 1);
	int getEnrolledNumber() const;
	void setWaitingNumber(int _waiting_number);
	void addWaitingNumber(int = 1);
	int getWaitingNumber() const;
	void enrollFirstStudentWaiting(int = 1);
	void removeLastStudentEnrolled(int = 1);
	void removeAllWaitingStudents();
	void setCourseTime(const CourseTime& _course_time);
	CourseTime getCourseTime() const;
	void setCourseLocation(std::string _course_location);
	std::string getCourseLocation() const;
	void setFinalExamTime(const ExamTime& _finalexam_time);
	ExamTime getFinalExamTime() const;
	void setFinalExamLocation(std::string _finalexam_location);
	std::string getFinalExamLocation() const;
	bool isSameWith(PresentedCourse* course) const;
	int getPresentedCourseID() const;
};

#endif // COURSE_H
