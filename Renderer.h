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
		Renderer(GLFWwindow& parent, Shader* shader = new Shader());
		~Renderer();

		Camera* GetCamera() { return m_Camera; }
		void SetCamera(Camera* camera) { m_Camera = camera; }
		
		void SetCurrentShader(Shader* shader) { m_Shader = shader; }

		void AddObject(RenderObject* object);

		void RenderObjects();

	protected:
		void SortObjectsByDepth();

		Camera* m_Camera;
		
		std::vector<RenderObject*> m_Objects;

		GLFWwindow* m_Parent;

		Shader* m_Shader;

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
	};
}
