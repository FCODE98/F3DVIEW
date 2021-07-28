#pragma once



#include "Shader.h"

class Texture
{
public:
	GLuint textureID;
	GLenum type;
	Texture(const char* imagePath, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	void texUnit(Shader& shader, const char* uniform, GLuint init);
	void Bind();
	void Unbind();
	void Delete();

};

