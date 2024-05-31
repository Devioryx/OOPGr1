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

	Group& operator+=(const Person& other);
	Group operator+(const Person& other) const;


	Group& operator-=(const Person& other);
	Group operator-(const Person& other) const;

	const Person& operator[](const std::size_t identity) const;
	Person& operator[](const std::size_t identity);

	const std::size_t operator()() const;
	const bool operator()(const Person& other) const;

protected:
	Vector<Person> people;

private:
	void free();
	void copy(const Group& other);
};

