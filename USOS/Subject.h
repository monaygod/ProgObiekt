#pragma once
#include "Grades.h"

#include <string>
#include <vector>
class Subject
{
public:
	unsigned int id_;
	unsigned int id_lecturer_;
	std::string name_;
	std::string desc_;
	std::vector<unsigned int> id_students_;
	std::vector<std::pair<unsigned int, Grade>> id_grades_;

	Subject(const unsigned int id, const unsigned int id_lecturer, std::string name, std::string desc);

	bool add_student(const unsigned int id);

	bool remove_student(const unsigned int id);

	bool add_grade(const unsigned int id_student, Grade grade);

	bool remove_grade(const unsigned int id_student, Grade grade);
};

