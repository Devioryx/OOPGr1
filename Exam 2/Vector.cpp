#include "Vector.h"

void Vector::clear()
{
    free();
}

void Vector::free()
{
    for(std::size_t i = 0; i < this->size; i++)
    {
        delete data[i];
    }

    delete[] this->data;
    this->data = nullptr;

    this->size = this->capacity = 0;
}

void Vector::copy(const Vector &other)
{
    this->data = new Appliance*[other.capacity];

    try
    {
        for(std::size_t i = 0; i < other.size; i++)
        {
            this->data[i] = other.data[i]->clone();
            this->size++;
        }
    }
    catch(...)
    {
        free();
        throw;
    }

    this->capacity = other.capacity;
    this->size = other.size;
    
}

Vector::Vector(const std::size_t capacity)
: capacity(capacity), size(0), data(nullptr) {
    try
    {
        this->data = new Appliance*[capacity];
    }
    catch(const std::exception& e)
    {
        free();
        throw;
    }
    
}

Vector::Vector(const Vector &other)
: data(nullptr) {
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

Vector::~Vector()
{
    free();
}

void Vector::push_back(const Appliance *app)
{
    if(this->capacity == this->size)
        throw std::runtime_error("Vector: No space left!");

    this->data[this->size++] = app->clone();
}

void Vector::erase(const std::size_t index)
{
    if(index >= this->size)
        throw std::out_of_range("Vector: Invalid erase index!");

    delete this->data[index];

    for(std::size_t i = index; i < this->size - 1; i++)
    {
        this->data[i] = this->data[i + 1];
    }

    this->size--;
}

const Appliance *Vector::operator[](const std::size_t index) const
{
    if(index >= this->size)
        throw std::out_of_range("Vector: invalid [] index");

    return this->data[index];
}

Appliance *Vector::operator[](const std::size_t index)
{
    if(index >= this->size)
        throw std::out_of_range("Vector: invalid [] index");

    return this->data[index];
}

Appliance *Vector::back()
{
    return this->data[this->size - 1];
}

Appliance *Vector::at(const std::size_t index)
{
     if (index >= this->size)
        throw std::out_of_range("Vector: Invalid at index");

    return data[index];
}
