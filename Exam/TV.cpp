#include "TV.h"

TV::TV(const char *make, const char *model, const char *serialNumber, float power, std::size_t brightness)
: Appliance(Type::TV, make, model, serialNumber, power) 
{
    setBrightness(brightness);
}

float TV::getConsumption() const
{
    return isOn() ? float( float(brightness)/ float(100)) * float(consumption) :  0.05f;
}

Appliance *TV::clone() const
{
    return new TV(*this);
}

void TV::setBrightness(std::size_t brightness) {
    if(brightness > 100)
        throw std::invalid_argument("Brightness must be a value between 0 and 100");

    this->brightness = brightness;
    if(source)
        source->checkPowerSource(); 
};