#pragma once
#include "Sound.h"
#include "Silence.h"
#include "FileSound.h"

#include "SoundContainer.h"
#include <fstream>
#include <sstream>

template<typename T>
class Playlist
{
public:
	Playlist(const T& limit, const char* path);

	void print() const;

	const T& getLimit() const { return this->limit; }
private:
	void build(const char* path);

	SoundContainer<T> sounds;
	T limit;
};

template<typename T>
Playlist<T>::Playlist(const T& limit, const char* path)
: limit(limit) {
	build(path);
}

template<typename T>
inline void Playlist<T>::print() const
{
	for (size_t i = 0; i < this->sounds.getSize(); i++)
	{
		std::cout << (*sounds[i]);
	}
}

template<typename T>
inline void Playlist<T>::build(const char* path)
{
	std::ifstream iTxtFile(path);
	if (!iTxtFile)
		throw std::runtime_error("Could not open file!");


	std::size_t soundCount = 0;

	char buffer[1024]{};

	while (iTxtFile && !iTxtFile.eof())
	{
		iTxtFile.getline(buffer, 1024, '\n');
		soundCount++;
	}
	
	iTxtFile.seekg(0, std::ios::beg);

	for (size_t i = 0; i < soundCount; i++)
	{
		std::size_t duration;

		iTxtFile >> duration;

		if (!iTxtFile)
		{
			iTxtFile.clear();
			
			char buffer[1024];
			double coefficient;

			iTxtFile >> buffer >> coefficient;

			FileSound<T> fSound(this->limit, buffer);
			Effect<T, Amplify<T>> fEffect = Effects<T>::amplifyEffect(fSound, coefficient);

			this->sounds.push_back(&fEffect);

			continue;
		}

		this->sounds.push_back(new Silence<T>(this->limit, duration));
	}


}
