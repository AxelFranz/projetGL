#pragma once

#include "../include.h"

// TODO all of this shit
namespace Geometry
{

    class VBO
    {
    private:
        GLuint id;
        GLuint numberVertices;

    public:
        VBO(std::vector<vec3> attributes);
        GLuint getID();
        GLuint getNumberVertices();
        VBO create(std::vector<vec3> attributes);
        VBO();
        ~VBO();
    };

    class VAO
    {
    private:
        GLuint id;
        VBO vbo;
    public:
        VAO(VBO vbo);
        VAO();
        void bind();
        void draw();
        ~VAO();
    };

};