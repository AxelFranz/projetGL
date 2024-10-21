#version 440 core

layout(location = 0) in vec3 position_in;

void main(void) {
    gl_Position = vec4(position_in,1.0f);
}

