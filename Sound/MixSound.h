#pragma once
#include "Sound.h"
#include "SoundContainer.h"

template<typename T>
class MixSound: public Sound<T>
{
public:
	MixSound(const T& limit, const SoundContainer<T>& sounds);

	virtual ~MixSound() = default;

	virtual Sound<T>* clone() const override;
private:
	void build(const SoundContainer<T>& sounds);
};

template<typename T>
inline MixSound<T>::MixSound(const T& limit, const SoundContainer<T>& sounds)
: Sound<T>(limit, 0) {
	this->build(sounds);
}

template<typename T>
inline Sound<T>* MixSound<T>::clone() const
{
	return new MixSound(*this);
}

template<typename T>
inline void MixSound<T>::build(const SoundContainer<T>& sounds)
{
	std::size_t maxDuration = 0;
	for (size_t i = 0; i < sounds.getSize(); i++)
	{
		maxDuration = maxDuration < sounds[i]->getDuration() ? sounds[i]->getDuration() : maxDuration;
	}

	for (std::size_t i = 0; i < maxDuration; i++)
	{
		T value = 0;

		for (std::size_t j = 0; j < sounds.getSize(); j++)
		{
			if (i >= sounds[j]->getDuration())
				break;

			value += (*sounds[j])[i];
		}

		this->samples.push_back(Sample<T>(value / sounds.getSize(), this->limit));

		this->duration = maxDuration;
	}
}
