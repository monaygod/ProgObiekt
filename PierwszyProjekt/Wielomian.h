/*
Napisaæ klasê Wielomian, która dzia³a na dowolnych(podstawowych)
typach, czyli ma byæ w postaci szablonu, która zawiera przeci¹¿enia
takich operatorow jak :
+, -, *, >> , << , =, == , +=, -=, *=
konstruktory :
	kopiuj¹cy,
	z parametrami :
a)* tmp, int,
b) string(lub char*) w który wpisujemy wielomian w postaci stringu np
"3x^5+4x^10*2x^2+1", parsuje go i tworzy odpowiedni¹ reprezentacjê
Metody zapisuj¹ce wielomian do pliku i odczytuj¹ce.

dzielenie przez dwumian i wyliczanie wartoœci wielomianu HORNER
*/

#pragma once
#include <cassert>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>


template <typename  T> class Wielomian
{
private:
	size_t size_;
	T* ptr_;

public:
	//Konstruktory
	Wielomian() : size_(0), ptr_(nullptr) {}
	Wielomian(const Wielomian& _copy) : size_(_copy.size_), ptr_(new T[size_]) { memcpy(ptr_, _copy.ptr_, sizeof(T) * size_); std::cout << "Konstruktor kopiujacy " << size_ << std::endl; }
	Wielomian(T* _tmp, size_t _size) : size_(_size), ptr_(new T[size_]) { memcpy(ptr_, _tmp, sizeof(T) * size_); }
	Wielomian(const std::string& str) : size_(0), ptr_(nullptr) { from_string(str, &size_, ptr_); }
	~Wielomian() { delete[] ptr_; }

	void test() const { std::cout << typeid(size_).name(); }
	std::string to_string()
	{
		std::cout << "To string_" << size_ << std::endl;
		std::stringstream result;
		for (size_t i = size_; i > 1; i--)
		{
			if (ptr_[i - 1] != 0.0)
				result << std::showpos << ptr_[i - 1] << "x^" << i - 1;
		}
		if (ptr_ && ptr_[0] != 0.0)
			result << std::showpos << ptr_[0];

		return result.str();
	}
	static void from_string(const std::string& _str, size_t* _size, T*& _dest_ptr) {
		std::string str = _str;
		size_t str_size = str.size();
		std::vector<std::string> temp;
		std::vector<T> temp_coeff;
		std::vector<size_t> temp_expon;
		int max_expon = 0;

		if (str.empty())
		{
			*(_size) = 0;
			_dest_ptr = nullptr;
			return;
		}
		for (size_t i = 0; i < str_size; i++)
		{
			if (str[i] != '+' && str[i] != '-' && str[i] != '^' && str[i] != '.' && str[i] != 'x' && (str[i] < '0' || str[i] > '9'))
			{
				throw std::invalid_argument("String contains forbidden symbols");
			}
		}
		if (isdigit(str[0])) str.insert(0, "+");
		if (str[0] == 'x') str.insert(0, "+");
		str.append("+");
		str_size = str.size();
		{
			size_t j = 0;
			for (size_t i = 1; i < str_size; ++i)
				if (str[i] == '+' || str[i] == '-')
				{
					temp.push_back(str.substr(j, i - j));
					j = i;
				}

		}
		for (auto& i : temp)
		{
			if (i[1] == 'x')
				i.insert(1, "1");
			auto flag = false;
			const auto len = i.size();
			for (size_t j = 1; j < len; j++)
				if (i[j] == 'x')
				{
					flag = true;
					if (j == len - 1)
						i.append("^1");
					break;
				}
			if (!flag)
				i.append("x^0");
		}
		for (auto i : temp)
		{
			int expon = -1;
			for (size_t j = 0; j < i.size(); j++)
			{
				if (i[j] == '^')
				{
					expon = std::stoi(i.substr(j + 1, i.size() - j));
					break;
				}
			}
			if (expon > max_expon)
				max_expon = expon;
		}
		*(_size) = max_expon + 1;
		_dest_ptr = new T[*(_size)];

		for (size_t i = 0; i < *(_size); i++)
		{
			_dest_ptr[i] = 0;
		}

		for (auto i : temp)
		{
			for (size_t j = 0; j < i.size(); j++)
			{
				if (i[j] == '^')
				{
					_dest_ptr[std::stoi(i.substr(j + 1, i.size() - j))] = T(std::stod(i.substr(0, j)));
					break;
				}
			}
		}
	}
	Wielomian<T>& shortening()
	{
		std::cout << "shortening " << size_ << std::endl;
		size_t new_size = size_ - 1;
		if ((*this)[new_size] != 0)	return (*this);

		while ((*this)[new_size] == 0 && new_size) new_size--;

		auto* temp = ptr_;
		size_ = new_size + 1;
		ptr_ = new T[size_];
		memcpy(ptr_, temp, sizeof(T) * (size_));
		delete temp;

		return (*this);
	}
	bool read_from_file(const std::string& file_name, const size_t line_number, const std::string& path_to_file = "./")
	{
		const std::string fullpath = path_to_file + file_name;
		std::ifstream ifs(fullpath);
		if (ifs.is_open()) {
			size_t i = 0;
			std::string line_string;
			// ReSharper disable once CppPossiblyErroneousEmptyStatements
			while (i < line_number && std::getline(ifs, line_string));
			if (i == line_number)
			{
				std::getline(ifs, line_string);
				from_string(line_string, &size_, ptr_);
			}
			return true;
		}
		else {
			throw std::invalid_argument("cant open file");
			return false;
		}
	}
	bool save_to_file(const std::string& file_name, bool append = false, const std::string& path_to_file = "./")
	{
		const std::string fullpath = path_to_file + file_name;
		std::ofstream ifs(fullpath, std::fstream::in | std::fstream::out | (append ? std::fstream::app : std::fstream::trunc));
		if (ifs.is_open()) {
			ifs << this->to_string() << "\n";
			return true;
		}
		else {
			throw std::invalid_argument("cant open file");
			return false;
		}
	}


	T operator[](size_t i) const { assert(i < size_); return ptr_[i]; }
	T& operator[](size_t i) { assert(i < size_); return ptr_[i]; }
	Wielomian<T> operator+(const Wielomian<T>& w)
	{
		const bool is_arg_higher = (size_ > w.size_) ? false : true;
		if (is_arg_higher) {
			Wielomian<T> result(w.ptr_, w.size_);
			for (size_t i = 0; i < size_; i++)
			{
				result[i] += (*this)[i];
			}
			return result.shortening();
		}
		else {
			Wielomian<T> result(ptr_, size_);
			for (size_t i = 0; i < w.size_; i++)
			{
				result[i] += w[i];
			}
			return result.shortening();
		}

	}
	Wielomian<T>& operator+=(const Wielomian<T>& w)
	{
		const bool is_arg_higher = (size_ > w.size_) ? false : true;
		if (is_arg_higher) {
			auto* temp = ptr_;
			//if (ptr_) delete ptr_;
			ptr_ = new T[w.size_];
			memcpy(ptr_, w.ptr_, sizeof(T) * size_);
			Wielomian<T> result(w.ptr_, w.size_);
			for (size_t i = 0; i < size_; i++)
			{
				(*this)[i] += temp[i];
			}
			size_ = w.size_;
			delete temp;
		}
		else {
			for (size_t i = 0; i < w.size_; i++)
			{
				(*this)[i] += w[i];
			}
		}
		return (*this).shortening();
	}
	Wielomian<T> operator-(const Wielomian<T>& w)
	{
		const bool is_arg_higher = (size_ > w.size_) ? false : true;
		if (is_arg_higher) {
			Wielomian<T> result(w.ptr_, w.size_);
			for (size_t i = 0; i < size_; i++)
			{
				result[i] *= (-1);
				result[i] += (*this)[i];
			}
			return result.shortening();
		}
		else {
			Wielomian<T> result(ptr_, size_);
			for (size_t i = 0; i < w.size_; i++)
			{
				result[i] -= w[i];
			}
			return result.shortening();
		}
	}
	Wielomian<T>& operator-=(const Wielomian<T>& w)
	{
		const bool is_arg_higher = (size_ > w.size_) ? false : true;
		if (is_arg_higher) {
			auto* temp = ptr_;
			//if (ptr_) delete ptr_;
			ptr_ = new T[w.size_];
			memcpy(ptr_, w.ptr_, sizeof(T) * size_);
			Wielomian<T> result(w.ptr_, w.size_);
			for (size_t i = 0; i < size_; i++)
			{
				(*this)[i] -= temp[i];
			}
			size_ = w.size_;
			delete temp;
		}
		else {
			for (size_t i = 0; i < w.size_; i++)
			{
				(*this)[i] -= w[i];
			}
		}
		return (*this).shortening();
	}
	Wielomian<T> operator*(const Wielomian<T>& w)
	{
		auto new_size = this->size_ + w.size_ - 1;

		T* temp = new T[new_size];
		//for (T& asd : temp) asd = 0;		czemu nie dzia³a?
		for (size_t i = 0; i < new_size; i++) temp[i] = 0;


		for (size_t i = 0; i < size_; i++)
		{
			for (size_t j = 0; j < w.size_; j++)
			{
				temp[i + j] += (*this)[i] * w[j];
			}
		}
		return Wielomian<T>(temp, new_size).shortening();
	}
	Wielomian<T>& operator*=(const Wielomian<T>& w)
	{
		auto new_size = this->size_ + w.size_ - 1;

		auto* temp = ptr_;
		if (ptr_) delete ptr_;
		ptr_ = new T[new_size];
		for (size_t i = 0; i < new_size; i++) ptr_[i] = 0;

		for (size_t i = 0; i < size_; i++)
		{
			for (size_t j = 0; j < w.size_; j++)
			{
				ptr_[i + j] += temp[i] * w[j];
			}
		}
		size_ = new_size;
		return (*this).shortening();
	}
	Wielomian<T>& operator=(const Wielomian<T>& w)  // NOLINT(bugprone-unhandled-self-assignment)
	{
		if (this != &w) {
			if (ptr_) delete ptr_;
			size_ = w.size_;
			ptr_ = new T[size_];
			memcpy(ptr_, w.ptr_, sizeof(T) * size_);
		}
		return (*this).shortening();
	}
	template <typename Y>
	bool operator==(const Wielomian<Y>& w)
	{
		if (!std::is_convertible<T, Y>::value && !std::is_convertible<Y, T>::value) return false;
		if (size_ != w.size_) return false;

		if (std::is_convertible<T, Y>::value)
			for (size_t i = 0; i < size_; i++)
			{
				if (static_cast<Y>((*this)[i]) != w[i]) return false;
			}
		else
			for (size_t i = 0; i < size_; i++)
			{
				if ((*this)[i] != static_cast<T>(w[i])) return false;
			}
		return true;
	}
	static Wielomian<T> horner_dzielenie(const Wielomian<T>& w, const T& b)
	{
		if(w.size_ < 2) throw std::invalid_argument("za ma³y wielomian");
		else if(w.size_ == 2)
		{
			T* result = new T[1];
			result[0] = w[1];
			Wielomian<T> temp(result, 1);
			delete[] result;
			if (((-b) * w[1] + w[0]) == 0) 
				return temp;
			return Wielomian<T>();  //pusty wielomian
		}
		T* result = new T[w.size_-1];
		result[w.size_-2] = w[w.size_ - 1];
		for(size_t i = w.size_-2; i>0; i--)
		{
			result[i-1] = result[i] * (-b) + w[i];
			std::cout << result[i-1];
		}		
		Wielomian<T> temp(result, w.size_-1);
		if ((-b) * result[0] + w[0] == 0) {
			delete[] result;
			return temp;
		}
		delete[] result;
		return Wielomian<T>();  //pusty wielomian		
	}
	T horner_wartosc(const T& value)
	{
		if (size_ == 0) return 0;

		return horner_rek(value, 0);
	}
private:
	T horner_rek(const T& value, const size_t& lap)
	{
		if (lap == size_-1)
			return ptr_[size_ - 1];

		return value * horner_rek(value, lap + 1) + ptr_[lap];
	}
public:
	
	friend std::ostream& operator <<(std::ostream& o, const Wielomian<T>& w)
	{
		return o << w.to_string();
	}
	friend std::istream& operator >>(std::istream& o, Wielomian<T>& w) {
		std::string wielomian_string("");
		o >> wielomian_string;
		if (w.ptr_) delete w.ptr_;
		from_string(wielomian_string, &(w.size_), w.ptr_);
		return o;
	}

};

