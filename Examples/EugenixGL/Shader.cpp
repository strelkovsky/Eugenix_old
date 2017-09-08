#include "Includes.h"
#include "Shader.h"

void CheckShader(GLuint glShader)
{
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(glShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(glShader, 512, NULL, infoLog);
		printf("Shader compilation failed - %s\n", infoLog);
	}
}

GLuint CreateShader(GLenum type, const char* source)
{
	auto glShader = glCreateShader(type);
	glShaderSource(glShader, 1, &source, nullptr);
	glCompileShader(glShader);

	return glShader;
}

ShaderProgram::ShaderProgram(const char* vsSource, const char* fsSource)
{
	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vsSource);
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fsSource);

	_glProgram = glCreateProgram();
	glAttachShader(_glProgram, vertexShader);
	glAttachShader(_glProgram, fragmentShader);
	glLinkProgram(_glProgram);

	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(_glProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(_glProgram, 512, NULL, infoLog);
		printf("Program linking failed - %s\n", infoLog);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderProgram::Use()
{
	glUseProgram(_glProgram);
}

void ShaderProgram::Unuse()
{
	glUseProgram(0);
}

void ShaderProgram::SetUniform(const char* name, const glm::mat4& mat)
{
	auto transformLoc = glGetUniformLocation(_glProgram, name);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mat));
}