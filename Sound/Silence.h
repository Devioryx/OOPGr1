#pragma once
#include "Sound.h"

template<typename T>
class Silence: public Sound<T>
{
public:
	Silence(const T& limit, const std::size_t duration);
	
	virtual ~Silence() = default;

	virtual Sound<T>* clone() const;
private:
	void build();
};

template<typename T>
inline Silence<T>::Silence(const T& limit, const std::size_t duration)
: Sound<T>(limit, duration)
{
	this->build();
}

template<typename T>
inline Sound<T>* Silence<T>::clone() const
{
	return new Silence(*this);
}

template<typename T>
inline void Silence<T>::build()
{
	for (std::size_t i = 0; i < this->duration; i++)
	{
		this->samples.push_back(Sample<T>(0, this->limit));
	}
}
