#include "geometry.h"

using namespace Geometry;
using namespace std;

VBO::VBO(std::vector<vec3> attributes)
{
    glGenBuffers(1, &id);

    glBindBuffer(GL_ARRAY_BUFFER, id);


    glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(attributes.size()*sizeof(vec3)), attributes.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    numberVertices = attributes.size();
    
    cout << id << endl;
}

GLuint Geometry::VBO::getID()
{
    return id;
}

GLuint Geometry::VBO::getNumberVertices()
{
    return numberVertices;
}

VBO Geometry::VBO::create(std::vector<vec3> attributes)
{
    return VBO(attributes);
}



Geometry::VAO::VAO(VBO vbo)
{
    this->vbo = vbo;
    glGenVertexArrays(1, &id);
    glBindVertexArray(id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo.getID());
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);

    glBindVertexArray(0);
}

void Geometry::VAO::bind()
{
    glBindVertexArray(id);
}

void Geometry::VAO::draw()
{
    // TODO : A changer quand y'aura de l'EBO
    glDrawArrays(GL_TRIANGLES, 0, vbo.getNumberVertices());
    glBindVertexArray(0);
}





Geometry::VAO::VAO()
{
}

Geometry::VAO::~VAO()
{
}

Geometry::VBO::VBO()
{
}

Geometry::VBO::~VBO()
{
}

