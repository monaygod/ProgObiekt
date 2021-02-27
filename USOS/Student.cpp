#include "Student.h"

Student::Student(const unsigned id, std::string first_name, std::string last_name):
	id_(id), first_name_(std::move(first_name)),
	last_name_(std::move(last_name))
{
}

bool Student::add_subject(const unsigned id)
{
	if (std::count(id_subjects_.begin(), id_subjects_.end(), id))
		return false;
	try
	{
		id_subjects_.emplace_back(id);
	}
	catch (std::exception&)
	{
		return false;
	}
	return true;
}

bool Student::remove_subject(const unsigned id)
{
	try
	{
		id_subjects_.erase(std::remove(id_subjects_.begin(), id_subjects_.end(), id), id_subjects_.end());
	}
	catch (std::exception&)
	{
		return false;
	}
	return true;
}
