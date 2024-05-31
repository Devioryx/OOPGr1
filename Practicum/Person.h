#pragma once
#include <iostream>
#include <cstring>
#include "Vector.h"

class Person
{
public:

	Person() = default;
	Person(const char* fName, const char* sName, const char* lName, const std::size_t identification);

	const char* getFName() const { return this->fName; }
	const char* getSName() const { return this->sName; }
	const char* getLName() const { return this->lName; }

	const std::size_t getIdentification() const { return identification; }

	bool operator==(const Person& other) const;
	bool operator!=(const Person& other) const;

	void print() const;
private:

	char fName[31];
	char sName[31];
	char lName[31];

	std::size_t identification;

	void setFName(const char* name);
	void setSName(const char* name);
	void setLName(const char* name);

	void setIdentification(const std::size_t identification);
};
