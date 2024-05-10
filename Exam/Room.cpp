#include "Room.h"

Room::Room(const char* name, const std::size_t socketCnt, float maxPower)
: sockets(), usedSocketCnt(0), socketCnt(socketCnt), powerDown(false)
{
    setMaxConsumption(maxPower);

    setName(name);
}

Room::Room(const Room& other)
{
    copy(other);
}

Room &Room::operator=(const Room &other)
{
    if(this != &other)
    {
        free();
        copy(other);
    }

    return *this;
}

Room::~Room()
{
    free();
}

Room &Room::operator+=(const Appliance &appliance)
{
    if(usedSocketCnt < socketCnt && isAllowed(appliance.getType()) && !appliance.isOn() && !powerDown && getAllConsumption() + appliance.getConsumption() <= maxConsumption)
    {
        Appliance* toAdd = appliance.clone();
        setSource(*toAdd);
        usedSocketCnt++;
        sockets.push_back(toAdd);
    }    
    
    return *this;
}

Room Room::operator+(const Appliance &appliance)
{
    return Room(*this) += appliance;
}

Room &Room::operator-=(const char *serialNumber)
{
    std::size_t index = findAppliance(serialNumber);
    if(index != socketCnt)
    {
        delete sockets[index];
        sockets.erase(index); 
    }
    return *this;
}

Room Room::operator-(const char *serialNumber)
{
    return Room(*this) -= serialNumber;
}

Appliance* Room::operator[](const char *serialNumber)
{
    int index = findAppliance(serialNumber);
    return index == -1 ? nullptr : sockets[index];
}

std::size_t Room::getSocketCnt() const
{
    return socketCnt;
}

std::size_t Room::getUsedSocketCnt() const
{
    return usedSocketCnt;
}

void Room::insertNotAllowedAppliance(Type type)
{
    std::size_t index = Room::MAX_APPLIANCES;

    for(std::size_t i = 0; i < Room::MAX_APPLIANCES; i++)
    {
        if(notAllowed[i] == type)
            return;    
    }

    for(std::size_t i = 0; i < Room::MAX_APPLIANCES; i++)
    {
        if(notAllowed[i] == Type::UNKNOWN)
            index = i;
    }

    if(index != Room::MAX_APPLIANCES)
        notAllowed[index] = type;
}

void Room::removeNotAllowedAppliance(Type type)
{
    for(std::size_t i = 0; i < Room::MAX_APPLIANCES; i++)
    {
        if(notAllowed[i] == type)
        {
            notAllowed[i] = Type::UNKNOWN;
            return;
        }
    }
}

void Room::setName(const char *name)
{
    if(strlen(name) == 31)
        throw std::invalid_argument("Invalid length of the name of the room!");
    
    strcpy(this->name, name);
}

void Room::print() const
{
	std::cout << "\t----\tRoom " << name << "\t----\t\n";
	std::cout << "Max power: " << maxConsumption << "; current consumption: " << getAllConsumption() << "\n";
	std::cout << "Power state: " << (powerDown ? "Down!" : "OK") << "\n";
	std::cout << "Total plugged devices: " << getUsedSocketCnt() << "\n";
	std::cout << "Total sockets: " << getSocketCnt() << "\n";
	for (unsigned i = 0; i < getUsedSocketCnt(); ++i) {
		sockets[i]->print();
	}
	std::cout << std::endl;
}

void Room::checkPowerSource()
{
    float total = getAllConsumption();
    if(total > maxConsumption)
    {
        powerDown = true;
        free();
        std::cout << "Power down!!!\n";
    }
}

float Room::getAllConsumption() const
{
    if(usedSocketCnt == 0)
        return 0;

    float total = 0;
    for(std::size_t i = 0; i < usedSocketCnt; i++)
    {
        total += sockets[i]->getConsumption();
    }

    return total;
}

float Room::getMaxConsumption() const
{
    return maxConsumption;
}

void Room::free()
{
    for(std::size_t i = 0; i < usedSocketCnt; i++)
    {
        delete sockets[i];
    }

    usedSocketCnt = 0;
}

void Room::copy(const Room &other)
{
    try
    {
        strcpy(this->name, other.name);
        memccpy(this->notAllowed, other.notAllowed, Room::MAX_APPLIANCES, sizeof(Type) * Room::MAX_APPLIANCES);

        this->powerDown = other.powerDown;
        this->maxConsumption = other.maxConsumption;
        this->socketCnt = other.socketCnt;
        this->usedSocketCnt = 0;

        for(std::size_t i = 0; i < other.usedSocketCnt; i++)
        {
            Appliance* toAdd = other.sockets[i]->clone();
            sockets.push_back(toAdd);
            setSource(*sockets[i]);
            usedSocketCnt++;
        }
    }
    catch(const std::exception& e)
    {
        free();
        throw e;
    }
    
}

void Room::setMaxConsumption(float power)
{
    if(power <= 0)
        throw std::invalid_argument("Invalid argument for max power!");

    this->maxConsumption = power;
}

bool Room::isAllowed(Type type)
{
    for(std::size_t i = 0; i < Room::MAX_APPLIANCES; i++)
    {
        if(notAllowed[i] == type)
            return false;
    }

    return true;
}

int Room::findAppliance(const char *serialNumber) const
{
    for(std::size_t i = 0; i < getUsedSocketCnt(); i++)
    {
        if(strcmp(sockets[i]->getSerialNumber(), serialNumber) == 0)
            return i;
    }

    return socketCnt;
}
