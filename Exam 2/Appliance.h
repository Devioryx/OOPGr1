#pragma once
#include <iostream>
#include <stdexcept>
#include <cstring>
#include "ApplianceType.h"

class Room;

class Appliance
{
public:
// Конструктори
    Appliance(ApplianceType type, const char* make, const char* model, const char* sN, const double power);
    Appliance(const Appliance& other);
    Appliance& operator=(const Appliance& other) = delete;

    virtual ~Appliance();


// Мутатори
    void turnOn();
    void turnOff();
    void setRoom(Room* room);

// Селектори
    bool getIsOn() const {return this->isOn;}
    virtual double getPower() const {return this->power;}

    const char* getMake() const {return this->make;}
    const char* getModel() const {return this->model;}
    const char* getSN() const {return this->sN;}
    Room* getRoom() {return this->currentRoom;}

// Допълнителни фунцкии
    virtual void print() const;


    virtual Appliance* clone() const  = 0;

    ApplianceType getType() const {return this->type;}
protected:

    char* make;
    char* model;
    char* sN;

    double power;
    bool isOn;
    ApplianceType type;

    Room* currentRoom;
private:
    void setMake(const char* make);
    void setModel(const char* model);
    void setSN(const char* sN); 
    void setPower(const double power);

    void copy(const Appliance& other);
    void free();
};