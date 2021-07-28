#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &ID);
}

void VAO::LinkVBO(VBO &VBO, GLuint layout)
{
	VBO.Bind();
	if (layout == 0)
		glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	else if (layout == 1)
		glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	else if(layout == 2)
		glVertexAttribPointer(layout, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}
