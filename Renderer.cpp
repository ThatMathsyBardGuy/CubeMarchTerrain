#include "Renderer.h"

#include <gtc/type_ptr.hpp>
#include <algorithm>

namespace rendering {

	Renderer::Renderer(GLFWwindow& parent, Shader* shader) : m_Parent(&parent) {
		m_Shader = shader;
		m_Camera = new Camera();
		m_ViewMatrix = m_Camera->BuildViewMatrix();

		m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		glEnable(GL_DEPTH_TEST);
	
	}

	Renderer::~Renderer() {
		delete m_Shader;
		m_Objects.clear();
	}

	void Renderer::AddObject(RenderObject* object) {
		m_Objects.push_back(object);
	}

	void Renderer::SortObjectsByDepth() {
		for (RenderObject* obj : m_Objects) {
			glm::mat4 transform = obj->GetTransform();
			float transformValues[16];
			const float* transformPointer = (const float*)glm::value_ptr(transform);
			for (int i = 0; i < 16; i++) {
				transformValues[i] = transformPointer[i];
			}
			glm::vec3 position = glm::vec3(transformValues[12], transformValues[13], transformValues[14]);
			obj->SetCameraDistance(glm::dot(position, position));
		}
		std::sort(m_Objects.begin(), m_Objects.end(), RenderObject::CompareByDepth);
	}

	void Renderer::RenderObjects() {
		SortObjectsByDepth();

		m_ViewMatrix = m_Camera->BuildViewMatrix();
		
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glUseProgram(m_Shader->GetProgram());
		glUniformMatrix4fv(glGetUniformLocation(m_Shader->GetProgram(), "viewMatrix"), 1, GL_FALSE, (float*)&m_ViewMatrix);
		glUniformMatrix4fv(glGetUniformLocation(m_Shader->GetProgram(), "projectionMatrix"), 1, GL_FALSE, (float*)&m_ProjectionMatrix);
		for (RenderObject* object : m_Objects) {
			glm::mat4 transform = object->GetTransform();
			glUniformMatrix4fv(glGetUniformLocation(m_Shader->GetProgram(), "modelMatrix"), 1, GL_FALSE, (float*)&transform);
			object->Draw();
		}
		glfwSwapBuffers(m_Parent);
		glUseProgram(0);
	}
}