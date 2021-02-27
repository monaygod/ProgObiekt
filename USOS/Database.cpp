
#include "Database.h"

bool Database::add_lecturer(std::string first_name, std::string last_name)
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

bool Database::add_student(std::string first_name, std::string last_name)
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

bool Database::add_subject(const unsigned id_lecturer, std::string name, std::string desc)
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

bool Database::remove_lecturer(const unsigned id)
{
	try
	{
		Lecturer& wykladowca = get_lecturer_by_id(id);
		for(auto id_subject : wykladowca.id_subjects_)
		{
			Subject& subject = get_subject_by_id(id_subject);
			subject.id_lecturer_ = 0;
		}
		lecturers.erase(std::remove_if(
			                lecturers.begin(), lecturers.end(),
			                [id](const Lecturer& x)
			                {
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

bool Database::remove_student(const unsigned id)
{
	try
	{
		Student& student = get_student_by_id(id);
		for (auto id_subject : student.id_subjects_)
		{
			Subject& przedmiot = get_subject_by_id(id_subject);
			przedmiot.id_students_.erase(std::remove_if(
				przedmiot.id_students_.begin(), przedmiot.id_students_.end(),
				[id_subject](const unsigned int& x)
			{
				return x == id_subject;
			}), przedmiot.id_students_.end());
		}
		students.erase(std::remove_if(
			students.begin(), students.end(),
					[id](const Student& x)
						{
							return x.id_ == id;
						}), students.end());
	}
	catch (std::exception&)
	{
		return false;
	}
	return true;
}

bool Database::remove_subject(const unsigned id)
{
	try
	{
		Subject& przedmiot = get_subject_by_id(id);
		Lecturer& wykladowca = get_lecturer_by_id(przedmiot.id_lecturer_);
		wykladowca.id_subjects_.erase(std::remove_if(
			wykladowca.id_subjects_.begin(), wykladowca.id_subjects_.end(),
			[id](const unsigned int& x)
		{
			return x == id;
		}), wykladowca.id_subjects_.end());
		for (auto id_student : przedmiot.id_students_)
		{
			Student& student = get_student_by_id(id_student);
			student.id_subjects_.erase(std::remove_if(
				student.id_subjects_.begin(), student.id_subjects_.end(),
				[id](const unsigned int& x)
			{
				return x == id;
			}), student.id_subjects_.end());
		}		
		subjects.erase(std::remove_if(
			subjects.begin(), subjects.end(),
			[id](const Subject& x)
		{
			return x.id_ == id;
		}), subjects.end());
	}
	catch (std::exception&)
	{
		return false;
	}
	return true;
}

Lecturer& Database::get_lecturer_by_id(const unsigned id)
{
	if (id == 0)
		return *(new Lecturer(0, "brak", "brak"));
	return *std::find_if(lecturers.begin(), lecturers.end(), [id](const Lecturer& x) { return x.id_ == id; });
}

Student& Database::get_student_by_id(const unsigned id)
{
	if (id == 0)
		return *(new Student(0, "brak", "brak"));
	return *std::find_if(students.begin(), students.end(), [id](const Student& x) { return x.id_ == id; });
}

Subject& Database::get_subject_by_id(const unsigned id)
{
	if (id == 0)
		return *(new Subject(0, 0, "brak", "brak"));
	return *std::find_if(subjects.begin(), subjects.end(), [id](const Subject& x) { return x.id_ == id; });
}
