#include "flieger.hpp"

int main() {
  C_flieger Aerophlot105;

  Aerophlot105.Position(0);
  Aerophlot105.Steig(3000);
  Aerophlot105.Position(10);
  Aerophlot105.Speed(300,200,10);
  Aerophlot105.Position(200);
  Aerophlot105.Position(600);
  Aerophlot105.Speed(-100,600,600);
  Aerophlot105.Position(1000);
  Aerophlot105.Speed(0,0,1000);
  Aerophlot105.Position(1010);
  Aerophlot105.Steig(-3000);
  Aerophlot105.Position(1210);
  return 0;
}


