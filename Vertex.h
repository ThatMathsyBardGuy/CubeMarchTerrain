#pragma once

#include <glm.hpp>

namespace rendering {
	struct Vertex {
		GLfloat x, y, z;
		GLfloat u, v;
		GLfloat r, g, b, a;
		GLfloat nx, ny, nz;
	};
}