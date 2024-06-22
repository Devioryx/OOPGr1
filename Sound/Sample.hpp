#pragma once
#include <iostream>
#include <cmath>

template<typename T>
class Sample
{
public:
	Sample();
	Sample(const T& value, const T& limit);

	const T& getValue() const { return this->value; }
	const T& getLimit() const { return this->limit; }


private:
	void clip();

	T value;
	T limit;
};

template<typename T>
inline Sample<T>::Sample()
: value(0), limit(0) {
}

template<typename T>
inline Sample<T>::Sample(const T& value, const T& limit)
: value(value), limit(std::fabs(limit))
{
	this->clip();
}

template<typename T>
inline void Sample<T>::clip()
{
	if (this->value < -this->limit) {
		this->value = -this->limit;
	}
	else if (this->value > this->limit) {
		this->value = this->limit;
	}
}
