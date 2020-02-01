#pragma once

#include <glm.hpp>

namespace rendering {
	class Camera
	{
	public:
		Camera();
		Camera(glm::vec3 position, glm::vec3 lookat = glm::vec3(0, 0, 1), glm::vec3 up = glm::vec3(0, 1, 0));
		~Camera();

		void SetPosition(glm::vec3 position) { m_Position = position; };
		void SetForward(glm::vec3 forward) { m_Forward = forward; }
		void SetUp(glm::vec3 up) { m_Up = up; }

		glm::mat4 BuildViewMatrix();
		
	protected:
		glm::vec3 m_Position;
		glm::vec3 m_Forward;
		glm::vec3 m_Up;
	};
}

