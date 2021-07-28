#pragma once

#include <glad/glad.h>
#include "VBO.h"

class VAO
{
public:
	GLuint ID;

	VAO();
	~VAO();

	void LinkVBO(VBO& VBO, GLuint layout);
	void Bind();
	void Unbind();


};

