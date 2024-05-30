#include "Person.h"

#pragma warning (disable:4996)

Person::Person(const char* fName, const char* sName, const char* lName, const std::size_t identification)
{
	setIdentification(identification);

	setFName(fName);
	setLName(lName);
	setSName(sName);
}

Person* Person::clone() const
{
	return new Person(*this);
}

bool Person::operator==(const Person& other) const
{
	return this->identification == other.identification;
}

bool Person::operator!=(const Person& other) const
{
	return !(*this == other);
}

void Person::print() const
{
	std::cout << "First Name: " << fName << std::endl;
	std::cout << "Second Name: " << sName << std::endl;
	std::cout << "Last Name: " << lName << std::endl;
	std::cout << "Identification: " << identification << std::endl;

}

void Person::setFName(const char* name)
{
	if (!name || !name[0] || strlen(name) > 30)
		throw std::invalid_argument("Person: Invalid First Name");

	strcpy(this->fName, name);
}

void Person::setSName(const char* name)
{
	if (strlen(name) > 30)
		throw std::invalid_argument("Person: Invalid Second Name");

	if (!name) name = "";

	strcpy(this->sName, name);
}

void Person::setLName(const char* name)
{
	if (!name || !name[0] || strlen(name) > 30)
		throw std::invalid_argument("Person: Invalid Last Name");

	strcpy(this->lName, name);
}

void Person::setIdentification(const std::size_t identification)
{
	if (identification <= 999'999'999 || identification >= 10'000'000'000)
		throw std::invalid_argument("Person: Invalid Identification");

	this->identification = identification;
}

