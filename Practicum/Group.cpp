#include "Group.h"

const std::size_t Group::getPeopleCount() const
{
	return this->people.getSize();
}

Group& Group::operator+=(const Person& other)
{
	for (std::size_t i = 0; i < getPeopleCount(); i++)
	{
		const Person& p = this->people[i];
		if (p == other)
			return *this;
	}

	this->people.push_back(other);

	return *this;
}

Group Group::operator+(const Person& other) const
{
	Group temp = *this;
	return temp += other;
}

Group& Group::operator-=(const Person& other)
{
	int index = -1;

	for (std::size_t i = 0; i < getPeopleCount(); i++)
	{
		const Person& p = this->people[i];
		if (p == other)
			index = i;
	}

	if (index == -1)
		return *this;

	this->people.erase(index);

	return *this;
}

Group Group::operator-(const Person& other) const
{
	Group copy = *this;
	return copy -= other;
}

const Person& Group::operator[](const std::size_t identity) const
{
	int index = -1;
	for (std::size_t i = 0; this->getPeopleCount(); i++)
	{
		if (this->people[i].getIdentification() == identity)
			index = i;
	}

	if (index == -1)
		throw std::invalid_argument("Group: Person not in group");

	return this->people[index];
}

Person& Group::operator[](const std::size_t identity)
{
	int index = -1;
	for (std::size_t i = 0; i < this->getPeopleCount(); i++)
	{
		if (this->people[i].getIdentification() == identity)
			index = i;
	}

	if (index == -1)
		throw std::invalid_argument("Group: Person not in group");

	return this->people[index];
}

void Group::free()
{
	this->people.clear();
}

void Group::copy(const Group& other)
{
	for (std::size_t i = 0; i < other.people.getSize(); i++)
	{
		this->people.push_back(other.people[i]);
	}
}

const std::size_t Group::operator()() const
{
	return this->getPeopleCount();
}

const bool Group::operator()(const Person& other) const
{
	int index = -1;

	for (std::size_t i = 0; i < getPeopleCount(); i++)
	{
		const Person& p = this->people[i];
		if (p == other)
			index == i;
	}

	return index != -1;
}
