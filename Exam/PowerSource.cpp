#include "PowerSource.h"
#include "Appliance.h"

void PowerSource::setSource(Appliance &appliance)
{
    appliance.setSource(this);
}

void PowerSource::cloearSource(Appliance &appliance)
{
    appliance.setSource(nullptr);
}