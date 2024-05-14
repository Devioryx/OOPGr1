#include "Room.h"

Room::Room(const char *name, const double maxPower, const std::size_t socketCnt)
:isPowerDown(false), socketCnt(socketCnt), sockets(socketCnt) 
{
    setName(name);
    setMaxPower(maxPower);
}

Room::Room(const Room &other)
: sockets(other.socketCnt) {
    copy(other);
}

Room &Room::operator=(const Room &other)
{
    if(this != &other)
    {
        copy(other);
    }
    return *this;
}

Room &Room::operator+=(const Appliance &app)
{
    std::size_t numType = static_cast<std::size_t>(app.getType());

    if(this->sockets.getSize() < this->socketCnt && !this->forbiddenAppliances[numType] && !isPowerDown)
    {
        this->sockets.push_back(&app);
        this->sockets.back()->setRoom(this);
    }
    
    return *this;
}

Room Room::operator+(const Appliance &app) const
{
    return Room(*this) += app;
}

Room &Room::operator-=(const char *sN)
{
    int index = -1;
    for(std::size_t i = 0; i < this->sockets.getSize(); i++)
    {
        if(strcmp(this->sockets[i]->getSN(), sN) == 0)
        {
            index = i;
            break;
        }
    }

    if(index != -1)
    {
        this->sockets.erase(index);
    }

    return *this;
}

Room Room::operator-(const char *sN) const
{
    return Room(*this) -= sN;
}

Appliance *Room::operator[](const char *sN)
{
    int index = -1;
    for(std::size_t i = 0; i < this->sockets.getSize(); i++)
    {
        if(strcmp(this->sockets[i]->getSN(), sN) == 0)
        {
            index = i;
            break;
        }
    }

    return index == -1 ? nullptr : this->sockets[index];
}

const Appliance *Room::operator[](const char *sN) const
{
    int index = -1;
    for(std::size_t i = 0; i < this->sockets.getSize(); i++)
    {
        if(strcmp(this->sockets[i]->getSN(), sN) == 0)
        {
            index = i;
            break;
        }
    }

    return index == -1 ? nullptr : this->sockets[index];
}

void Room::print() const
{
    std::cout << "Room: " << this->name << std::endl;
    std::cout << "Power down: " << (this->isPowerDown ? "Yes" : "No") << std::endl;
    std::cout << "Max power: " << this->maxPower << std::endl;
    std::cout << "Current power: " << getAllPower() << std::endl;
    std::cout << "Sockets in room: " << this->socketCnt << std::endl;
    std::cout << "Sockets in use: " << this->sockets.getSize() << std::endl;
    for(std::size_t i = 0; i < this->sockets.getSize(); i++)
    {
        this->sockets[i]->print();
    }
    std::cout << "\n\n";
}

void Room::setName(const char *name)
{
    if(strlen(name) > 30 || name == nullptr)
        throw std::invalid_argument("Room: Incorrect name!");

    strcpy(this->name, name);
}

void Room::removeForbidden(ApplianceType type)
{
    std::size_t numType = static_cast<std::size_t>(type);
    if(!forbiddenAppliances[numType])
        throw std::runtime_error("Applaince is not forbidden in that room!");

    forbiddenAppliances[numType] = false;
}

void Room::addForbiden(ApplianceType type)
{
    std::size_t numType = static_cast<std::size_t>(type);
    if(forbiddenAppliances[numType])
        throw std::runtime_error("Applaince is already forbidden in that room!");

    forbiddenAppliances[numType] = true;
}

void Room::calcPower()
{
    double total = 0.0;
    for(std::size_t i = 0; i < this->sockets.getSize(); i++)
    {
        total += this->sockets[i]->getPower();
    }

    if(total > this->maxPower)
        throw std::runtime_error("Room: Max power reached!");

}

void Room::checkPower()
{
    double total = 0.0;
    for(std::size_t i = 0; i < this->sockets.getSize(); i++)
    {
        total += this->sockets[i]->getPower();
    }

    if(total > this->maxPower)
    {
        isPowerDown = true;
        this->sockets.clear();
    }
}

double Room::getAllPower() const
{
    double total = 0.0;
    for(std::size_t i = 0; i < this->sockets.getSize(); i++)
    {
        total += this->sockets[i]->getPower();
    }

    return total;
}

void Room::copy(const Room &other)
{
    strcpy(this->name, other.name);
    this->maxPower = other.maxPower;
    this->socketCnt = other.socketCnt;
    this->sockets = other.sockets;
    this->isPowerDown = other.isPowerDown;
    for(std::size_t i = 0; i < 3; i++)
    {
        this->forbiddenAppliances[i] = other.forbiddenAppliances[i];
    }

    for(std::size_t i = 0; i < this->sockets.getSize(); i++)
    {
        this->sockets[i]->setRoom(this);
    }
}

void Room::setMaxPower(const double maxPower)
{
    if(maxPower <= 0)
        throw std::invalid_argument("Room: Invalid max power!");

    this->maxPower = maxPower;
}
