#ifndef Mesh_H
#define Mesh_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <cassert>
#include <map>
#include <string>
#include <vector>
#include <iostream>

class Mesh
{
public:
    struct face
    {
        std::string mat;
        std::string group;
        std::vector<int> vind;
        std::vector<int> nind;
        std::vector<int> tex;
    };

    struct material
    {
        material();

        float ka[3], ks[3], kd[3];
        float ns;
        int illum;
        std::string map_ka, map_kd, map_ks;
    };

    Mesh();
    ~Mesh();

    bool load(const std::string& filename);
    void draw();

    inline size_t get_vertex_count() const;
    inline const float* get_vertex(size_t i) const;
    inline size_t get_normal_count() const;
    inline const float* get_normal(size_t i) const;
    inline size_t get_face_count() const;
    inline const face& get_face(size_t i) const;
    inline const material& get_material(
        const std::string& name
        ) const;

private:
    bool load_material(const std::string& filename);

    std::vector<float> verts;
    std::vector<float> norms;
    std::vector<float> tex;
    std::vector<face> faces;
    std::map<std::string, material> mats;
};

size_t Mesh::get_face_count() const
{
    return faces.size();
}

const Mesh::face& Mesh::get_face(size_t i) const
{
    assert(i < faces.size());
    return faces[i];
}

size_t Mesh::get_vertex_count() const
{
    return verts.size() / 3;
}

const float* Mesh::get_vertex(size_t i) const
{
    return &verts[3*i];
}

size_t Mesh::get_normal_count() const
{
    return norms.size() / 3;
}

const float* Mesh::get_normal(size_t i) const
{
    return &norms[3*i];
}

const Mesh::material& Mesh::get_material(
    const std::string& name
    ) const
{
    std::map<std::string, material>::const_iterator i =
        mats.find(name);
    assert(i != mats.end());
    return i->second;
}

#endif
