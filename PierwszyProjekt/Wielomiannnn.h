#pragma once
#include <string>

class Wielomiannnn
{
private:
	int* n;
	int* tablica;

public:
	Wielomiannnn();
	Wielomiannnn(int);
	Wielomiannnn(const int *, int);
	Wielomiannnn(const Wielomiannnn*);
	Wielomiannnn(const Wielomiannnn&);
	~Wielomiannnn();

	Wielomiannnn& operator= (const Wielomiannnn&);
	[[nodiscard]] std::string to_string() const;
	Wielomiannnn operator+ (const Wielomiannnn&) const;
	Wielomiannnn operator+ (const int) const;

	friend Wielomiannnn operator+(const int, const Wielomiannnn&);

};

