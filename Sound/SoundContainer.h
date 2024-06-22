#pragma once
#include "Sound.h"

template<typename T>
class SoundContainer
{
public:
	SoundContainer();
	SoundContainer(const std::size_t capacity);

	SoundContainer(const SoundContainer<T>& other);
	SoundContainer& operator=(const SoundContainer<T>& other);

	~SoundContainer();

	void push_back(const Sound<T>* sound);
	void erase(const std::size_t index);

	const Sound<T>* operator[](const std::size_t index) const { return this->data[index]; };
	Sound<T>* operator[](const std::size_t index) { return this->data[index]; };

	std::size_t getCapacity() const { return this->capacity; }
	std::size_t getSize() const { return this->size; }
private:
	void free();
	void copy(const SoundContainer& other);

	void resize();
	Sound<T>** data;
	std::size_t size;
	std::size_t capacity;
};

template<typename T>
inline SoundContainer<T>::SoundContainer()
: data(nullptr), size(0), capacity(2) {
	data = new Sound<T> * [this->capacity];
}

template<typename T>
inline SoundContainer<T>::SoundContainer(const std::size_t capacity)
: data(nullptr), size(0), capacity(capacity) {
	data = new Sound<T>  * [this->capacity];
}

template<typename T>
inline SoundContainer<T>::SoundContainer(const SoundContainer<T>& other)
: data(nullptr) {
	copy(other);
}

template<typename T>
inline SoundContainer<T>& SoundContainer<T>::operator=(const SoundContainer<T>& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

template<typename T>
inline SoundContainer<T>::~SoundContainer()
{
	free();
}

template<typename T>
inline void SoundContainer<T>::push_back(const Sound<T>* sound)
{
	if (this->size >= this->capacity)
		resize();

	this->data[this->size] = sound->clone();
	this->size++;
}

template<typename T>
inline void SoundContainer<T>::erase(const std::size_t index)
{
	for (size_t i = index; i < this->size-1; i++)
	{
		this->data[i] = this->data[i + 1];
	}

	this->size--;
}

template<typename T>
inline void SoundContainer<T>::free()
{
	for (size_t i = 0; i < this->size; i++)
	{
		delete this->data[i];
	}

	delete[] this->data;
}

template<typename T>
inline void SoundContainer<T>::copy(const SoundContainer& other)
{
	this->data = new Sound<T>  * [other.capacity];

	try
	{
		for (size_t i = 0; i < other.size; i++)
		{
			this->data[i] = other.data[i]->clone();
			this->size++;
		}
	}
	catch (const std::exception&)
	{
		free();
		throw;
	}

	this->capacity = other.capacity;
}

template<typename T>
inline void SoundContainer<T>::resize()
{
	std::size_t newCap = this->capacity * 2;

	Sound<T>** newData = new Sound<T>  * [newCap];

	for (size_t i = 0; i < this->size; i++)
	{
		newData[i] = this->data[i];
	}

	delete[] this->data;
	this->data = newData;

	this->capacity = newCap;
}
