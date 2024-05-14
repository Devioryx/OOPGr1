#include "Heater.h"

Heater::Heater(const char *make, const char *model, const char *sN, const double power)
    : Appliance(ApplianceType::HEATER,make, model, sN, power) {}

void Heater::print() const
{
    std::cout << "Type: Heater" << std::endl;
    Appliance::print();
}

Appliance *Heater::clone() const
{
    return new Heater(*this);
}

double Heater::getPower() const
{
    return getIsOn() ? this->power : 0.0;
}
