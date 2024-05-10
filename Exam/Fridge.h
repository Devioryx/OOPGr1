#pragma once
#include "Appliance.h"

class Fridge: public Appliance
{
public:
    Fridge(const char *make, const char *model, const char *serialNumber, float power, std::size_t compressors);
    
    virtual float getConsumption() const override;
    virtual Appliance* clone() const override;

    std::size_t getCompressors() const {return this->compressors;} 
private:
    std::size_t compressors;
};