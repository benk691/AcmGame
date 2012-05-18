#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>
#include <cmath>

#include "gl_viewer.h"
#include "timer.h"
#include "lib/vehicle.h"
#include "lib/door.h"

class line_segment
{
public:
    line_segment()
        : x0(0), y0(0), x1(0), y1(0)
    {}

    line_segment(int x0, int y0, int x1, int y1)
        : x0(x0), y0(y0), x1(x1), y1(y1)
    {}

    int x0, y0, x1, y1;
};

class application : public gl_viewer
{
    public:
        application();
        ~application();
        void init_event();
        void draw_event();
    private:
        bool solid;
        std::vector <Vehicle> vehicles;
        timer t;
        int selectedObject;
        int resolution;
        double distance;
};

#endif
