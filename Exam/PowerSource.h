#pragma once

class Appliance;

struct PowerSource
{
    virtual void checkPowerSource() = 0;
    virtual float getAllConsumption() const = 0;
    virtual float getMaxConsumption() const = 0;
    virtual void setSource(Appliance& appliance);
    virtual void cloearSource(Appliance& appliance);
};