#include "TV.h"
#include "Room.h"

TV::TV(const char *make, const char *model, const char *sN, const double power, const std::size_t brightness)
: Appliance(ApplianceType::TV, make, model, sN, power)
{
    setBrightness(brightness);
}

Appliance *TV::clone() const
{
    return new TV(*this);
}

double TV::getPower() const
{
    return getIsOn() ? static_cast<double>((brightness / 100)) * this->power : 0.05; 
}

void TV::print() const
{
    std::cout << "Type: TV" << std::endl;
    Appliance::print();
    std::cout << "Brightness: " << brightness << "%" << std::endl;
}

void TV::setBrightness(const std::size_t brightness)
{
    if(brightness > 100)
        throw std::invalid_argument("TV: Invalid brightness!");

    this->brightness = brightness;

    if(this->currentRoom)
        this->currentRoom->checkPower();
}
