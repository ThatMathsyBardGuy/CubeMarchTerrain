#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "Camera.h"
#include "RenderObject.h"
#include "Shader.h"

namespace rendering {

	class Renderer
	{
	public:
		Renderer(GLFWwindow& parent);
		~Renderer();

		Camera* GetCamera() { return m_Camera; }
		
		void SetCurrentShader(Shader* shader) { m_CurrentShader = shader; }

		void AddObject(RenderObject* object);

		void RenderObjects();

	protected:
		Camera* m_Camera;
		
		std::vector<RenderObject*> m_Objects;

		GLFWwindow* m_Parent;

		Shader* m_CurrentShader;

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
	};
}
