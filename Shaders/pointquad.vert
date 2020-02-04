#version 330 core

layout (location = 0) in vec3 position;
layout (location = 2) in vec4 colour;

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

void main() {
	mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;
	gl_Position = mvp*vec4(position, 1.0);
}