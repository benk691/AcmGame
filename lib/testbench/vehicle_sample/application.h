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
    void mouse_click_event(mouse_button button, mouse_button_state button_state,int x, int y);
    void options_menu(int input);
    void mouse_move_event(int x, int y);
    void keyboard_event(unsigned char key, int x, int y);
    void keyboard_up_event(unsigned char key, int x, int y);

private:
    bool solid;
    bool up_1, down_1, left_1, right_1,
         up_2, down_2, left_2, right_2,
         left_d1, right_d1, left_d2, right_d2;
    std::vector <Vehicle> vehicles;
    timer t;
    int selectedObject;
    int resolution;
    double distance;
};

#endif
