#pragma once

#include <vector>
#include <string>
#include <glm.hpp>
#include <GL/glew.h>

#include "Vertex.h"

namespace rendering {
	class Mesh {
	public:
		Mesh(std::vector<rendering::Vertex> vertices, std::vector<GLuint> indices, std::string name = "Unnamed Mesh");
		~Mesh();

		static Mesh* GenerateQuad();

		GLuint GetVAO() { return m_VAO; }
		
		void SetIndices(std::vector<GLuint> indices) { m_Indices = indices; }
		std::vector<GLuint> GetIndices() { return m_Indices; }

		void SetVertices(std::vector<rendering::Vertex> vertices) { m_Vertices = vertices; }

		void BufferData();
	protected:
		std::vector<rendering::Vertex> m_Vertices;
		std::vector<GLuint> m_Indices;

		GLuint m_VBO, m_IBO, m_VAO;

		std::string m_Name;
	};
}