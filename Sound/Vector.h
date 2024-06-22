#pragma once
#include <iostream>

template<typename T>
class Vector
{
public:
	Vector();
	Vector(const std::size_t capacity);

	Vector(const Vector& other);
	Vector& operator=(const Vector& other);


	~Vector();

	void push_back(const T& other);
	void erase(const std::size_t index);

	const T& operator[](const std::size_t index) const;
	T& operator[](const std::size_t index);

	std::size_t getCapacity() const { return this->capacity; }
	std::size_t getSize() const { return this->size; }
private:
	void free();
	void copy(const Vector& other);

	void resize();

	T* data;
	std::size_t size;
	std::size_t capacity;
};

template<typename T>
inline void Vector<T>::free()
{
	delete[] this->data;
	this->data = nullptr;

	this->capacity = this->size = 0;
}

template<typename T>
inline void Vector<T>::copy(const Vector& other)
{
	this->capacity = other.capacity;

	this->data = new T [other.capacity];

	for (std::size_t i = 0; i < other.size; i++)
	{
		this->data[i] = other.data[i];
		this->size++;
	}
}

template<typename T>
inline void Vector<T>::resize()
{
	std::size_t newCap = this->capacity * 2;

	T* newData = new T[newCap];

	for (std::size_t i = 0; i < this->size; i++)
	{
		newData[i] = this->data[i];
	} 

	delete[] this->data;
	this->data = newData;

	this->capacity = newCap;
}

template<typename T>
inline Vector<T>::Vector()
: data(nullptr), size(0), capacity(2) {
	this->data = new T[this->capacity];
}

template<typename T>
inline Vector<T>::Vector(const std::size_t capacity)
: data(nullptr), size(0), capacity(capacity) {
	this->data = new T[this->capacity];
}

template<typename T>
inline Vector<T>::Vector(const Vector& other)
: data(nullptr)
{
	copy(other);
}

template<typename T>
inline Vector<T>& Vector<T>::operator=(const Vector& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
}

template<typename T>
inline Vector<T>::~Vector()
{
	free();
}

template<typename T>
inline void Vector<T>::push_back(const T& other)
{
	if (this->size == this->capacity)
		resize();

	this->data[this->size] = other;
	this->size++;
}

template<typename T>
inline void Vector<T>::erase(const std::size_t index)
{
	if (index >= this->size)
		throw std::out_of_range("Vector: Invalid Index");

	for (size_t i = index; i < this->size - 1; i++)
	{
		this->data[i] = this->data[i + 1];
	}
	this->size--;
}

template<typename T>
inline const T& Vector<T>::operator[](const std::size_t index) const
{
	if (index >= this->size)
		throw std::out_of_range("Vector: Invalid Index");

	return this->data[index];
}

template<typename T>
inline T& Vector<T>::operator[](const std::size_t index)
{
	if (index >= this->size)
		throw std::out_of_range("Vector: Invalid Index");

	return this->data[index];
}
