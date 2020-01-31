#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>

#include "Renderer.h"

void ProcessInput(GLFWwindow* window, std::map<int, bool>& buttonstates) {
	for (std::map<int, bool>::iterator it = buttonstates.begin(); it != buttonstates.end(); it++) {
		it->second = glfwGetKey(window, it->first) == GLFW_PRESS;
	}
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

	glViewport(0, 0, 800, 600);

	glClearColor(0.1, 0.2, 0.2, 1.0);

	rendering::Renderer renderer = rendering::Renderer(*window);

	rendering::Mesh* quad = rendering::Mesh::GenerateQuad();
	rendering::RenderObject renderObject(quad);

	renderer.AddObject(&renderObject);

	bool renderThings = true;

	std::map<int, bool> buttonStates;
	buttonStates.insert(std::pair<int, bool>(GLFW_KEY_0, false));
	buttonStates.insert(std::pair<int, bool>(GLFW_KEY_ESCAPE, false));

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		if (buttonStates.at(GLFW_KEY_0)) renderThings = !renderThings;
		if (buttonStates.at(GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(window, true);
		if (renderThings) renderer.RenderObjects();
		glfwPollEvents();
		ProcessInput(window, buttonStates);
	}

	return 0;
}