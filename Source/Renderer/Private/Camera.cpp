#include "Camera.h"

#include <gtc/type_ptr.hpp>

#include <iostream>

namespace rendering
{
	Camera::Camera()
	{
		m_Position = glm::vec3(0, 0, -3.0f);
		m_Forward = glm::vec3(0, 0, 1);
		m_Up = glm::vec3(0, 1, 0);
	}

	Camera::Camera(glm::vec3 position, glm::vec3 lookat, glm::vec3 up)
	{
		m_Position = position;
		m_Forward = glm::normalize(lookat);
		m_Up = glm::normalize(up);
	}

	Camera::~Camera()
	{
		
	}

	
	glm::mat4 Camera::BuildViewMatrix()
	{
		//glm::vec3 right = glm::normalize(glm::cross(m_Forward, m_Up));
		//float values[16] = {
		//	right.x, right.y, right.z, 0,
		//	m_Forward.x, m_Forward.y, m_Forward.z, 0,
		//	m_Up.x, m_Up.y, m_Up.z, 0,
		//	m_Position.x, m_Position.y, m_Position.z, 1
		//};
		//glm::mat4 view = glm::make_mat4(values);

		glm::mat4 view = glm::lookAt(m_Position, m_Position + m_Forward, m_Up);

		//glm::mat4 view = glm::mat4(1.0f);
		//view = glm::translate(view, glm::vec3(0, 0, -3.0f));
		
		return view;
	}

}