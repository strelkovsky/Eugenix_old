#include "Includes.h"
#include "Shader.h"

void CheckShader(GLuint glShader)
{
	GLint success;
	glGetShaderiv(glShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLint infoLogLength;
		glGetShaderiv(glShader, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> infoLog(std::max(infoLogLength, int(1)));
		glGetShaderInfoLog(glShader, 512, NULL, infoLog.data());
		printf("Shader compilation failed - %s\n", infoLog.data());
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
	glGetProgramiv(_glProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLint infoLogLength;
		glGetProgramiv(_glProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> infoLog(std::max(infoLogLength, int(1)));
		glGetProgramInfoLog(_glProgram, 512, NULL, infoLog.data());
		printf("Program linking failed - %s\n", infoLog.data());
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