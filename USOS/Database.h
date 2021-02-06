#pragma once
#include <vector>

#include "Lecturer.h"
#include "Student.h"
#include "Subject.h"

class Database
{
	unsigned int lecturers_id_counter;
	std::vector<Lecturer> lecturers;
	unsigned int students_id_counter;
	std::vector<Student> students;
	unsigned int subjects_id_counter;
	std::vector<Subject> subjects;
	
public:
	Database()
	{
		lecturers_id_counter = students_id_counter = subjects_id_counter = 0;
	}

	bool add_lecturer(std::string first_name, std::string last_name)
	{
		try
		{
			lecturers.emplace_back(++lecturers_id_counter, first_name, last_name);
		}
		catch (std::exception&)
		{
			return false;
		}
		return true;
	}

	bool add_student(std::string first_name, std::string last_name)
	{
		try
		{
			students.emplace_back(++students_id_counter, first_name, last_name);
		}
		catch (std::exception&)
		{
			return false;
		}
		return true;
	}

	bool add_subject(const unsigned int id_lecturer, std::string name, std::string desc)
	{
		try
		{
			subjects.emplace_back(++subjects_id_counter, id_lecturer, name, desc);
		}
		catch (std::exception&)
		{
			return false;
		}
		return true;
	}

	bool remove_lecturer(const unsigned int id)
	{
		try
		{			
			lecturers.erase(std::remove_if(
				lecturers.begin(), lecturers.end(),
				[id](const Lecturer& x) {
				return x.id_ == id;
			}), lecturers.end());
			//TODO
		}
		catch (std::exception&)
		{
			return false;
		}
		return true;
	}

	bool remove_student(const unsigned int id)
	{
		try
		{
			//TODO
		}
		catch (std::exception&)
		{
			return false;
		}
		return true;
	}

	bool remove_subject(const unsigned int id)
	{
		try
		{
			//TODO
		}
		catch (std::exception&)
		{
			return false;
		}
		return true;
	}
			
	Lecturer& get_lecturer_by_id(const unsigned int id)
	{
		return *std::find_if(lecturers.begin(), lecturers.end(),[id](const Lecturer& x) {return x.id_ == id; });
	}

	Student& get_student_by_id(const unsigned int id)
	{
		return *std::find_if(students.begin(), students.end(), [id](const Student& x) {return x.id_ == id; });
	}

	Subject& get_subject_by_id(const unsigned int id)
	{
		return *std::find_if(subjects.begin(), subjects.end(), [id](const Subject& x) {return x.id_ == id; });
	}



	


	
};

