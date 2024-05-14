#pragma once
#include "Appliance.h"

class Heater: public Appliance
{
public:
    Heater(const char* make, const char* model, const char* sN, const double power);
    
    virtual ~Heater() = default;


    virtual void print() const override;
    virtual Appliance* clone() const override;
    virtual double getPower() const override;
};