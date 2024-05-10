#pragma once
#include "Appliance.h"

class Heater: public Appliance
{
public:
    Heater(const char* make, const char* model, const char* serialNumber, float power);


    virtual float getConsumption() const override;
    virtual Appliance* clone() const override;
};