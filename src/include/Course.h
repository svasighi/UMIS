#ifndef Course_H
#define Course_H

#include <string>
#include <vector>
#include "Professor.h"
#include "TimeDate.h"

class Course {
protected:
	short credit;
	std::string name;
	short type;
	std::vector<Course*> prerequisite;
	std::vector<Course*> corequisite;
public:
	Course();
	void setCredit(short _credit);
	short getCredit() const;
	void setName(std::string _name);
	std::string getName() const;
	void setType(short _type);
	short getType() const;
	void setPrerequisite(std::vector<Course*> _prerequisite);
	void addPrerequisite(Course* course);
	std::vector<Course*> getPrerequisite() const;
	void setCorequisite(std::vector<Course*> _corequisite);
	void addCorequisite(Course* course);
	std::vector<Course*> getCorequisite() const;
};

class Presented_Course : public Course {
protected:
	Professor* course_professor;
	int capacity;
	int term_no;
	Course_Time course_time;
	std::string course_location;
	Time finalexam_time;
public:
	Presented_Course();
	void setCourseProfessor(Professor* _course_professor);
	Professor* getCourseProfessor() const;
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
};

#endif // Course_H
