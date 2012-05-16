#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include "door.h"

Door::Door()
:width(2), height(1.4), depth(.1), open_out(false), open_angle(50), open_speed(.3),
 current_angle(0), opening(false), rel_x(0), rel_y(0), rel_z(0), free(false), pitch(0)
{}
Door::~Door()
{}

void Door::update(bool toggle){
    if(not free){
        if(toggle) opening = !opening;
        if(opening){
            if(current_angle < open_angle)
                current_angle += open_speed;
        }
        else{
            if(current_angle >= open_speed)
                current_angle -= open_speed;
        }
    }
    draw_solid();
}
void Door::draw_solid(){
    glPushMatrix();
        glTranslatef(rel_x, rel_y, rel_z);
        if(open_out){
            if(free){
                if(rel_y > 0) rel_y -= .01;
                if(pitch < 90) pitch += .5;
                glRotatef(pitch,1,0,0);
                glTranslatef(0, -height/2, 0);
            }
            glRotatef(-current_angle,0,1,0);
        }
        else{
            if(free){
                if(rel_y > 0) rel_y -= .01;
                if(pitch > -90) pitch -= .5;
                glRotatef(pitch,1,0,0);
                glTranslatef(0, -height/2, 0);
            }
            glRotatef(current_angle,0,1,0);
        }

        glTranslatef(-width*.5, 0, 0);

        glScalef(width, height, depth);

        glColor3f(.2, .2, .2);
        glutSolidCube(1);
    glPopMatrix();
}
void Door::set_open_out(bool set){
    open_out = set;
}
void Door::break_off(double x_val, double y_val, double z_val){
    current_angle = 0;
    free = true;
    rel_x = x_val;
    rel_y = y_val;
    rel_z = z_val;
}
bool Door::is_broken(){
    return free;
}
void Door::set_position(double x_val, double y_val, double z_val){
    rel_x = x_val;
    rel_y = y_val;
    rel_z = z_val;
}
