#pragma once
#include <string>
#include <fstream>

#include "Sound.h"

template<typename T>
class FileSound: public Sound<T>
{
public:
	FileSound(const T& limit, const char* path);

	virtual ~FileSound() = default;

	virtual Sound<T>* clone() const override;

private: 
	void build();

	std::string path;
};

template<typename T>
inline FileSound<T>::FileSound(const T& limit, const char* path)
	: Sound<T>(limit, 0), path(path)
{
	this->build();
}
template<typename T>
inline Sound<T>* FileSound<T>::clone() const
{
	return new FileSound(*this);
}
template<typename T>
inline void FileSound<T>::build()
{
	std::ifstream iFile(path, std::ios::binary);
	if (!iFile)
		throw std::runtime_error("FileSound: Could Not Open File");

	iFile.read(reinterpret_cast<char*>(&this->duration), sizeof(this->duration));
	
	T value{};

	for (size_t i = 0; i < this->duration; i++)
	{
		iFile.read(reinterpret_cast<char*>(&value), sizeof(value));
		this->samples.push_back(Sample<T>(value, this->limit));
	}

	iFile.close();
};
