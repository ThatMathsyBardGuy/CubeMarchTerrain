#include "Renderer.h"

#include <gtc/type_ptr.hpp>

namespace rendering {

	Renderer::Renderer(GLFWwindow& parent) : m_Parent(&parent) {
		m_CurrentShader = new Shader();
		m_Camera = new Camera();
		m_ViewMatrix = m_Camera->BuildViewMatrix();

		m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	
	}

	Renderer::~Renderer() {
		delete m_CurrentShader;
		m_Objects.clear();
	}

	void Renderer::AddObject(RenderObject* object) {
		m_Objects.push_back(object);
	}

	void Renderer::RenderObjects() {
		m_ViewMatrix = m_Camera->BuildViewMatrix();
		
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glUseProgram(m_CurrentShader->GetProgram());
		glUniformMatrix4fv(glGetUniformLocation(m_CurrentShader->GetProgram(), "viewMatrix"), 1, GL_FALSE, (float*)&m_ViewMatrix);
		glUniformMatrix4fv(glGetUniformLocation(m_CurrentShader->GetProgram(), "projectionMatrix"), 1, GL_FALSE, (float*)&m_ProjectionMatrix);
		for (RenderObject* object : m_Objects) {
			glm::mat4 transform = object->GetTransform();
			glUniformMatrix4fv(glGetUniformLocation(m_CurrentShader->GetProgram(), "modelMatrix"), 1, GL_FALSE, (float*)&transform);
			object->Draw();
		}
		glfwSwapBuffers(m_Parent);
		glUseProgram(0);
	}
}