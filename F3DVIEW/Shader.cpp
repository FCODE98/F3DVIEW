#include "Shader.h"


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	this->isDebug = isDebug;

	std::string vertexContent = getContentFile(vertexPath);
	std::string fragmentContent = getContentFile(fragmentPath);

	if (isDebug)
	{
		std::cout << "[DEUBG SHADER READER]" << std::endl;
		std::cout << vertexContent << std::endl;
		std::cout << fragmentContent << std::endl;
	}
	

	const char* vertexSource = vertexContent.c_str();
	const char* fragmentSource = fragmentContent.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, 0);
	glCompileShader(vertexShader);
	checkCompileError(vertexShader, "VERTEX_SHADER");

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, 0);
	glCompileShader(fragmentShader);
	checkCompileError(fragmentShader, "FRAGMENT_SHADER");

	programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);
	checkCompileError(programID, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


}



Shader::~Shader()
{
	
}



void Shader::Use()
{
	glUseProgram(programID);
}

void Shader::Delete()
{
	glDeleteProgram(programID);
}


std::string  Shader::getContentFile(const char* filePath)
{
	std::ifstream hFile(filePath, std::ios::binary);
	std::string content;
	if (hFile)
	{
		std::string temp;

		while (std::getline(hFile,temp))
		{
			content += temp + "\n";
		}

		return content;
	}
	throw(errno);

}

void Shader::checkCompileError(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, 0, infoLog);
			std::cout << "Error::SHADER_COMPILATION_ERROR of type : " << type << "\n" << infoLog << std::endl;
			std::cout << "-----------------------------" << std::endl;

		}
	}
	else
	{
		glGetShaderiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, 0, infoLog);
			std::cout << "Error::SHADER_COMPILATION_ERROR of type : " << type << "\n" << infoLog << std::endl;
			std::cout << "-----------------------------" << std::endl;
		}
	}
}

void Shader::setBool(const std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value)
{
	glUniform2fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string& name, float x, float y)
{
	glUniform2f(glGetUniformLocation(programID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value)
{
	glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(programID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value)
{
	glUniform4fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(programID, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string& name, const glm::mat2& mat)
{
	glUniformMatrix2fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string& name, const glm::mat3& mat)
{
	glUniformMatrix3fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat)
{
	glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
