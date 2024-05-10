#include "Appliance.h"

Appliance::Appliance(Type type, const char *make, const char *model, const char *serialNumber, float power)
: make(nullptr), model(nullptr), serialNumber(nullptr), on(false), type(type), source(nullptr) {
    try
    {
        setConsumption(power);

        setString(this->make, make);
        setString(this->model, model);
        setString(this->serialNumber, serialNumber);
    }
    catch(const std::exception& e)
    {
        free();
        throw e;
    }
    
}

Appliance::Appliance(const Appliance &other)
: make(nullptr), model(nullptr), serialNumber(nullptr)
{
    copy(other);
}

Appliance &Appliance::operator=(const Appliance &other)
{
    if(this != &other)
    {
        free();
        copy(other);
    }
    return *this;
}

Appliance::~Appliance()
{
    free();
}

bool Appliance::turnOn()
{
    if(!source || isOn())
        return false;

    float current = source->getAllConsumption();
    float max = source->getMaxConsumption();

    on = true;

    if(current + getConsumption() > max)
    {
        on = false;
        return false;
    }
    source->checkPowerSource();
    return true;
}

bool Appliance::turnOff()
{
    if(!isOn())
        return false;

    on = false;
    source->checkPowerSource();
    return false;
}

void Appliance::print() const
{
    std::cout << "Model: " << this->getModel() << std::endl;
    std::cout << "Make: " << this->getMake() << std::endl;
    std::cout << "Consumed power: " << (isOn() ? this->getConsumption() : 0.0f) << "KW" << std::endl;
}

void Appliance::setSource(PowerSource *source)
{
    if(source)
    {
        if(this->source)
            throw std::logic_error("Appliance already has a power source!");

        this->source = source;
        this->source->checkPowerSource();
    }

    else
    {
        on = false;
        if(this->source)
            this->source->checkPowerSource();
        this->source = nullptr;
    }

}

void Appliance::free()
{
    delete[] this->make;
    this->make = nullptr;

    delete[] this->model;
    this->model = nullptr;

    delete[] this->serialNumber;
    this->serialNumber = nullptr;

    this->source = nullptr;
}

void Appliance::copy(const Appliance &other)
{
    try
    {
        this->source = nullptr;
        this->consumption = other.consumption;
        this->on = other.on;
        this->type = other.type;

        setString(this->make, other.make);
        setString(this->model, other.model);
        setString(this->serialNumber, other.serialNumber);
    }
    catch(const std::exception& e)
    {
        free();
        throw e;        
    }
}

void Appliance::setString(char *&destination, const char *source)
{
    if(!source || !source[0])
        throw std::invalid_argument("Appliance make, model and serial number must be a valid string!");

    delete[] destination;
    destination = new (std::nothrow) char[strlen(source) + 1];
    if(!destination)
        throw std::bad_alloc();

    strcpy(destination, source);
}

void Appliance::setConsumption(float power)
{
    if(power <= 0)
        throw std::invalid_argument("Appliance must have a positive consumption value!");

    this->consumption = power;
}
