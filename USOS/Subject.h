#pragma once
#include "Grades.h"

class Subject
{
public:
	unsigned int id_;
	unsigned int id_lecturer_;
	std::string name_;
	std::string desc_;
	std::vector<unsigned int> id_students_;
	std::vector<std::pair<unsigned int, Grade>> id_grades_;
	
	Subject(const unsigned int id, const unsigned int id_lecturer, std::string name, std::string desc) :
		id_(id),
		name_(std::move(name)),
		desc_(std::move(desc)),
		id_lecturer_(id_lecturer)
	{

	}

	bool add_student(const unsigned int id)
	{
		if (std::count(id_students_.begin(), id_students_.end(), id))
			return false; //jesli juz zapisany to false
		try
		{
			id_students_.emplace_back(id);
		}
		catch (std::exception&)
		{
			return false;
		}
		return true;
	}

	bool remove_student(const unsigned int id)
	{
		if (!std::count(id_students_.begin(), id_students_.end(), id))
			return false; //nie mozna usunac bo go nie ma
		try
		{
			id_students_.erase(std::remove(id_students_.begin(), id_students_.end(), id), id_students_.end());
			id_grades_.erase(std::remove_if(
				id_grades_.begin(), id_grades_.end(),
				[id](const std::pair<unsigned int, Grade>& x) {
				return x.first == id;
			}), id_grades_.end());
		}
		catch (std::exception&)
		{
			return false;
		}
		return true;
	}
	
	bool add_grade(const unsigned int id_student, Grade grade)
	{
		if (!std::count(id_students_.begin(), id_students_.end(), id_student))
			return false; //nie ma studenta z podanym id w tym przedmiocie
		try
		{
			id_grades_.emplace_back(std::make_pair(id_student, grade));
		}
		catch (std::exception&)
		{
			return false;
		}
		return true;
	}
	
	bool remove_grade(const unsigned int id_student, Grade grade)
	{
		try
		{
			id_grades_.erase(std::remove_if(
				id_grades_.begin(), id_grades_.end(),
				[id_student, grade](const std::pair<unsigned int, Grade>& x) {
				return (x.first == id_student) && (x.second == grade);
			}), id_grades_.end());
		}
		catch (std::exception&)
		{
			return false;
		}
		return true;
	}
};

