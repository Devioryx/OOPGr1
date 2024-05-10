#pragma once
#include "Appliance.h"
#include "Vector.h"
#include "PowerSource.h"

class Room: public PowerSource
{
public:
    Room(const char* name, const std::size_t socketCnt, float maxConsumption);
    Room(const Room& other);
    Room& operator=(const Room& other);

    ~Room();

    // Operators
    Room& operator+=(const Appliance& appliance);
    Room operator+(const Appliance& Appliance);
    Room& operator-=(const char* serialNumber);
    Room operator-(const char* serialNumber);
    
    Appliance* operator[](const char* serialNumber); 
    

    std::size_t getSocketCnt() const;
    std::size_t getUsedSocketCnt() const;

    void insertNotAllowedAppliance(Type type);
    void removeNotAllowedAppliance(Type type);

    void setName(const char* name);
    void print() const;

    virtual void checkPowerSource() override;
    virtual float getAllConsumption() const override;
    virtual float getMaxConsumption() const override;

private:
    void free();
    void copy(const Room& other);

    void setMaxConsumption(float power);
    bool isAllowed(Type type);
    int findAppliance(const char* serialNumber) const;

    char name[31];

    std::size_t socketCnt;
    std::size_t usedSocketCnt;

    float maxConsumption;
    static constexpr std::size_t MAX_APPLIANCES = 3;
    bool powerDown;

    Vector sockets;
    Type notAllowed[Room::MAX_APPLIANCES];
};