#ifndef GL_CAMERA_H
#define GL_CAMERA_H

#include "vector3.h"

class gl_camera
{
public:
    gl_camera() : distance(50.0),
        elevation(0.0), twist(0.0),
        focal_point(0.0, 0.0, 0.0)
    {}

    void set_elevation(float deg);
    float get_elevation() const;

    void set_twist(float deg);
    float get_twist() const;

    void set_distance(float d);
    float get_distance() const;

    void set_focal_point(const vector3& focal_point);
    void set_focal_point(double x, double y, double z);
    vector3 get_focal_point() const;

    vector3 get_position() const;

    vector3 get_target() const;
    vector3 get_up() const;
    vector3 get_right() const;

    void apply_gl_transform();

private:
    float distance;
    float elevation, twist;
    vector3 focal_point;

};

#endif
