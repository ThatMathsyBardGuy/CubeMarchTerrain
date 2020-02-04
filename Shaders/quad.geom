#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 6) out;

in vec4 vertexColour;

out vec4 geomColour;

void main() {
	gl_Position = gl_in[0].gl_Position + vec4(-1, 1, 0.0, 0.0);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(1, 1, 0.0, 0.0);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(-1, -1, 0.0, 0.0);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(1, -1, 0.0, 0.0);
	EmitVertex();
	EndPrimitive();
}