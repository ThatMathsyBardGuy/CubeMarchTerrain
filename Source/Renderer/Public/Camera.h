#pragma once

#include <glm.hpp>

namespace rendering {
	class Camera
	{
	public:
		Camera();
		Camera(glm::vec3 position, glm::vec3 lookat = glm::vec3(0, 0, 1), glm::vec3 up = glm::vec3(0, 1, 0));
		~Camera();

		void SetPosition(glm::vec3 position) { m_Position = position; }
		glm::vec3 GetPosition() { return m_Position; }
		
		void SetForward(glm::vec3 forward) { m_Forward = forward; }
		glm::vec3 GetForward() { return m_Forward; }
		
		void SetUp(glm::vec3 up) { m_Up = up; }
		glm::vec3 GetUp() { return m_Up; }

		glm::mat4 BuildViewMatrix();
		
	protected:
		glm::vec3 m_Position;
		glm::vec3 m_Forward;
		glm::vec3 m_Up;
	};
}

