#include "Heater.h"

Heater::Heater(const char *make, const char *model, const char *serialNumber, float power)
: Appliance(Type::HEATER, make, model, serialNumber, power) {}

float Heater::getConsumption() const
{
    return isOn() ? consumption : 0.0f;
}

Appliance *Heater::clone() const
{
    return new Heater(*this);
}
