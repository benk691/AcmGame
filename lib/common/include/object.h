#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "mesh.h"

class Object
{
    public:
        static unsigned int objId = 0;
        double x;
        double y;
        double z;
        double pitch;
        double roll;
        double yaw;
        const unsigned int id;

    public:
        Object();

        virtual ~Object() = 0;

        virtual void draw() = 0;

        virtual void update() = 0;
};

#endif //__OBJECT_H__
