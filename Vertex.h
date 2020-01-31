#pragma once

#include <glm.hpp>

namespace rendering {
	struct Vertex {
		GLfloat x;
		GLfloat y;
		GLfloat z;
		
		GLfloat u;
		GLfloat v;

		GLfloat r;
		GLfloat g;
		GLfloat b;
		GLfloat a;

		GLfloat nx;
		GLfloat ny;
		GLfloat nz;
	};
}