#include <GL/glut.h>
#include <cmath>
#include "weapon.h"
//Jorge
//this is the weapon class implementation

Weapon::Weapon()
:part_a(gluNewQuadric()),part_b(gluNewQuadric()), part_c(gluNewQuadric()),red(.6), green(.6), blue(0),
 rel_x(0), rel_y(0), rel_z(0), value(0), weapon_index(0), attack_power(10), attack_speed(10), animation_speed(1),
 knock_back(0), adhesion(0), recoil(0), reboot_timer(10), current_index(0), max_index(10), free(false), active(false)
{}
Weapon::~Weapon()
{
    gluDeleteQuadric(part_a);
    gluDeleteQuadric(part_b);
    gluDeleteQuadric(part_c);
}

void Weapon::update(bool toggle){
    draw();
}
void Weapon::draw(){
    /*
    glPushMatrix();
        glTranslatef(rel_x, rel_y, rel_z);
        glColor3f(red, green, blue);
        switch(weapon_index){
            case 0:
                glScalef(3, 3, 3);
                gluCylinder(part_a, .5, .5, 1, 6, 1);

                glTranslatef(-1, 0, 0);
                glScalef(value, value, value);
                gluCylinder(part_a, .5, .5, 1, 6, 1);
            break;
        }
    glPopMatrix();
    */
}
