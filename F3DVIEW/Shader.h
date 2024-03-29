#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Shader
{
public:
	int programID;

public:
	bool isDebug{ true };

public:

	Shader(const char* vertexPath,const char* fragmentPath);
	~Shader();

	void Use();
	void Delete();
private:
	std::string getContentFile(const char* filePath);

	void checkCompileError(unsigned int shader, std::string type);

public:

	// GLSL Shader Function 
    void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
    void setVec2(const std::string& name, const glm::vec2& value);
    void setVec2(const std::string& name, float x, float y);
    void setVec3(const std::string& name, const glm::vec3& value);
    void setVec3(const std::string& name, float x, float y, float z);
    void setVec4(const std::string& name, const glm::vec4& value);
    void setVec4(const std::string& name, float x, float y, float z, float w);
    void setMat2(const std::string& name, const glm::mat2& mat);
    void setMat3(const std::string& name, const glm::mat3& mat);
	void setMat4(const std::string& name, const glm::mat4& mat);


};

