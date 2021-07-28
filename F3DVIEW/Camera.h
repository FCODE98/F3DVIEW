#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>


#include "Shader.h"

class Camera
{
	Shader& mainShader;
public:
	GLFWwindow* window;
	Camera(GLFWwindow* window,Shader& mainShader);

public:
	glm::mat4 view;
	glm::mat4 projection;

	float cameraSpeed = 0.01f;


	// Camera Setting
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


	// Testing & Show
	void cameraPreviewCircle();



	// Update EveryFrame to update Camera movement
	void updateCamera(float& deltaTime);
	

private:
	void MovementCamera(float& deltaTime);
};

