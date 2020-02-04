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
#include "CubeMarchMap.h"

#define CAMERA_SPEED 3
#define CAMERA_TILT_SPEED 1
#define MOUSE_SENSITIVITY 0.5f

#define SHADERDIR "Shaders/"

rendering::RenderObject* GenerateCubeMarchNodeVisualisation(cubemarch::CubeMarchMap* map) {
	std::vector<rendering::Vertex> vertices;
	std::vector<unsigned int> indices;
	vertices.resize(map->GetNumOfNodes());
	indices.resize(vertices.size());
	for (int i = 0; i < vertices.size(); i++) {
		cubemarch::CubeMarchNode node = map->GetNodes()[i];
		vertices.at(i) = rendering::Vertex({ (GLfloat)node.x, (GLfloat)node.y, (GLfloat)node.z, 0, 0, node.weight, node.weight, node.weight, 1, 0, 0, 0 });
		indices.at(i) = i;
	}
	rendering::Mesh* mesh = new rendering::Mesh(vertices, indices, "CubeMarch mesh");
	rendering::RenderObject* renderObject = new rendering::RenderObject(mesh);
	renderObject->SetDrawMode(GL_POINTS);
	return renderObject;
}

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

	rendering::Shader defaultShader = rendering::Shader(std::string(SHADERDIR"default.vert"), std::string(SHADERDIR"default.frag"));
	rendering::Shader pointquadShader = rendering::Shader(std::string(SHADERDIR"pointquad.vert"), std::string(SHADERDIR"pointquad.frag"), std::string(SHADERDIR"pointquad.geom"));

	rendering::Renderer renderer = rendering::Renderer(*window, &pointquadShader);

	rendering::Camera* camera = renderer.GetCamera();

	cubemarch::CubeMarchMap cubeMarchMap(10, 10, 10);

	rendering::RenderObject* cubeMarchRenderObject = GenerateCubeMarchNodeVisualisation(&cubeMarchMap);

	renderer.AddObject(cubeMarchRenderObject);

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
		glfwSwapBuffers(window);
		glfwPollEvents();
		ProcessInput(window, buttonStates);
	}

	return 0;
}

