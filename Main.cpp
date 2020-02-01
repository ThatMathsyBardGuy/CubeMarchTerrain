#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>

#include <gtc/matrix_transform.hpp>
#include <gtx/rotate_vector.hpp>

#include "Renderer.h"

#define CAMERA_SPEED 3
#define CAMERA_TILT_SPEED 1
#define MOUSE_SENSITIVITY 0.5f

void ProcessInput(GLFWwindow* window, std::map<int, bool>& buttonstates) {
	for (std::map<int, bool>::iterator it = buttonstates.begin(); it != buttonstates.end(); it++) {
		it->second = glfwGetKey(window, it->first) == GLFW_PRESS;
	}
}

///@MAGIC NUMBER this needs to always  be the center of the window
float lastX = 400, lastY = 300;
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	float xOffset = xpos - lastX;
	float yOffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	xOffset *= MOUSE_SENSITIVITY;
	yOffset *= MOUSE_SENSITIVITY;

}


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glewInit();

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	glfwSetCursorPosCallback(window, mouse_callback);
	
	glViewport(0, 0, 800, 600);

	glClearColor(0.1, 0.2, 0.2, 1.0);

	rendering::Renderer renderer = rendering::Renderer(*window);

	rendering::Camera* camera = renderer.GetCamera();
	
	rendering::Mesh* quad = rendering::Mesh::GenerateQuad();
	rendering::RenderObject renderObject(quad);

	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(1, 1, 2));
	transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(0, 0, 1));
	
	rendering::RenderObject renderObject2(quad, transform);

	renderer.AddObject(&renderObject);
	renderer.AddObject(&renderObject2);

	std::map<int, bool> buttonStates;
	buttonStates.insert(std::pair<int, bool>(GLFW_KEY_0, false));
	buttonStates.insert(std::pair<int, bool>(GLFW_KEY_ESCAPE, false));
	buttonStates.insert(std::pair<int, bool>(GLFW_KEY_R, false));
	buttonStates.insert(std::pair<int, bool>(GLFW_KEY_D, false));
	buttonStates.insert(std::pair<int, bool>(GLFW_KEY_F, false));
	buttonStates.insert(std::pair<int, bool>(GLFW_KEY_G, false));
	buttonStates.insert(std::pair<int, bool>(GLFW_KEY_SPACE, false));
	buttonStates.insert(std::pair<int, bool>(GLFW_KEY_X, false));
	buttonStates.insert(std::pair<int, bool>(GLFW_KEY_UP, false));
	buttonStates.insert(std::pair<int, bool>(GLFW_KEY_DOWN, false));
	buttonStates.insert(std::pair<int, bool>(GLFW_KEY_LEFT, false));
	buttonStates.insert(std::pair<int, bool>(GLFW_KEY_RIGHT, false));

	float currentTime, lastTime, dt;
	
	lastTime = glfwGetTime();
	currentTime = glfwGetTime();

	float cameraSpeed;
	float tiltSpeed;
	glm::vec3 cameraRight;

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		lastTime = currentTime;
		currentTime = glfwGetTime();
		dt = currentTime - lastTime;

		cameraSpeed = CAMERA_SPEED * dt;
		tiltSpeed = CAMERA_TILT_SPEED * dt;

		cameraRight = glm::normalize(glm::cross(camera->GetForward(), camera->GetUp()));
		
		if (buttonStates.at(GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(window, true);

		if (buttonStates.at(GLFW_KEY_R)) camera->SetPosition(camera->GetPosition() + cameraSpeed * camera->GetForward());
		if (buttonStates.at(GLFW_KEY_F)) camera->SetPosition(camera->GetPosition() - cameraSpeed * camera->GetForward());
		if (buttonStates.at(GLFW_KEY_D)) camera->SetPosition(camera->GetPosition() - cameraSpeed * cameraRight);
		if (buttonStates.at(GLFW_KEY_G)) camera->SetPosition(camera->GetPosition() + cameraSpeed * cameraRight);
		if (buttonStates.at(GLFW_KEY_SPACE))  camera->SetPosition(camera->GetPosition() + cameraSpeed * camera->GetUp());
		if (buttonStates.at(GLFW_KEY_X))  camera->SetPosition(camera->GetPosition() - cameraSpeed * camera->GetUp());

		if (buttonStates.at(GLFW_KEY_UP)) camera->SetForward(glm::rotate(camera->GetForward(), tiltSpeed, cameraRight));
		if (buttonStates.at(GLFW_KEY_DOWN)) camera->SetForward(glm::rotate(camera->GetForward(), -tiltSpeed, cameraRight));
		
		if (buttonStates.at(GLFW_KEY_LEFT)) camera->SetForward(glm::rotate(camera->GetForward(), tiltSpeed, camera->GetUp()));
		if (buttonStates.at(GLFW_KEY_RIGHT)) camera->SetForward(glm::rotate(camera->GetForward(), -tiltSpeed, camera->GetUp()));
		
		renderer.RenderObjects();
		glfwPollEvents();
		ProcessInput(window, buttonStates);
	}

	return 0;
}

