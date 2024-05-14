#include "Appliance.h"
#include "Room.h"

Appliance::Appliance(ApplianceType type, const char *make, const char *model, const char *sN, const double power)
: make(nullptr), model(nullptr), sN(nullptr), isOn(false), type(type), currentRoom(nullptr) {
    try
    {
        setMake(make);
        setModel(model);
        setSN(sN);
        setPower(power);
    }
    catch(...)
    {
        free();
        throw;
    }
}

Appliance::Appliance(const Appliance &other)
: make(nullptr), model(nullptr), sN(nullptr), currentRoom(nullptr)
{
    copy(other);
}

Appliance::~Appliance()
{
    free();
}

void Appliance::turnOn()
{
    if(!currentRoom || isOn)
        return;

    isOn = true;

    try
    {
        currentRoom->calcPower();
    }
    catch(const std::runtime_error& e)
    {
        isOn = false;
    }
}

void Appliance::turnOff()
{
    if(!currentRoom || !isOn)
        return;

    isOn = false;
}

void Appliance::setRoom(Room *room)
{
    if(currentRoom)
        throw std::runtime_error("Applaince: Already connected to socket!");

    currentRoom = room;
}

void Appliance::print() const
{
    std::cout << "Make: " << make << std::endl;
    std::cout << "Model: " << model << std::endl;
    std::cout << "Serial number: " << sN << std::endl;
    std::cout << "Power: " << power << std::endl;
    std::cout << "Is on: " << (isOn ? "Yes" : "No") << std::endl;
}

void Appliance::setMake(const char *make)
{
    if(!make || !make[0])
        throw std::invalid_argument("Appliance: Invalid make!");

    delete[] this->make;
    this->make = new char[strlen(make) + 1];
    strcpy(this->make, make);
}

void Appliance::setModel(const char *model)
{
    if(!model || !model[0])
        throw std::invalid_argument("Appliance: Invalid model!");

    delete[] this->model;
    this->model = new char[strlen(model) + 1];
    strcpy(this->model, model);
}

void Appliance::setSN(const char *sN)
{
    if(!sN || !sN[0])
        throw std::invalid_argument("Appliance: Invalid serial number!");

    delete[] this->sN;
    this->sN = new char[strlen(sN) + 1];
    strcpy(this->sN, sN);
}

void Appliance::setPower(const double power)
{
    if(power <= 0)
        throw std::invalid_argument("Appliance: Invalid power!");

    this->power = power;
}

void Appliance::copy(const Appliance &other)
{
    try
    {
        this->setMake(other.make);
        this->setModel(other.model);
        this->setSN(other.sN);

        this->power = other.power;
        this->isOn = other.isOn;
    }
    catch(...)
    {
        free();
    }
}

void Appliance::free()
{
    delete[] this->make;
    this->make = nullptr;

    delete[] this->model;
    this->model = nullptr;
    
    delete[] this->sN;
    this->sN = nullptr;

    this->currentRoom = nullptr;
    this->power = this->isOn = 0;
}
