#include "Fridge.h"

Fridge::Fridge(const char *make, const char *model, const char *serialNumber, float power, std::size_t compressors)
: Appliance(Type::FRIDGE, make, model, serialNumber, power), compressors(compressors) {}

float Fridge::getConsumption() const
{
    return compressors * consumption;
}

Appliance *Fridge::clone() const
{
    return new Fridge(*this);
}
