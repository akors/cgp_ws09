#include "flieger.hpp"

int main()
{
    C_flieger Boeing, Airbus;

    // start der Flugzeuge
    Boeing.Speed(600,600,0);
    Boeing.Steig(1500);
    Airbus.Speed(600,-600,0);
    Airbus.Steig(1200);

    // erste Wende
    Boeing.Speed(400,-200,1000);
    Airbus.Speed(400,200,1000);

    Kollisionstest(Boeing,Airbus,500,1500);

    return 0;
}


