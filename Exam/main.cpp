#include "Heater.h"
#include "Room.h"
#include "TV.h"
#include "Fridge.h"

void test()
{
    Heater heater("Peshy", "Mega Heat", "P MH140-7765d", 2);
    TV tv("Samsung", "Smart TV", "S 55UJ6307", 0.25, 100);


    Room bedroom("Bedroom", 5, 2.1f);
    bedroom += heater;
    bedroom.insertNotAllowedAppliance(Type::TV);
    bedroom.insertNotAllowedAppliance(Type::FRIDGE);

    bedroom["P MH140-7765d"]->turnOn();

    bedroom.print();

    Room guestroom(bedroom);
    guestroom.setName("Guestroom");
    guestroom.removeNotAllowedAppliance(Type::TV);

    guestroom += tv;
    guestroom["S 55UJ6307"]->turnOn();

    guestroom["P MH140-7765d"]->turnOff();
    guestroom["S 55UJ6307"]->turnOn();

    ((TV*)guestroom["S 55UJ6307"])->setBrightness(20);

    guestroom["P MH140-7765d"]->turnOn();
    ((TV*)guestroom["S 55UJ6307"])->setBrightness(100);

    guestroom.print();
 }

int main()
{
    test();
}