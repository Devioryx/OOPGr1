#include "Fridge.h"

Fridge::Fridge(const char *make, const char *model, const char *sN, const double power, const std::size_t compressors)
: Appliance(ApplianceType::FRIDGE, make, model, sN, power), compressors(compressors)
{
}

void Fridge::print() const
{
    std::cout << "Type: Fridge" << std::endl;
    Appliance::print();
    std::cout << "Compressors: " << compressors << std::endl;
}

Appliance *Fridge::clone() const
{
    return new Fridge(*this);
}

double Fridge::getPower() const
{
    return static_cast<double>(compressors) * power;
}
