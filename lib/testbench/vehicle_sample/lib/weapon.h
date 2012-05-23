#ifndef WEAPON_H
#define WEAPON_H

#include <GL/glut.h>
#include <cmath>

class Weapon
{
    public :
        Weapon();
        ~Weapon();
        void draw();
        void update(bool toggle);
        void activate();
    private :
        GLUquadricObj *part_a;
        GLUquadricObj *part_b;
        GLUquadricObj *part_c;
        double red;
        double green;
        double blue;

        double rel_x;
        double rel_y;
        double rel_z;

        unsigned int value;
        unsigned int weapon_index;

        unsigned int attack_power;
        unsigned int attack_speed;
        double animation_speed;

        unsigned int knock_back;
        unsigned int adhesion;
        unsigned int recoil;

        unsigned int reboot_timer;

        double current_index;
        double max_index;
        bool free;
        bool active;
};

#endif
