#pragma once
#include "Appliance.h"

class TV: public Appliance
{
public:
    TV(const char* make, const char* model, const char* sN, const double power, const std::size_t brightness);

    virtual ~TV() = default;
    virtual Appliance* clone() const override;

    virtual double getPower() const override;
    virtual void print() const override;
    
    void setBrightness(const std::size_t brightness);
private:
    std::size_t brightness;
};