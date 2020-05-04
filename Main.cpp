#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <PerlinNoise.hpp>

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

#include <gtc/matrix_transform.hpp>
#include <gtx/rotate_vector.hpp>

#include "Renderer.h"
#include "CubeMarchMap.h"
#include "ComputeShader.h"

#define CAMERA_SPEED 3
#define CAMERA_TILT_SPEED 1
#define MOUSE_SENSITIVITY 0.5f

#define SHADERDIR "Shaders/"

void GenerateCubeMarchNodeVisualisation(cubemarch::CubeMarchMap* map, float surfacelevel, rendering::RenderObject& object) {
	std::vector<rendering::Vertex> vertices;
	std::vector<unsigned int> indices;
	for (int i = 0; i < map->GetNumOfNodes(); i++) {
		cubemarch::CubeMarchNode node = map->GetNodes()[i];
		if (node.weight > surfacelevel) {
			indices.push_back(vertices.size());
			vertices.emplace_back(rendering::Vertex({ (GLfloat)node.x, (GLfloat)node.y, (GLfloat)node.z, 0, 0, node.weight, node.weight, node.weight, 1.0, 0, 0, 0 }));
		}
	}
	object.GetMesh()->SetVertices(vertices);
	object.GetMesh()->SetIndices(indices);
	object.SetDrawMode(GL_POINTS);
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
	std::vector<rendering::Vertex> test;
	std::cout << test.max_size() << std::endl;
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

	glClearColor(0.1, 0.3, 0.2, 1.0);

	rendering::Shader defaultShader = rendering::Shader(std::string(SHADERDIR"default.vert"), std::string(SHADERDIR"default.frag"));
	rendering::Shader flatshadeShader = rendering::Shader(std::string(SHADERDIR"flatshading.vert"), std::string(SHADERDIR"flatshading.frag"));
	rendering::Shader pointquadShader = rendering::Shader(std::string(SHADERDIR"pointquad.vert"), std::string(SHADERDIR"pointquad.frag"), std::string(SHADERDIR"pointquad.geom"));

	rendering::Renderer nodeRenderer = rendering::Renderer(*window, &pointquadShader);
	rendering::Renderer terrainRenderer = rendering::Renderer(*window, &flatshadeShader);

	rendering::Camera* camera = nodeRenderer.GetCamera();

	//TODO this is a messy way of syncing the cameras, make a better one?
	delete terrainRenderer.GetCamera();
	terrainRenderer.SetCamera(camera);

	cubemarch::CubeMarchMap cubeMarchMap(50, 50, 50);

	std::map<int, bool> buttonStates;
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
	buttonStates.insert(std::pair<int, bool>(GLFW_KEY_EQUAL, false));
	buttonStates.insert(std::pair<int, bool>(GLFW_KEY_MINUS, false));
	buttonStates.insert(std::pair<int, bool>(GLFW_KEY_1, false));
	buttonStates.insert(std::pair<int, bool>(GLFW_KEY_2, false));

	float currentTime, lastTime, dt;
	
	lastTime = glfwGetTime();
	currentTime = glfwGetTime();

	float cameraSpeed;
	float tiltSpeed;
	glm::vec3 cameraRight;

	float surfaceLevel = 0.5f;
	float surfaceIncrement = 0.10f;

	bool usegpu = false;

	rendering::RenderObject cubeMarchRenderObject(rendering::Mesh::GenerateQuad(), glm::mat4(1.0f), "CubeMarch Visualiser"); 
	GenerateCubeMarchNodeVisualisation(&cubeMarchMap, surfaceLevel, cubeMarchRenderObject);
	nodeRenderer.AddObject(&cubeMarchRenderObject);

	rendering::Mesh* terrainMesh = rendering::Mesh::GenerateQuad();
	rendering::RenderObject terrainRenderObject(terrainMesh);
	cubeMarchMap.GenerateMesh(surfaceLevel, *terrainMesh, usegpu);
	terrainRenderer.AddObject(&terrainRenderObject);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		GenerateCubeMarchNodeVisualisation(&cubeMarchMap, surfaceLevel, cubeMarchRenderObject);


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

		if (buttonStates.at(GLFW_KEY_1)) {
			usegpu = false;
			float gentimestart = glfwGetTime();
			cubeMarchMap.GenerateMesh(surfaceLevel, *terrainMesh, usegpu);
			float gentime = glfwGetTime() - gentimestart;
			std::cout << "CPU: " << gentime << std::endl;
		}

		if (buttonStates.at(GLFW_KEY_2)) {
			usegpu = true;
			float gentimestart = glfwGetTime();
			cubeMarchMap.GenerateMesh(surfaceLevel, *terrainMesh, usegpu);
			float gentime = glfwGetTime() - gentimestart;
			std::cout << "GPU: " << gentime << std::endl;
		}

		if (buttonStates.at(GLFW_KEY_EQUAL)) {
			surfaceLevel = std::min(surfaceLevel + surfaceIncrement * dt, 1.0f);
			float gentimestart = glfwGetTime();
			cubeMarchMap.GenerateMesh(surfaceLevel, *terrainMesh, usegpu);
			float gentime = glfwGetTime() - gentimestart;
			usegpu ? std::cout << "GPU: " << gentime << std::endl : std::cout << "CPU: " << gentime << std::endl;
		}
		if (buttonStates.at(GLFW_KEY_MINUS)) {
			surfaceLevel = std::max(surfaceLevel - surfaceIncrement * dt, 0.0f);
			float gentimestart = glfwGetTime();
			cubeMarchMap.GenerateMesh(surfaceLevel, *terrainMesh, usegpu);
			float gentime = glfwGetTime() - gentimestart;
			usegpu ? std::cout << "GPU: " << gentime << std::endl : std::cout << "CPU: " << gentime << std::endl;
		}

		nodeRenderer.RenderObjects();
		terrainRenderer.RenderObjects();
		glfwSwapBuffers(window);
		glfwPollEvents();
		ProcessInput(window, buttonStates);
	}

	return 0;
}

