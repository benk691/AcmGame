#include <GL/glut.h>
#include <cmath>
#include "weapon.h"
//Jorge
//this is the weapon class implementation

Weapon::Weapon()
:model(Mesh()), red(.8), green(.8), blue(.3),
 rel_x(-1), rel_y(0), rel_z(0), value(0), weapon_index(0), attack_power(10), attack_speed(10), animation_speed(1),
 knock_back(0), adhesion(0), recoil(0), reboot_timer(10), current_index(0), max_index(10), free(false), active(false)
{}
Weapon::~Weapon()
{}
void Weapon::set_model(char * file_name){
    model.load(file_name);
}
void Weapon::update(bool toggle){
    if(active){
        current_index += .25;
        if(current_index >= max_index)
            active = false;
    }
    else
    if(current_index > 0){
        current_index -= .25;
    }
    else
    if(toggle)
        active = true;

    draw(-100*current_index/max_index);
}
void Weapon::draw(float angle){
    glPushMatrix();
        glRotatef(angle, 0,0,1);
        glTranslatef(rel_x, rel_y, rel_z);
        glColor3f(red, green, blue);
        model.draw();
    glPopMatrix();
}
bool Weapon::is_active(){
    return active;
}
