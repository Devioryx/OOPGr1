#pragma once
#include "Sound.h"
#include "Vector.h"

template<typename T>
class PeriodicSound : public Sound<T>
{
public:
	PeriodicSound(const T& limit, const Vector<T>& samples, const std::size_t number);

	virtual ~PeriodicSound() = default;

	virtual Sound<T>* clone() const override;

private:
	void build(const Vector<T>& samples, const std::size_t number);
};

template<typename T>
inline PeriodicSound<T>::PeriodicSound(const T& limit, const Vector<T>& samples, const std::size_t number)
: Sound<T>(limit, 0)
{
	if (samples.getSize() == 0 || number == 0)
		throw std::invalid_argument("Invalid arguments for periodic sound");

	this->build(samples, number);
}

template<typename T>
inline Sound<T>* PeriodicSound<T>::clone() const
{
	return new PeriodicSound(*this);
}

template<typename T>
inline void PeriodicSound<T>::build(const Vector<T>& samples, const std::size_t number)
{
	for (size_t i = 0; i < number; i++)
	{
		for (size_t j = 0; j < samples.getSize(); j++)
		{
			this->samples.push_back(Sample<T>(samples[j], this->limit));
		}
	}

	this->duration = this->samples.getSize();
}
