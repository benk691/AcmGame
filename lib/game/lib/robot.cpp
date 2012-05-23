#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <cmath>
#include "robot.h"
//Jorge
//this is the vehicle class implementation

Robot::Robot()
:use_keys(false), x_pos(0), y_pos(0), z_pos(0), direction(0.0), speed (0), turn (0.0),
max_speed(.1), max_turn(30), x_prev(0), z_prev(0)
{
    wheels[0] = Tire();
    wheels[1] = Tire();
    wheels[2] = Tire();
    wheels[3] = Tire();

    doors[0] = Door();
    doors[1] = Door();

    doors[0].set_open_out(true);
    doors[1].set_open_out(false);

    doors[0].set_position(1.0,0.0,-1.5);
    doors[1].set_position(1.0,0.0,1.5);

    my_weapon = Weapon();
    my_weapon.set_model("hammer.obj");
}
Robot::Robot(bool keys, double x, double y, double z)
:use_keys(keys), x_pos(x), y_pos(y), z_pos(z), direction(0.0), speed (0), turn (0.0),
max_speed(.1), max_turn(30), x_prev(0), z_prev(0)
{
    wheels[0] = Tire();
    wheels[1] = Tire();
    wheels[2] = Tire();
    wheels[3] = Tire();

    wheels[0].set_position(-2.0,-1.0,2.0);
    wheels[1].set_position(2.0,-1.0,2.0);
    wheels[2].set_position(-2.0,-1.0,-2.0);
    wheels[3].set_position(2.0,-1.0,-2.0);

    doors[0] = Door();
    doors[1] = Door();

    doors[0].set_open_out(true);
    doors[1].set_open_out(false);

    doors[0].set_position(1.0,0.0,-1.5);
    doors[1].set_position(1.0,0.0,1.5);

    my_weapon = Weapon();
    my_weapon.set_model("hammer.obj");
}

Robot::~Robot()
{}

void Robot::collision(){
    if(rand()%10 < 5 and speed > .5*max_speed) snap_item();
    move_back();
    speed *= -.5;
}
void Robot::draw(double counter,bool up, bool down, bool left, bool right, bool left_open, bool right_open, bool attack){
    //this updates the x and y coordinates given the car's speed and direction
    x_prev = x_pos;
    z_prev = z_pos;

    x_pos += speed*cos(direction*0.0174532925);
    z_pos -= speed*sin(direction*0.0174532925);

    speed *= .997; //friction effect (slows down over time)
    turn *= .99;   //friction effect, (wheels realign over time)

    //change Robot's direction based on speed and wheel angle
    direction += 11*speed*sin(turn*0.0174532925);

    //fix the direction to keep nice ranges
    while(direction > 360)
        direction -= 360;
    while(direction < 0)
        direction += 360;

    if(up)
        if(speed < max_speed)
            speed += .002;   //accelerate

    if(down){
        if(speed > -max_speed)
            speed -= .002;   //decelerate
    }

    if(left xor right){       //won't turn left AND right
        if(left){
            if(turn < max_turn)     //max turn angle
                turn += 0.4;  //turn speed left
        }
        if(right){
            if(turn > -max_turn)
                turn -= 0.4;  //turn speed right
        }
    }

    //draw doors where they fell off, not with car
    if(doors[0].free) doors[0].draw(false);
    if(doors[1].free) doors[1].draw(false);

    //tires
    if(wheels[0].free) wheels[0].draw(0,0);
    if(wheels[1].free) wheels[1].draw(0,0);
    if(wheels[2].free) wheels[2].draw(0,0);
    if(wheels[3].free) wheels[3].draw(0,0);

    glPushMatrix();
        glTranslatef(x_pos, y_pos, z_pos);
        glRotatef(direction, 0, 1, 0);

        //weapon
        my_weapon.update(attack);

        //tires
        if(not wheels[0].free) wheels[0].draw(speed,0);
        if(not wheels[1].free) wheels[1].draw(speed,turn);
        if(not wheels[2].free) wheels[2].draw(speed,0);
        if(not wheels[3].free) wheels[3].draw(speed,turn);

        //doors
        //draw doors with the car
        if(not doors[0].free) doors[0].draw(left_open);
        if(not doors[1].free) doors[1].draw(right_open);

        //body
        glPushMatrix();
            glColor3f(.3, .3, .5);
            glScalef(1.5, .5, 1);
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
void Robot::snap_item(){
    if(rand()%10 < 2)
    switch(rand()%6){
        case 0:
            if(not wheels[0].free){
                wheels[0].break_off(x_pos,y_pos,z_pos);
                max_speed *= .6;
            }
            break;
        case 1:
            if(not wheels[1].free){
                wheels[1].break_off(x_pos,y_pos,z_pos);
                max_turn *= .6;
            }
            break;
        case 2:
            if(not wheels[2].free){
                wheels[2].break_off(x_pos,y_pos,z_pos);
                max_speed *= .6;
            }
            break;
        case 3:
            if(not wheels[3].free){
                wheels[3].break_off(x_pos,y_pos,z_pos);
                max_turn *= .6;
            }
            break;
        case 4:
            if(not doors[0].free)
                doors[0].break_off(x_pos,y_pos,z_pos);
            break;
        case 5:
            if(not doors[1].free)
                doors[1].break_off(x_pos,y_pos,z_pos);
            break;
        default: break;
    }
}
void Robot::move_back(){
    x_pos = x_prev;
    z_pos = z_prev;
}
bool Robot::attacking(){
    return my_weapon.is_active();
}
