#version 440 core

// INPUT AND UNIFORMS
layout(location = 0) uniform vec3 uColor;


// OUTPUT
out vec4 color;

void main(){
  color = vec4(1.0f,0.0f,1.0f,1.0f);
}