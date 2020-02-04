#version 330 core

layout (points) in;

layout (triangle_strip, max_vertices = 11) out;

in vec4 pointColour[];

out vec4 vertexColour;

void main() {
	vertexColour = pointColour[0];
	
	float t = (1.0 + 2.2360679775) / 2.0;	// 1 + sqrt(5)/2
	
	vec4 center = gl_in[0].position;
	
	//http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html
	
	vec4 p0 = center + vec4(-1.0, t, 0.0, 1.0);
	vec4 p1 = center + vec4(1.0, t, 0.0, 1.0);
	vec4 p2 = center + vec4(-1.0, -t, 0.0, 1.0);
	vec4 p3 = center + vec4(1.0, -t, 0.0, 1.0);
	
	vec4 p4 = center + vec4(0.0, -1.0, t, 1.0);
	vec4 p5 = center + vec4(0.0, 1.0, t, 1.0);
	vec4 p6 = center + vec4(0.0, -1.0, -t, 1.0);
	vec4 p7 = center + vec4(0.0, 1.0, -t, 1.0);
	
	vec4 p8 = center + vec4(t, 0.0, -1.0, 1.0);
	vec4 p9 = center + vec4(t, 0.0, 1.0, 1.0);
	vec4 p10 = center + vec4(-t, 0.0, -1.0, 1.0);
	vec4 p11 = center + vec4(-t, 0.0, 1.0, 1.0);
	
	// Center Strip
	gl_Position = p0;
	EmitVertex();
	gl_Position = p11;
	EmitVertex();
	gl_Position = p5;
	EmitVertex();
	gl_Position = p4;
	EmitVertex();
	gl_Position = p9;
	EmitVertex();
	gl_Position = p3;
	EmitVertex();
	gl_Position = p8;
	EmitVertex();
	gl_Position = p6;
	EmitVertex();
	gl_Position = p7;
	EmitVertex();
	gl_Position = p10;
	EmitVertex();
	gl_Position = p0;
	EmitVertex();
	EndPrimitive();
	
	// Top
	gl_Position = p0;
	EmitVertex();
	gl_Position = p1;
	EmitVertex();
	gl_Position = p5;
	EmitVertex();
	EndPrimitive();
	
	gl_Position = p5;
	EmitVertex();
	gl_Position = p1;
	EmitVertex();
	gl_Position = p9;
	EmitVertex();
	EndPrimitive();
	
	gl_Position = p9;
	EmitVertex();
	gl_Position = p1;
	EmitVertex();
	gl_Position = p8;
	EmitVertex();
	EndPrimitive();
	
	gl_Position = p8;
	EmitVertex();
	gl_Position = p1;
	EmitVertex();
	gl_Position = p7;
	EmitVertex();
	EndPrimitive();
	
	gl_Position = p7;
	EmitVertex();
	gl_Position = p1;
	EmitVertex();
	gl_Position = p0;
	EmitVertex();
	EndPrimitive();
	
	
	// Bottom
	gl_Position = p2;
	EmitVertex();
	gl_Position = p10;
	EmitVertex();
	gl_Position = p11;
	EmitVertex();
	EndPrimitive();
	
	gl_Position = p2;
	EmitVertex();
	gl_Position = p11;
	EmitVertex();
	gl_Position = 4;
	EmitVertex();
	EndPrimitive();
	
	gl_Position = 2;
	EmitVertex();
	gl_Position = p4;
	EmitVertex();
	gl_Position = p3;
	EmitVertex();
	EndPrimitive();
	
	gl_Position = p2;
	EmitVertex();
	gl_Position = p3;
	EmitVertex();
	gl_Position = p6;
	EmitVertex();
	EndPrimitive();
	
	gl_Position = p2;
	EmitVertex();
	gl_Position = p6;
	EmitVertex();
	gl_Position = p10;
	EmitVertex();
	EndPrimitive();
	
}











