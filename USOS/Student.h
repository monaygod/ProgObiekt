#include <utility>


#pragma once
class Student
{
public:
	unsigned int id_;
	std::string first_name_;
	std::string last_name_;
	std::vector<unsigned int> id_subjects_;
	Student(const unsigned int id,std::string first_name, std::string last_name): id_(id), first_name_(std::move(first_name)),
	                                                                                 last_name_(std::move(last_name))
	{
		
	}

	bool add_subject(const unsigned int id)
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
	bool remove_subject(const unsigned int id)
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
};

