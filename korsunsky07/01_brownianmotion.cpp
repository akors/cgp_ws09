#include <iostream>
#include <unistd.h>

 #include "xwindows.h"

const double fps = 50;
const int nx = 400, ny = 300;

void maintain_fps();

int main ()
{
    XWindow main_window(450,0);

    // Oeffne Fenster der Groesse xmax x ymax

    main_window.Open(nx, ny, "Brownsche Molekularbewegung");

    // allocate variables for particle position
    int p_x = nx/2, p_y = ny/2;

    // number of position changes per frame
    const int iters = 5;

    std::cout<<"Rendern...\n";
    while (!main_window.KeyIsPressed())
    {
        for (int i = 0; i < iters; ++i)
        {
            int rr = rand() % 4;
            switch (rr)
            {
                case 0: ++p_x; break; case 1: --p_x; break;
                case 2: ++p_y; break; case 3: --p_y;  default:;
            }

            main_window.DrawPoint(p_x,p_y);
        }

        useconds_t sleep_us = ((1/fps) * 1e+6);
        usleep(sleep_us); // sleep certain time to maintain framerate
    }

    std::cout<<"Bye!\n";
    return 0;
 }
