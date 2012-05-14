#ifndef POINT3_H
#define POINT3_H

#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>

class vector3
{
public:
    vector3()
    {
        set(0, 0, 0);
    }
    
    vector3(const vector3& v)
    {
        set(v[0], v[1], v[2]);
    }

    vector3(float x, float y, float z)
    {
        set(x, y, z);
    }

    vector3(const float u[3])
    {
        memcpy(p, u, 3 * sizeof(float));
    }

    float& operator[](int index)
    {
        assert(index >= 0 && index < 3);

        return p[index];
    }

    const float& operator[](int index) const
    {
        assert(index >= 0 && index < 3);

        return p[index];
    }

    float x() const { return p[0]; }
    float y() const { return p[1]; }
    float z() const { return p[2]; }
    
    void set(const vector3& v) 
    { 
        p[0] = v[0]; p[1] = v[1]; p[2] = v[2];
    }
    
    void set(float x, float y, float z) 
    { 
        p[0] = x; p[1] = y; p[2] = z;
    }

    void add(const vector3& v) 
    {
        p[0] += v[0]; p[1] += v[1]; p[2] += v[2];
    }

    void sub(const vector3& v) 
    {
        p[0] -= v[0]; p[1] -= v[1]; p[2] -= v[2];
    }

    void scale(float s) 
    {
        p[0] *= s; p[1] *= s; p[2] *= s;
    }

    float mag() const 
    {
        return sqrt(p[0]*p[0] + p[1]*p[1] + p[2]*p[2]);
    }

    void normalize() 
    {
        float m = mag();
        assert(m > 0);
        scale(1/m);
    }

    vector3 cross(const vector3& v) const
    {
        return vector3(p[1]*v[2] - v[1]*p[2],
                       p[2]*v[0] - v[0]*p[2],
                       p[0]*v[1] - v[1]*p[0]);
    }
    
    /*
    void cross(const vector3& u, const vector3& v) {
        p[0] = u[1]*v[2] - u[2]*v[1]; 
        p[1] = u[2]*v[0] - u[0]*v[2]; 
        p[2] = u[0]*v[1] - u[1]*v[0]; 
    }*/
    
    vector3& operator=(const vector3& v) 
    {
        set(v);
        return *this;
    }
    
    vector3 operator+(const vector3& v) const 
    {
        vector3 u(*this);
        u.add(v);
        return u;
    }

    vector3 operator-(const vector3& v) const 
    {
        vector3 u(*this);
        u.sub(v);
        return u;
    }

    vector3 operator*(float s) const 
    {
        vector3 u(*this);
        u.scale(s);
        return u;
    }

    vector3 operator/(float s) const 
    {
        vector3 u(*this);
        assert(s != 0);
        u.scale(1.0/s);
        return u;
    }


private:
    float p[3];

}; 

inline vector3 operator*(float s, const vector3& u) 
{
    vector3 v;
    v.set(u);
    v.scale(s);
    return v;
}

inline std::ostream& operator<<(std::ostream& ostr, const vector3& u)
{
    ostr << u[0] << " " << u[1] << " " << u[2];
    return ostr;
}

#endif
