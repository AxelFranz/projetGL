#pragma once
#include <string>
#include <GL/gl.h>
#define SHADER_PATH "src/shaders/programs/"

namespace Shaders {
    class ShaderProgram {
        private: 
            GLuint vertexShader;
            GLuint fragmentShader;
        public:
            ShaderProgram create(std::string vertexPath, std::string fragmentPath);
            ShaderProgram(std::string vertexPath, std::string fragmentPath);
    };
}