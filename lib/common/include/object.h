#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
//#include "mesh.h"

class Object
{
    public:
        static unsigned int curObjId;
        double x;
        double y;
        double z;
        double pitch;
        double roll;
        double yaw;
        //Mesh mesh;
        const unsigned int objId;

    public:
        Object();

        virtual ~Object() {};

        virtual void draw() = 0;

        virtual void update() = 0;
};

#endif //__OBJECT_H__
