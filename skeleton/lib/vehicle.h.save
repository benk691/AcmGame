#ifndef VEHICLE_H
#define VEHICLE_H

#include <GL/glut.h>
#include <cmath>
#include "door.h"

class Hubcap
{
    public :
        Hubcap()
        :p(gluNewQuadric()),red(.5), green(.5), blue(0)
        {}
        ~Hubcap()
        {}
        void draw(){

            int num_spokes = 16;
            double spoke_width = .05;
            double angle_step = 360.0/num_spokes;

            glPushMatrix();
                glColor3f(red, green, blue);
                glutSolidSphere(.25, 20, 20);

                glRotatef(90,0,1,0);
                for(int i = 0; i < num_spokes; ++i){
                    glRotatef(angle_step*i,1,0,0);
                    gluCylinder(p, spoke_width, spoke_width, .75, 4, 1);
                }
            glPopMatrix();
        }
    private :
        GLUquadricObj *p;
        double red;
        double green;
        double blue;
};
class Tire
{
    public:
        Tire()
        {}
        ~Tire()
        {}
        void draw(double x, double y, double z, double spin, double turn){

            angle -= spin*38.1971863;

            glPushMatrix();
                glTranslatef(x, y, z);
                //glScalef(1, 1, 0.5);

                glRotatef(turn, 0, 1, 0);
                glRotatef(angle, 0, 0, 1);

                my_cap.draw();

                //glScalef(1, 1, 0.5);
                //solid ? glutSolidTorus(0.5, 1, 12, 12) : glutWireTorus(0.5, 1, 12, 12);
                glColor3f(.2, .2, .2);
                glutSolidTorus(0.5, 1, 10, 10);
            glPopMatrix();
        }
    private:
        Hubcap my_cap;
        double angle;
};
class Vehicle
{
    public:
        Vehicle();
        Vehicle(bool keys, double x, double y, double z);
        ~Vehicle();
        void draw(double counter,bool up, bool down, bool left, bool right, bool left_open, bool right_open);
        bool use_keys;
        double x_pos;
        double y_pos;
        double z_pos;
        double direction;
        double speed;
    private:
        double turn;
        Tire wheels[4];
        Door doors[2];
};

#endif
