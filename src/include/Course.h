#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "TimeDate.h"
#include "BinaryFile.h"

class Professor;
class Student;

class Course {
protected:
	short department_id;
	short group_id;
	short course_id;
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
	Course(short _department_id, short _group_id, short _course_id, char _credit = 0, std::string _name = "", char _type = -1);
	static std::map<int,Course*>  readAllCourses(void) ;
	void setDepartment_id(short _department_id);
	short getDepartment_id() const;
	void setGroup_id(short _group_id);
	short getGroup_id() const;
	void setCourse_id(short _course_id);
	short getCourse_id() const;
	void setCredit(char _credit);
	char getCredit() const;
	void setName(std::string _name);
	std::string getName() const;
	void setType(char _type);
	char getType() const;
	void setPrerequisites(std::vector<Course*> _prerequisites);
	std::vector<Course*> getPrerequisites() const;
	void addPrerequisite(Course* course);
	void removePrerequisite(Course* course);
	void setCorequisites(std::vector<Course*> _corequisites);
	std::vector<Course*> getCorequisites() const;
	void addCorequisite(Course* course);
	void removeCorequisite(Course* course);
};

class Presented_Course : public Course {
protected:
	Professor* course_professor;
	std::vector<Student*> course_students;
	int capacity;
	int term_no;
	Course_Time course_time;
	std::string course_location;
	Time finalexam_time;
	std::string finalexam_location;
public:
	Presented_Course();
	Presented_Course(Course* course, int _term_no = 0, Professor* _course_professor = nullptr, int _capacity = 0);
	void setCourseProfessor(Professor* _course_professor);
	Professor* getCourseProfessor() const;
	void setCourseStudents(std::vector<Student*> _course_students);
	std::vector<Student*> getCourseStudents() const;
	void addStudent(Student* student);
	void removeStudent(Student* student);
	int getNumberofStudents() const;
	void setCapacity(int _capacity);
	int getCapacity() const;
	void setTerm_no(int _term_no);
	int getTerm_no() const;
	void setCourseTime(Course_Time _course_time);
	Course_Time getCourseTime() const;
	void setCourseLocation(std::string _course_location);
	std::string getCourseLocation() const;
	void setFinalExamTime(Time _finalexam_time);
	Time getFinalExamTime() const;
	void setFinalExamLocation(std::string _finalexam_location);
	std::string getFinalExamLocation() const;
};

#endif // COURSE_H
