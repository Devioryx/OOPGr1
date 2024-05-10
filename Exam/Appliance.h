#pragma once
#include <iostream>
#include <cstring>

#include "PowerSource.h"

enum class Type
{
    UNKNOWN,

    HEATER,
    TV,
    FRIDGE,
};

class Appliance
{
public:
    Appliance(Type type, const char* make, const char* model, const char* serialNumber, float power);

    Appliance(const Appliance& other);
    Appliance& operator=(const Appliance& other);

    virtual ~Appliance();


    Type getType() const {return this->type;}
    const char* getMake() const {return this->make;}
    const char* getModel() const {return this->model;}
    const char* getSerialNumber() const {return this->serialNumber;}
    virtual float getConsumption() const {return this->consumption;}
    bool isOn() const {return this->on;}
    
    bool turnOn();
    bool turnOff();

    virtual void print() const;
    virtual Appliance* clone() const = 0;


protected:

    char* make;
    char* model;
    char* serialNumber;

    float consumption;
    bool on;

    Type type;

    friend PowerSource;
    PowerSource* source;
private:
    void setSource(PowerSource* source);
    void free();
    void copy(const Appliance& other);


    void setString(char*& destination, const char* source);
    void setConsumption(float power);
};