#include "shaders.h"
#include <GL/gl.h>
#include <glad/glad.h>

using namespace Shaders;

ShaderProgram ShaderProgram::create(std::string vertexPath, std::string fragmentPath)
{
    return ShaderProgram(vertexPath,fragmentPath);
}

Shaders::ShaderProgram::ShaderProgram(std::string vertexPath, std::string fragmentPath)
{
    vertexShader = glad_glCreateShader(GL_VERTEX_SHADER);
}
