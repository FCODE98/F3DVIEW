#define STB_IMAGE_IMPLEMENTATION   



#include <iostream>
#include <chrono>
#include <ctime>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#include "Texture.h"

#include "Camera.h"


using namespace std;

auto currentTime = glfwGetTime();

void OnResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void OnKeyboardCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
	
	static bool bXrayMode = false;


	
	if (currentTime + 0.4 < glfwGetTime())
	{
		if (key == GLFW_KEY_X)
		{
			currentTime = glfwGetTime();
			bXrayMode = !bXrayMode;


			if (bXrayMode)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
		}
	}

	
}

int main()
{
	glfwInit();
	
	// define version of opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLfloat vertices[] = {
		-0.5f,-0.5f,0.5f,		1.0f,0.0f,0.0f,			0.f,0.f,	// front left	0
		0.5f,-0.5f,0.5f,		0.0f,1.0f,0.0f,			5.f,0.f,	// front right	1
		-0.5f,-0.5f,-0.5f,		0.0f,0.0f,1.0f,			5.f,0.f,	// back left	2
		0.5f,-0.5f,-0.5f,		1.0f,1.0f,0.0f,			0,0,		// back right	3
		0.0f,0.5f,0.0f,			1.0f,1.0f,1.0f,			2.5f,5.0f,	// top center	4
	};

	GLuint indices[] =
	{
		0,1,2,
		1,2,3,
		0,1,4,
		1,3,4,
		2,3,4,
		0,2,4
	};


	glm::vec3 cubePosition[] =
	{
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	// manage windows
	GLFWwindow* m_window = glfwCreateWindow(800,600,"F3DVIEW",nullptr,nullptr);
	if (m_window == nullptr)
	{
		std::cout << "failed to init glfwCreateWindow()" << std::endl;
		glfwTerminate();
		return -1;
	}

	// make context render to window
	glfwMakeContextCurrent(m_window);

	// load glad func
	gladLoadGL();

	glfwSetKeyCallback(m_window, OnKeyboardCallback);
	glfwSetFramebufferSizeCallback(m_window, OnResizeCallback);

	glViewport(0, 0, 800, 600);


	Shader mainShader{ "Default.vs","Default.fs" };

	VAO vao;
	vao.Bind();

	VBO vbo{ vertices,sizeof(vertices) };
	EBO ebo{ indices,sizeof(indices) };

	vao.LinkVBO(vbo, 0);
	vao.LinkVBO(vbo, 1);
	vao.LinkVBO(vbo, 2);

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
	

	Texture mainTexture{ "Textures//brick.jpg",GL_TEXTURE_2D,GL_TEXTURE0,GL_RGB,GL_UNSIGNED_BYTE };
	mainTexture.texUnit(mainShader, "tex0", 0);
	
	

	glEnable(GL_DEPTH_TEST);

	// Camera setting
	Camera mainCamera{ m_window , mainShader };

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	while (!glfwWindowShouldClose(m_window))
	{
		// Update Framerate to control program with deltaTime
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Clear Buffer with Color
		glClearColor(0.3f, 0.4f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		mainShader.Use();
		mainCamera.updateCamera(deltaTime);


		// Add Many Cube in My Map
		vao.Bind();
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePosition[i]);
			float angle = 20.f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
			mainShader.setMat4("model", model);

			glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
		}

		mainTexture.Bind();


		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	glfwDestroyWindow(m_window);
	glfwTerminate();
}