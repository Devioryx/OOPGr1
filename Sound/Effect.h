#pragma once
#include "Sound.h"

template<typename T, typename Functor>
class Effect : public Sound<T>
{
public:
	Effect(const Sound<T>& sound, const Functor& func);
	
	const Functor& getFunc() const { return this->func; }

	virtual ~Effect() = default;

	virtual Sound<T>* clone() const { return new Effect(*this); }
private:
	void build(const Sound<T>& sound);

	const Functor& func;
};

template<typename T, typename Functor>
inline Effect<T, Functor>::Effect(const Sound<T>& sound, const Functor& func)
: Sound<T>(sound.getLimit(), sound.getDuration()), func(func) 
{
	this->build(sound);
}

template<typename T, typename Functor>
inline void Effect<T, Functor>::build(const Sound<T>& sound)
{
	for (size_t i = 0; i < this->duration; i++)
	{
		this->samples.push_back(func(sound.getSamples()[i], i));
	}
}
