#version 330 core

in vec4 vertexColour;
in vec3 viewSpacePosition;

out vec4 fragColor;

void main() {
	vec3 xTangent = dFdx(viewSpacePosition);
	vec3 yTangent = dFdy(viewSpacePosition);
	vec3 faceNormal = normalize(cross(xTangent, yTangent));
	
	vec3 lightDir = normalize(vec3(-1, -1, -1));
	
	fragColor = vec4(faceNormal, 1.0);
}