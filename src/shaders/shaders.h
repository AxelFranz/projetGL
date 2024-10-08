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
        public:
            GLuint programID;
            void create(const char* vertexPath, const char* fragmentPath);
            ShaderProgram() {};
    };
}