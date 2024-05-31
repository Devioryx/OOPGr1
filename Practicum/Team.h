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
	bool operator()(const Person& p1,const Person& p2);

	bool operator >= (const Team& other) const;
	bool operator <= (const Team& other) const;

	bool operator > (const Team& other) const;
	bool operator < (const Team& other) const;


	operator bool() const;

private:
	Vector<Relation> relations;

	bool checkCycle() const;
};

