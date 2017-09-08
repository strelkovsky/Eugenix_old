#include "Includes.h"
#include "Shader.h"

GLuint CreateShader(GLenum type, const char* source)
{
	auto glShader = glCreateShader(type);
	glShaderSource(glShader, 1, &source, nullptr);
	glCompileShader(glShader);

	return glShader;
}

void DeleteShader(GLuint glShader)
{
	glDeleteShader(glShader);
}

bool CheckShader(GLuint glShader)
{
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(glShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(glShader, 512, NULL, infoLog);
		printf("Shader compilation failed - %s\n", infoLog);
		return false;
	}

	return true;
}

GLuint CreateProgram(GLuint vertexShader, GLuint fragmentShader)
{
	auto shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	return shaderProgram;
}

void UseProgram(GLuint glProgram)
{
	glUseProgram(glProgram);
}

void UnuseProgram()
{
	glUseProgram(0);
}

void SetUniform(GLuint glProgram, const char* name, const glm::mat4& mat)
{
	auto transformLoc = glGetUniformLocation(glProgram, name);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mat));
}