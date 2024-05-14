#pragma once
#include "Appliance.h"

class Fridge: public Appliance
{
public:
    Fridge(const char *make, const char *model, const char *sN, const double power, const std::size_t compressors);

    virtual ~Fridge() = default;

    virtual void print() const override;
    virtual Appliance* clone() const override;
    virtual double getPower() const override;

private:
    std::size_t compressors;
};