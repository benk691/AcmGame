#include "gl_camera.h"

#include <cmath>

#include <GL/gl.h>

void gl_camera::set_elevation(float deg)
{
    float new_deg = deg;

    // get the remainder
    new_deg = new_deg - (int)(new_deg / 360.0) * 360.0;

    if (new_deg > 0)
    {
        if (new_deg > 180.0)
            new_deg = new_deg - 360;
    }
    else
    {
        if (new_deg < -180.0)
            new_deg =  new_deg + 360;

    }

    this->elevation = new_deg;
}

float gl_camera::get_elevation() const
{
    return this->elevation;
}

// the number of degrees about the z-axis
void gl_camera::set_twist(float deg)
{
    float new_deg = deg;

    // get the remainder
    new_deg = new_deg - (int)(new_deg / 360.0) * 360.0;

    if (new_deg > 0)
    {
        if (new_deg > 180.0)
            new_deg = new_deg - 360;
    }
    else
    {
        if (new_deg < -180.0)
            new_deg =  new_deg + 360;

    }

    this->twist = new_deg;
}

float gl_camera::get_twist() const
{
    return this->twist;
}

void gl_camera::set_distance(float distance)
{
    this->distance = distance;
}

float gl_camera::get_distance() const
{
    return distance;
}

void gl_camera::set_focal_point(const vector3& focal_point)
{
    this->focal_point = focal_point;
}
void gl_camera::set_focal_point(double x, double y, double z)
{
    this->focal_point[0] = x;
    this->focal_point[1] = y;
    this->focal_point[2] = z;
}

vector3 gl_camera::get_focal_point() const
{
    return focal_point;
}

#define PI 3.14159265358979323846264338328

vector3 gl_camera::get_position() const
{
    vector3 p;

    float t1, t2;
    float b;

    p[2] = get_distance();
    p[0] = p[1] = 0.0;

    // rotate about x
    b = -get_elevation() / 180.0 * PI;
    t1 = cos(b)*p[1] - sin(b)*p[2];
    t2 = sin(b)*p[1] + cos(b)*p[2];

    p[1] = t1;
    p[2] = t2;

    // rotate about y
    b = get_twist() / 180.0 * M_PI;
    t1 = cos(b)*p[0] + sin(b)*p[2];
    t2 = -sin(b)*p[0] + cos(b)*p[2];

    p[0] = t1;
    p[2] = t2;

    // translate
    p.add(get_focal_point());
    return p;
}

vector3 gl_camera::get_target() const
{
    vector3 tar;
    tar.set(get_focal_point());
    tar.sub(get_position());
    tar.normalize();
    return tar;
}

vector3 gl_camera::get_up() const
{
    vector3 up;
    up = get_right().cross(get_target());//up.cross(get_right(), get_target());
    return up;
}

vector3 gl_camera::get_right() const
{
    vector3 Y(0,1,0);
    vector3 right;
    right = get_target().cross(Y);//right.cross(get_target(), Y);
    right.normalize();
    return right;
}

void gl_camera::apply_gl_transform()
{
    glTranslated(0.0, 0.0, -this->distance);
    glRotated(-this->get_elevation(), -1.0, 0.0, 0.0);
    glRotated(-this->get_twist(), 0.0, 1.0, 0.0);
    glTranslated(
        -this->focal_point[0], -this->focal_point[1], -this->focal_point[2]
    );
}
