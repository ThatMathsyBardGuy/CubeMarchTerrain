#include "Renderer.h"

namespace rendering {

	Renderer::Renderer(GLFWwindow& parent) : m_Parent(&parent) {
		m_CurrentShader = new Shader();
	}

	Renderer::~Renderer() {
		delete m_CurrentShader;
		m_Objects.clear();
	}

	void Renderer::AddObject(RenderObject* object) {
		m_Objects.push_back(object);
	}

	void Renderer::RenderObjects() {
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glUseProgram(m_CurrentShader->GetProgram());
		for (RenderObject* object : m_Objects) {
			object->Draw();
		}
		glfwSwapBuffers(m_Parent);
		glUseProgram(0);
	}
}