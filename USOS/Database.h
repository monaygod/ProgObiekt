#pragma once
#include <string>
#include <vector>

#include "Lecturer.h"
#include "Student.h"
#include "Subject.h"

class Database
{
	std::vector<Lecturer> lecturers;
	std::vector<Student> students;
	std::vector<Subject> subjects;
	
public:
	unsigned int subjects_id_counter;
	unsigned int students_id_counter;
	unsigned int lecturers_id_counter;
	Database()
	{
		lecturers_id_counter = students_id_counter = subjects_id_counter = 0;
	}

	bool add_lecturer(std::string first_name, std::string last_name);

	bool add_student(std::string first_name, std::string last_name);

	bool add_subject(const unsigned int id_lecturer, std::string name, std::string desc);

	bool remove_lecturer(const unsigned int id);

	bool remove_student(const unsigned int id);

	bool remove_subject(const unsigned int id);

	Lecturer& get_lecturer_by_id(const unsigned int id);

	Student& get_student_by_id(const unsigned int id);

	Subject& get_subject_by_id(const unsigned int id);
};

