#pragma once
#include "Appliance.h"

class Vector
{
public:
    Vector(const std::size_t capacity);
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);

    ~Vector();

    void push_back(const Appliance* app);
    void erase(const std::size_t index);

    const Appliance* operator[](const std::size_t index) const;
    Appliance* operator[](const std::size_t index); 
    
    Appliance* back();

    Appliance* at(const std::size_t index);

    std::size_t getCapacity() const {return this->capacity;}
    std::size_t getSize() const {return this->size;}

    void clear();
private:
    void free();
    void copy(const Vector& other);

    std::size_t capacity;
    std::size_t size;

    Appliance** data;
};
