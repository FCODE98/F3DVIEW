#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION 

#include <stb/stb_image.h>


Texture::Texture(const char* imagePath, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	int textureWidth, textureHeight, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(imagePath, &textureWidth, &textureHeight, &numColCh, 0);
	if (bytes == nullptr)
	{
		std::cout << "Cannot load Texture file." << std::endl;
	}
	else
	{
		std::cout << "Load image file successful." << std::endl;
	}

	glGenTextures(1, &textureID);
	glActiveTexture(slot);
	glBindTexture(texType, textureID);

	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(texType, 0, format, textureWidth, textureHeight, 0, format, pixelType, bytes);
	glGenerateMipmap(texType);

	stbi_image_free(bytes);
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	GLuint texUnit = glGetUniformLocation(shader.programID, uniform);

	shader.Use();
	glUniform1i(texUnit, unit);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &textureID);
}
