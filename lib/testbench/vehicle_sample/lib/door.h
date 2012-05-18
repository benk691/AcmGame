#ifndef DOOR_H
#define DOOR_H

#include <GL/glut.h>
#include <cmath>
class Door{
    public :
        Door();
        ~Door();

        void draw_solid();
        void update(bool toggle);
        void set_open_out(bool set);

        void break_off(double x_val, double y_val, double z_val);
        void set_position(double x_val, double y_val, double z_val);
        bool free;
    private :
        double width;
        double height;
        double depth;
        bool open_out;
        int open_angle;
        double open_speed;
        double current_angle;
        bool opening;
        double rel_x;
        double rel_y;
        double rel_z;
        double pitch;
};

#endif
