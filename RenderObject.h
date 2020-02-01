#pragma once

#include "Mesh.h"

namespace rendering {
	class RenderObject
	{
	public:
		RenderObject(Mesh* mesh, glm::mat4 transform = glm::mat4(1.0f), std::string name = "Unnamed Render Object");
		~RenderObject();

		void SetDrawMode(GLuint mode) { m_DrawType = mode; }

		glm::mat4 GetTransform() { return m_Transform; }

		void Draw();
	protected:
		Mesh* m_Mesh;
		glm::mat4 m_Transform;
		GLuint m_DrawType;

		std::string m_Name;
	};
}