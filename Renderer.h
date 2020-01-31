#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "RenderObject.h"
#include "Shader.h"

namespace rendering {

	class Renderer
	{
	public:
		Renderer(GLFWwindow& parent);
		~Renderer();

		void SetCurrentShader(Shader* shader) { m_CurrentShader = shader; }

		void AddObject(RenderObject* object);

		void RenderObjects();

	protected:
		std::vector<RenderObject*> m_Objects;

		GLFWwindow* m_Parent;

		Shader* m_CurrentShader;
	};
}
