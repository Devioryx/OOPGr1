#pragma once
#include "Appliance.h"

class Vector
{
public:
    Vector();
    Vector(const std::size_t cap);

    Vector(const Vector& other);
    Vector& operator=(const Vector& other);

    void push_back(Appliance* appliance);
    void erase(const std::size_t index);

    const Appliance* operator[](const std::size_t index) const;
    Appliance* operator[](const std::size_t index);

    std::size_t getSize() const {return this->size;}
    std::size_t getCapacity() const {return this->capacity;}

private:
    void free();
    void copy(const Vector& other);
    void resize();

    Appliance** data;
    std::size_t size;
    std::size_t capacity;    
};