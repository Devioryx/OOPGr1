#pragma once
#include "Vector.h"
#include "Person.h"

class Group
{
public:
	Group();
	Group(const Group& other);
	Group& operator=(const Group& other);

	~Group();

	const std::size_t getPeopleCount() const;

	Group& operator+=(Person& other);
	Group operator+(Person& other) const;


	Group& operator-=(Person& other);
	Group operator-(Person& other) const;

	const Person& operator[](const std::size_t identity) const;
	Person& operator[](const std::size_t identity);

	const std::size_t operator()() const;
	const bool operator()(Person& other) const;

protected:
	Vector<Person*> people;

private:
	void free();
	void copy(const Group& other);
};

