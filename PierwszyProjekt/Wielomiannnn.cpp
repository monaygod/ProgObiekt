#include "Wielomiannnn.h"

Wielomiannnn::Wielomiannnn() : n(new int)
{
	*(this->n) = 0;
	this->tablica = nullptr;
}

Wielomiannnn::Wielomiannnn(int _n) : n(new int)
{
	*(this->n) = _n;
	this->tablica = new int[*(this->n)];
}

Wielomiannnn::Wielomiannnn(const int* _tablica, int _n) : n(new int)
{
	*(this->n) = _n;
	this->tablica = new int[*(this->n)];
	for (int i = 0; i < *(this->n); i++)
	{
		this->tablica[i] = _tablica[i];
	}
}

Wielomiannnn::Wielomiannnn(const Wielomiannnn* obj) : n(new int)
{
	*(this->n) = *(obj->n);
	this->tablica = new int[*(this->n)];
	for (int i = 0; i < *(this->n); i++)
	{
		this->tablica[i] = obj->tablica[i];
	}
}
Wielomiannnn::Wielomiannnn(const Wielomiannnn& obj) : n(new int)
{
	*(this->n) = *(obj.n);
	this->tablica = new int[*(this->n)];
	for (int i = 0; i < *(this->n); i++)
	{
		this->tablica[i] = obj.tablica[i];
	}
}

Wielomiannnn::~Wielomiannnn()
{
	delete n;	this->n = nullptr;
	delete[] tablica;	this->tablica = nullptr;
}

Wielomiannnn& Wielomiannnn::operator=(const Wielomiannnn& l_value)
{
	if (this == &l_value)
		return *this;
	delete[]tablica;
	this->n = new int(*(l_value.n));
	memcpy(this->tablica, (l_value.tablica), sizeof(int) * *(l_value.n));
	return *this;	
}

std::string Wielomiannnn::to_string() const
{
	std::string result = std::string("");
	for(int i= *(this->n)-1; i>=0;i--)
	{
		if(this->tablica[i] != 0)
		{
			result += tablica[i] + "x^" + i;
		}
	}
	return result;
}

Wielomiannnn Wielomiannnn::operator+(const Wielomiannnn& l_value) const
{
	bool is_arg_higher = (*(this->n) > * (l_value.n)) ? false : true;
	int new_n = (is_arg_higher) ? *(l_value.n) : *(this->n) ;

	Wielomiannnn result = new Wielomiannnn(new_n);
	memcpy(result.tablica, (is_arg_higher) ? l_value.tablica : (this->tablica), sizeof(int) * new_n);
	for(int i=0;i< (is_arg_higher? *(this->n): *(l_value.n));i++)
	{
		result.tablica += (is_arg_higher) ? this->tablica[i] : l_value.tablica[i];
	}

	return result;
}

Wielomiannnn Wielomiannnn::operator+(const int l_value) const
{
	Wielomiannnn result = new Wielomiannnn(*(this->n));
	memcpy(result.tablica, (this->tablica), sizeof(int) * *(this->n));
	result.tablica[0] += l_value;
	return result;
}

 Wielomiannnn operator+(const int r_value, const Wielomiannnn& l_value)
{
	Wielomiannnn result = new Wielomiannnn(*(l_value.n));
	memcpy(result.tablica, (l_value.tablica), sizeof(int) * *(l_value.n));
	result.tablica[0] += r_value;
	return result;
}

