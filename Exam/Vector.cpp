#include "Vector.h"

Vector::Vector()
: data(nullptr), size(0), capacity(0) {
}

Vector::Vector(const std::size_t cap)
    : capacity(cap), size(0), data(nullptr)
{
    data = new (std::nothrow) Appliance*[capacity];
}

Vector::Vector(const Vector &other)
: data(nullptr)
{
    copy(other);
}

Vector &Vector::operator=(const Vector &other)
{
    if(this != &other)
    {
        free();
        copy(other);
    }
    return *this;
}

void Vector::push_back(Appliance* appliance)
{
    if(size == capacity)
        resize();

    data[size++] = appliance;;
}

void Vector::erase(const std::size_t index)
{
    if(index >= size)
        throw std::out_of_range("Index out of range");

    delete data[index];

    for(std::size_t i = index; i < size - 1; i++)
    {
        data[i] = data[i + 1];
    }
}

const Appliance *Vector::operator[](const std::size_t index) const
{
    return data[index];
}

Appliance *Vector::operator[](const std::size_t index)
{
    return data[index];
}

void Vector::free()
{
    delete[] data;
    data = nullptr;

    size = capacity = 0;
}

void Vector::copy(const Vector &other)
{
    this->capacity = other.capacity;
    this->size = other.size;

    try
    {
        data = new Appliance*[this->capacity];

        for(std::size_t i = 0; i < other.size; i++)
        {
            data[i] = other.data[i];
        }
    }
    catch(const std::exception& e)
    {
        free();
        throw e;
    }
    
}

void Vector::resize()
{
    std::size_t newCap = this->capacity * 2;

    Appliance** newData = new Appliance*[newCap];

    for(std::size_t i = 0; i < size; i++)
    {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;

    capacity = newCap;
}
