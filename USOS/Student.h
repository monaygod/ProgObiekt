#include <string>
#include <utility>
#include <vector>


#pragma once
class Student
{
public:
	unsigned int id_;
	std::string first_name_;
	std::string last_name_;
	std::vector<unsigned int> id_subjects_;
	Student(const unsigned int id, std::string first_name, std::string last_name);

	bool add_subject(const unsigned int id);

	bool remove_subject(const unsigned int id);
};

