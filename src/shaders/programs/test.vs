#version 330 core

layout(location = 0) in vec3 position_in;

void main(void) {
    gl_Position = position_in;
}

