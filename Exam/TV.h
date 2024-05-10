#pragma once
#include "Appliance.h"

class TV: public Appliance
{
public:
    TV(const char* make, const char* model, const char* serialNumber,float power, std::size_t brightness);

    virtual float getConsumption() const override;
    virtual Appliance* clone() const override;

    std::size_t getBrightness() const {return this->brightness;}
    void setBrightness(std::size_t brightness);
private:

    std::size_t brightness;
};