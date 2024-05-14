#pragma once
#include "Appliance.h"
#include "Vector.h"

class Room
{
public:
    Room(const char* name, const double maxPower, const std::size_t socketCnt);
    Room(const Room& other);
    Room& operator=(const Room& other);

    ~Room() = default;

    Room& operator+=(const Appliance& app);
    Room operator+(const Appliance& app) const;

    Room& operator-=(const char* sN);
    Room operator-(const char* sN) const;

    Appliance* operator[](const char* sN);
    const Appliance* operator[](const char* sN) const;

    void print() const;
    void setName(const char* name);
    void removeForbidden(ApplianceType type);
    void addForbiden(ApplianceType type);

    void calcPower();
    void checkPower();
    double getAllPower() const;
private:
    void copy(const Room& other);

    void setMaxPower(const double maxPower);

    char name[31];
    double maxPower;

    bool forbiddenAppliances[3] {0};
    
    bool isPowerDown;

    std::size_t socketCnt;
    Vector sockets;
};