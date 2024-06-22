#pragma once
#include "Sound.h"
#include "SoundContainer.h"

template<typename T>
class SequenceSound : public Sound<T>
{
public:
	SequenceSound(const T& limit, const SoundContainer<T>& sounds);

	virtual ~SequenceSound() = default;

	virtual Sound<T>* clone() const { return new SequenceSound<T>(*this); }
private:
	void build(const SoundContainer<T>& sounds);
};

template<typename T>
inline SequenceSound<T>::SequenceSound(const T& limit, const SoundContainer<T>& sounds)
: Sound<T>(limit, 0) 
{
	this->build(sounds);
}

template<typename T>
inline void SequenceSound<T>::build(const SoundContainer<T>& sounds)
{
	std::size_t duration = 0;
	for (size_t i = 0; i < sounds.getSize(); i++)
	{
		duration += sounds[i]->getDuration();

		for (size_t j = 0; j < sounds[i]->getDuration(); j++)
		{
			this->samples.push_back(Sample<T>((*sounds[i])[j], this->limit));
		}
	}
	
	this->duration = duration;
}
