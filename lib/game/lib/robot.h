#ifndef ROBOT_H
#define ROBOT_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <cmath>
#include "door.h"
#include "weapon.h"

class Hubcap
{
    public :
        Hubcap()
        :p(gluNewQuadric()),red(.5), green(.5), blue(0)
        {}
        ~Hubcap()
        {
            //gluDeleteQuadric(p);
        }
        void draw(){
            int num_spokes = 4;
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
        :free(false), rel_x(0.0), rel_y(0.0), rel_z(0.0),my_cap(Hubcap()), angle(0), pitch(0)
        {}
        ~Tire()
        {}
        void draw(double spin, double turn){

            angle -= spin*38.1971863;

            glPushMatrix();
                glTranslatef(rel_x, rel_y, rel_z);
                //glScalef(1, 1, 0.5);
                if(free){
                    if(rel_y > 0) rel_y -= .01;
                    if(pitch < 90) pitch += .5;
                    glRotatef(pitch,1,0,0);
                    glTranslatef(0, -1.5, 0);
                }
                else{
                    glRotatef(turn, 0, 1, 0);
                    glRotatef(angle, 0, 0, 1);
                }

                my_cap.draw();

                //glScalef(1, 1, 0.5);
                //solid ? glutSolidTorus(0.5, 1, 12, 12) : glutWireTorus(0.5, 1, 12, 12);
                glColor3f(.2, .2, .2);
                glutSolidTorus(0.5, 1, 10, 10);
            glPopMatrix();
        }
        void update(){

        }
        void break_off(double x_val, double y_val, double z_val){
            free = true;
            rel_x += x_val;
            rel_y += y_val;
            rel_z += z_val;
        }
        void set_position(double x_val, double y_val, double z_val){
            rel_x = x_val;
            rel_y = y_val;
            rel_z = z_val;
        }
        bool free;
    private:
        double rel_x;
        double rel_y;
        double rel_z;
        Hubcap my_cap;
        double angle;
        double pitch;
};
class Robot
{
    public:
        Robot();
        Robot(bool keys, double x, double y, double z);
        ~Robot();
        void collision();
        void draw(double counter,bool up, bool down, bool left, bool right, bool left_open, bool right_open, bool attack);
        void snap_item();
        void move_back();
        bool attacking();
        bool use_keys;
        double x_pos;
        double y_pos;
        double z_pos;
        double direction;
        double speed;
        double turn;
        double max_speed;
        double max_turn;
    private:
        double x_prev;
        double z_prev;
        Tire wheels[4];
        Door doors[2];
        Weapon my_weapon;
};

#endif
