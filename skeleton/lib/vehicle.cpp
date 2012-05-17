#include <GL/glut.h>
#include <cmath>
#include "vehicle.h"
//Jorge
//this is the vehicle class implementation

Vehicle::Vehicle()
:use_keys(false), x_pos(0), y_pos(0), z_pos(0), direction(0.0), speed (0), turn (0.0)
{
    doors[0].set_open_out(true);
    doors[1].set_open_out(false);

    doors[0].set_position(1.0,0.0,-1.5);
    doors[1].set_position(1.0,0.0,1.5);
}
Vehicle::Vehicle(bool keys, double x, double y, double z)
:use_keys(keys), x_pos(x), y_pos(y), z_pos(z), direction(0.0), speed (0), turn (0.0)
{
    doors[0].set_open_out(true);
    doors[1].set_open_out(false);

    doors[0].set_position(1.0,0.0,-1.5);
    doors[1].set_position(1.0,0.0,1.5);
    //to see how the doors break off immediately
    //doors[0].break_off(x_pos + 4.0,y_pos,z_pos - 1.5);
    //doors[1].break_off(x_pos + 4.0,y_pos,z_pos + 1.5);
}

Vehicle::~Vehicle()
{}
void Vehicle::draw(double counter,bool up, bool down, bool left, bool right, bool left_open, bool right_open){
    //this updates the x and y coordinates given the car's speed and direction
    x_pos += speed*cos(direction*0.0174532925);
    z_pos -= speed*sin(direction*0.0174532925);

    speed *= .997; //friction effect (slows down over time)
    turn *= .99;   //friction effect, (wheels realign over time)

    //change vehicle's direction based on speed and wheel angle
    direction += 11*speed*sin(turn*0.0174532925);

    //fix the direction to keep nice ranges
    if(direction > 360)
        direction -= 360;
    if(direction < 0)
        direction += 360;

    if(up)
        if(speed < .06)
            speed += .0003;   //accelerate

    if(down){
        if(speed > -.06)
            speed -= .0003;   //decelerate
    }

    if(left xor right){       //won't turn left AND right
        if(left){
            if(turn < 45)     //max turn angle
                turn += 0.4;  //turn speed left
        }
        if(right){
            if(turn > -45)
                turn -= 0.4;  //turn speed right
        }
    }
    // yeah, this snaps a door off if you turn to too much
    if(turn > 30 and not doors[0].is_broken())
        doors[0].break_off(x_pos + 4.0,y_pos,z_pos - 1.5);

    //draw doors where they fell off, not with car
    if(doors[0].is_broken()) doors[0].update(false);
    if(doors[1].is_broken()) doors[1].update(false);

    glPushMatrix();
        glTranslatef(x_pos, y_pos, z_pos);
        glRotatef(direction, 0, 1, 0);
        glTranslatef(3, 0, 0);

        //tires
        wheels[0].draw(-3.0,-1.0,2.0,speed,0);
        wheels[1].draw(3.0,-1.0,2.0,speed,turn);
        wheels[2].draw(-3.0,-1.0,-2.0,speed,0);
        wheels[3].draw(3.0,-1.0,-2.0,speed,turn);

        //doors
        //draw doors with the car
        if(not doors[0].is_broken()) doors[0].update(left_open);
        if(not doors[1].is_broken()) doors[1].update(right_open);

        //body
        glPushMatrix();
            glColor3f(.3, .3, .5);
            glScalef(2, .5, 1);
            glutSolidCube(3);
        glPopMatrix();

        //roof
        glPushMatrix();
            glTranslatef(0, 2, 0);
            glColor3f(.2, .2, .7);
            glScalef(1, .06, 1);
            glutSolidCube(3);
        glPopMatrix();

        //wind shield
        glPushMatrix();
            glEnable (GL_BLEND);
            //glBlendFunc (GL_ONE ,GL_ONE);
            glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(1, 1, 1, .1);

            glPushMatrix();
                glTranslatef(3, .4, 0);
                glRotatef(45, 0, 0, 1);
                glTranslatef(0, 1.3, 0);
                glScalef(.02, .6, 1);
                glutSolidCube(2.6);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(-1.5, 1.4, 0);
                glScalef(.02, .5, 1);
                glutSolidCube(2.6);
            glPopMatrix();

            glDisable (GL_BLEND);
        glPopMatrix();
    glPopMatrix();
}
