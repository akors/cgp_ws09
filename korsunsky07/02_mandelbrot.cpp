#include "xwindows.h"

double x_start = -2., y_start = -1.25;
const int nx = 800;

const unsigned iter_max = 500;
const double radius = 2.0;

unsigned niter(double x, double y);

int main()
{
    double x = x_start, y = y_start;
    double Dx = 2.5 / static_cast<float>(nx);

    std::cout<<"Dx = "<<Dx<<'\n';

    XWindow main_window(450,0);
    main_window.Open(nx, nx, "Mandelbrotmenge");

    for (int point_x = 0; point_x < nx; ++point_x)
    {
        for (int point_y = 0; point_y < nx; ++point_y)
        {
            unsigned nn = niter(x,y);
            if (nn <= iter_max)
            {
                main_window.SetColor( 1. - nn/(30.) );
                main_window.DrawPoint(point_x,point_y);
            }

            y += Dx;
        }

        x += Dx;
        y = y_start;
    }

    main_window.WaitForKeypress();

    return 0;
}

unsigned niter(double x, double y)
{
    unsigned nn = 0;
    double last_r = .0, w_r, w_i = .0;

    // calculate absolute value of the complex number and compare to be smaller
    // than the radius (spare the additional sqrt() call)
    while(w_r*w_r + w_i*w_i < radius*radius && nn < iter_max)
    {
        // calculate the sqare of the complex number, add the current point

        // real part
        w_r = last_r*last_r - w_i*w_i + x;

        // imaginary part
        w_i = 2*last_r*w_i + y;

       last_r = w_r;
       ++nn; // increment counter

       // std::cout<<w_r<<" + i * "<<w_i<<", nn = "<<nn<<std::endl;
    }

    return nn;
}
