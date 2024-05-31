#pragma once
#include <iostream>

template<typename T>
class Vector
{
public:
	Vector();
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);

	~Vector();

	void push_back(const T& p);
	void erase(const std::size_t index);

	const T& operator[](const std::size_t index) const;
	T& operator[](const std::size_t index);

	const std::size_t getSize() const { return this->size; }
	const std::size_t getCapacity() const { return this->capacity; }

	bool includes(const T& other) const;

	void clear();
private:
	void free();
	void copy(const Vector& other);

	void resize();

	T* data;
	std::size_t capacity; 
	std::size_t size;
};


template<typename T>
inline bool Vector<T>::includes(const T& other) const
{
	for (std::size_t i = 0; i < this->size; i++)
	{
		if (this->data[i] == other)
			return true;
	}

	return false;
}

template<typename T>
void Vector<T>::clear()
{
	delete[] this->data;
	this->data = nullptr;

	this->size = this->capacity = 0;
}

template<typename T>
void Vector<T>::free()
{
	delete[] this->data;
	this->data = nullptr;

	this->size = this->capacity = 0;
}

template<typename T>
void Vector<T>::copy(const Vector& other)
{
	this->capacity = other.capacity;
	this->size = other.size;

	this->data = new T [this->capacity];

	for (size_t i = 0; i < other.getSize(); i++)
	{
		this->data[i] = other.data[i];
	}
}

template<typename T>
void Vector<T>::resize()
{
	std::size_t newCap = this->capacity * 2;

	T* newData = new T [newCap];

	for (std::size_t i = 0; i < this->size; i++)
	{
		newData[i] = this->data[i];
	}

	delete[] this->data;
	this->data = newData;

	this->capacity = newCap;
}

template<typename T>
Vector<T>::Vector()
	: data(nullptr), capacity(2), size(0)
{
	this->data = new T [this->capacity];
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other)
	: data(nullptr) {
	copy(other);
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

template<typename T>
Vector<T>::~Vector()
{
	free();
}

template<typename T>
void Vector<T>::push_back(const T& p)
{
	if (this->size == this->capacity)
		resize();

	this->data[this->size] = p;
	this->size++;
}

template<typename T>
void Vector<T>::erase(const std::size_t index)
{
	if (index >= this->size)
		throw std::out_of_range("Vector: Invalid Erase Index");

	for (std::size_t i = index; i < this->size - 1; i++)
	{
		this->data[i] = this->data[i + 1];
	}

	this->size--;
}

template<typename T>
const T& Vector<T>::operator[](const std::size_t index) const
{
	if (index >= this->size)
		throw std::out_of_range("Vector: Invalid [] Index");

	return this->data[index];
}

template<typename T>
T& Vector<T>::operator[](const std::size_t index)
{
	if (index >= this->size)
		throw std::out_of_range("Vector: Invalid [] Index");

	return this->data[index];
}

