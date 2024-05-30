#include "Group.h"

Group::Group()
{}

Group::Group(const Group & other)
{
	copy(other);
}

Group& Group::operator=(const Group& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}

	return *this;
}

Group::~Group()
{
	free();
}

const std::size_t Group::getPeopleCount() const
{
	return this->people.getSize();
}

Group& Group::operator+=(Person& other)
{
	for (std::size_t i = 0; i < getPeopleCount(); i++)
	{
		Person* p = this->people[i];
		if (*p == other)
			return *this;
	}

	this->people.push_back(other.clone());

	return *this;
}

Group Group::operator+(Person& other) const
{
	Group temp = *this;
	return temp += other;
}

Group& Group::operator-=(Person& other)
{
	int index = -1;

	for (std::size_t i = 0; i < getPeopleCount(); i++)
	{
		Person* p = this->people[i];
		if (*p == other)
			index = i;
	}

	if (index == -1)
		return *this;

	Person* p = this->people[index];
	delete p;

	this->people.erase(index);

	return *this;
}

Group Group::operator-(Person& other) const
{
	Group copy = *this;
	return copy -= other;
}

const Person& Group::operator[](const std::size_t identity) const
{
	int index = -1;
	for (std::size_t i = 0; this->getPeopleCount(); i++)
	{
		if (this->people[i]->getIdentification() == identity)
			index = i;
	}

	if (index == -1)
		throw std::invalid_argument("Group: Person not in group");

	return *this->people[index];
}

Person& Group::operator[](const std::size_t identity)
{
	int index = -1;
	for (std::size_t i = 0; i < this->getPeopleCount(); i++)
	{
		if (this->people[i]->getIdentification() == identity)
			index = i;
	}

	if (index == -1)
		throw std::invalid_argument("Group: Person not in group");

	return *this->people[index];
}

void Group::free()
{
	for (std::size_t i = 0; i < this->people.getSize(); i++)
	{
		delete this->people[i];
	}

	this->people.clear();
}

void Group::copy(const Group& other)
{
	for (std::size_t i = 0; i < other.people.getSize(); i++)
	{
		Person* newP = other.people[i]->clone();
		this->people.push_back(newP);
	}
}

const std::size_t Group::operator()() const
{
	return this->getPeopleCount();
}

const bool Group::operator()(Person& other) const
{
	int index = -1;

	for (std::size_t i = 0; i < getPeopleCount(); i++)
	{
		const Person* p = this->people[i];
		if (*p == other)
			index == i;
	}

	return index != -1;
}
