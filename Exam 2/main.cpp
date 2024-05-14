#include "Heater.h"
#include "TV.h"
#include "Fridge.h"
#include "Room.h"

int main()
{
    
    Room bedroom("Bedroom", 2.1, 5);

    Heater h("Peshy", "Mega Heat", "P MH140-7765d", 2);

    bedroom += h;
    bedroom.addForbiden(ApplianceType::TV);
    bedroom.addForbiden(ApplianceType::FRIDGE);

    bedroom["P MH140-7765d"]->turnOn();

    bedroom.print();

    Room guestroom(bedroom);
    guestroom.setName("Guestroom");
    bedroom.print();
    guestroom.print();

    TV tv("Samsung", "UE55TU8002UXXH", "S UE55TU8002UXXH", 0.250, 100);

    guestroom.removeForbidden(ApplianceType::TV);
    guestroom += tv;

    guestroom.print();

    guestroom["S UE55TU8002UXXH"]->turnOn();
    
    guestroom.print();

    guestroom["P MH140-7765d"]->turnOff();
    
    guestroom.print();

    guestroom["S UE55TU8002UXXH"]->turnOn();

    guestroom.print();

    dynamic_cast<TV*>(guestroom["S UE55TU8002UXXH"])->setBrightness(20);

    guestroom.print();

    guestroom["P MH140-7765d"]->turnOn();

    guestroom.print();

    dynamic_cast<TV*>(guestroom["S UE55TU8002UXXH"])->setBrightness(100);

    guestroom.print();
}
