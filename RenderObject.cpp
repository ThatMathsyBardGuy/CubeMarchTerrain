#include "RenderObject.h"

namespace rendering {
	RenderObject::RenderObject(Mesh* mesh, glm::mat4 transform, std::string name) : m_Mesh(mesh), m_Transform(transform), m_Name(name), m_DrawType(GL_TRIANGLES) {
		m_CameraDistance = 0.0f;
	}

	RenderObject::~RenderObject() {

	}

	void RenderObject::Draw() {
		m_Mesh->BufferData();
		glBindVertexArray(m_Mesh->GetVAO());

		glDrawElements(m_DrawType, m_Mesh->GetIndices().size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}

}