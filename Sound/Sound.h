#pragma once
#include "Vector.h"
#include "Sample.hpp"

template<typename T>
class Sound
{
public:
	Sound();
	Sound(const T& limit, const size_t duration);

	Sound& operator = (const Sound & other) = delete;

	virtual ~Sound() = default;
	virtual Sound* clone() const = 0;

	const T& operator[](const std::size_t index) const;

	std::size_t getDuration() const { return this->duration; }
	const T& getLimit() const { return this->limit; }
	const Vector<Sample<T>>& getSamples() const { return this->samples; }

	friend std::ostream& operator<<(std::ostream& stream, const Sound<T>& sound) {
		stream << "The limit of the sound is: " << sound.limit << '\n';
		stream << "The duration of the sound is: " << sound.duration << '\n';

		if (sound.duration > 0) {
			stream << "The samples values in the sound are: ";

			for (std::size_t i = 0; i < sound.duration; ++i) {
				stream << sound[i] << ' ';
			}
		}
		else {
			stream << "The sound has no samples within itself.";
		}
		stream << std::endl;

		return stream;
	}

	void save(const char* path) const;

protected:
	Vector<Sample<T>> samples;

	std::size_t duration;
	T limit;
};

template<typename T>
inline Sound<T>::Sound()
: limit(0), duration(0) {
}

template<typename T>
inline Sound<T>::Sound(const T& limit, const size_t duration)
: limit(limit), duration(duration) {
}

template<typename T>
inline const T& Sound<T>::operator[](const std::size_t index) const
{
	if (index >= this->duration)
		throw std::out_of_range("Sound: Invalid Index For []");

	return this->samples[index].getValue();
}

template<typename T>
inline void Sound<T>::save(const char* path) const
{
	std::ofstream& oFile(path, std::ios::binary);
	if (!oFile)
		throw std::runtime_error("Could not open file!");

	oFile.write(reinterpret_cast<const char*>(&this->duration), sizeof(this->duration));

	for (size_t i = 0; i < this->duration; i++)
	{
		T value = (*this)[i];
		oFile.write(reinterpret_cast<const char*>(&value), sizeof(value));
	}

	oFile.close();
}
