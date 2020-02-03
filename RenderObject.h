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

		void SetCameraDistance(float dist) { m_CameraDistance = dist; }
		float GetCameraDistance() { return m_CameraDistance; }

		virtual void Draw();

		static bool CompareByDepth(RenderObject* a, RenderObject* b) { return a->GetCameraDistance() < b->GetCameraDistance(); }
	
	protected:
		Mesh* m_Mesh;
		glm::mat4 m_Transform;
		GLuint m_DrawType;

		float m_CameraDistance;

		std::string m_Name;

		
	};
	
}