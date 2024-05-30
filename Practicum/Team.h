#pragma once
#include "Group.h"

struct Relation
{
	Person employer;
	Person employee;

	Relation() = default;
	Relation(const Person& employer, const Person& employee) : employer(employer), employee(employee) {}
};


class Team : public Group
{
public:
	bool operator()(Person& p1, Person& p2);

	bool operator > (const Team& other) const;
	bool operator < (const Team& other) const;


	operator bool();

private:
	Vector<Relation> relations;

	void checkCycle(Vector<std::size_t>& visited);
};

