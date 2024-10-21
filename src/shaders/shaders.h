#pragma once
#include "../include.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

const std::string SHADER_PATH = ".\\..\\src\\shaders\\programs\\";

namespace Shaders {
    class ShaderProgram {
        private: 
            GLuint programID;
            void create(const char* vertexPath, const char* fragmentPath);
        public:
            void bind();
            void path(const char* vertexPath, const char* fragmentPath);
            ShaderProgram() {};
    };
}