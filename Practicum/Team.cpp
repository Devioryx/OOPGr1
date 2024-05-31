#include "Team.h"

bool Team::operator()(const Person& p1,const Person& p2)
{
	try
	{
		Person& first = Group::operator[](p1.getIdentification());
		Person& second = Group::operator[](p2.getIdentification());

		Relation relation(first, second);

		relations.push_back(relation);

		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}

}

bool Team::operator>=(const Team& other) const
{
	std::size_t thisEmployerCnt = 0;
	std::size_t otherEmployerCnt = 0;

	Vector<std::size_t> visited;

	for (std::size_t i = 0; i < this->relations.getSize(); i++)
	{
		if (!visited.includes(this->relations[i].employer.getIdentification()))
			visited.push_back(this->relations[i].employer.getIdentification());
	}
	thisEmployerCnt = visited.getSize();

	visited = Vector<std::size_t>();

	for (std::size_t i = 0; i < other.relations.getSize(); i++)
	{
		if (!visited.includes(other.relations[i].employer.getIdentification()))
			visited.push_back(other.relations[i].employer.getIdentification());
	}
	otherEmployerCnt = visited.getSize();

	return thisEmployerCnt >= otherEmployerCnt;
}

bool Team::operator<=(const Team& other) const
{
	std::size_t thisEmployerCnt = 0;
	std::size_t otherEmployerCnt = 0;

	Vector<std::size_t> visited;

	for (std::size_t i = 0; i < this->relations.getSize(); i++)
	{
		if (!visited.includes(this->relations[i].employer.getIdentification()))
			visited.push_back(this->relations[i].employer.getIdentification());
	}
	thisEmployerCnt = visited.getSize();

	visited = Vector<std::size_t>();

	for (std::size_t i = 0; i < other.relations.getSize(); i++)
	{
		if (!visited.includes(other.relations[i].employer.getIdentification()))
			visited.push_back(other.relations[i].employer.getIdentification());
	}
	otherEmployerCnt = visited.getSize();

	return thisEmployerCnt <= otherEmployerCnt;
}

bool Team::operator<(const Team& other) const
{
	return !(*this >= other);
}

bool Team::operator>(const Team& other) const
{
	return !(*this <= other);
}

Team::operator bool() const
{
	return checkCycle();
}

bool Team::checkCycle() const
{
	for (int i = 0; i < relations.getSize(); i++) {
		std::size_t employer = relations[i].employer.getIdentification();
		std::size_t employee = relations[i].employee.getIdentification();

		for (int j = 0; j < relations.getSize(); j++) {
			if (relations[j].employer.getIdentification() == employee) {
				if (relations[j].employee.getIdentification() == employer) {
					return false;
				}
				employee = relations[j].employee.getIdentification();
				j = -1;
			}
		}
	}

	return true;

}

