#include "Camera.h"

Camera::Camera(GLFWwindow* pwindow,Shader& refShader)
	: window{ pwindow } , mainShader { refShader }
{
	projection = glm::perspective(glm::radians(45.f), float(800 / 600), 0.1f, 100.f);
	mainShader.setMat4("projection", projection);

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	mainShader.setMat4("view", view);
}

void Camera::cameraPreviewCircle()
{
	glm::mat4 view = glm::mat4(1.0f);
	float radius = 10.f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;

	view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	mainShader.setMat4("view", view);
}

void Camera::updateCamera(float& deltaTime)
{
	MovementCamera(deltaTime);


	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	mainShader.setMat4("view", view);
}

void Camera::MovementCamera(float& deltaTime)
{
	float updateSpeed = cameraSpeed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}


