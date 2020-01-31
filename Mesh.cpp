#include "Mesh.h"

namespace rendering {
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::string name) : m_Vertices(vertices), m_Indices(indices), m_Name(name) {
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_IBO);
		glGenVertexArrays(1, &m_VAO);
		BufferData();
	}

	Mesh::~Mesh() {
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_IBO);
		glDeleteVertexArrays(1, &m_VAO);
	}

	Mesh* Mesh::GenerateQuad() {
		std::vector<Vertex> verts;
		verts.resize(4);
		verts[0] = { -1, -1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0 };
		verts[1] = { -1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0 };
		verts[2] = { 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 };
		verts[3] = { 1, -1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0 };


		std::vector<GLuint> ind = { 0, 2, 1, 0, 3, 2 };

		Mesh* m = new Mesh(verts, ind, "Quad");

		return m;
	}

	void Mesh::BufferData() {

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(GLuint), m_Indices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), m_Vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);						//x, y, z
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));	// u, v
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(5 * sizeof(GLfloat)));	// r, g, b, a
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(9 * sizeof(GLfloat)));	// nx, ny, nz

		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}