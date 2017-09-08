
#include <string>

#define GLEW_STATIC
#include "../3rdParty/glew/include/gl/glew.h"

#include "../3rdParty/glm/glm.hpp"
#include "../3rdParty/glm/gtc/matrix_transform.hpp"
#include "../3rdParty/glm/gtc/type_ptr.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../3rdParty/stb_image.h"

#include "Core/Debug/Debug.h"
#include "Platform/Runtime.h"

#include "App/App.h"

using namespace Eugenix;

glm::mat4 model;
glm::mat4 view;
glm::mat4 proj;

GLuint _tex;

GLuint CreateTexture(const std::string& name)
{
	GLuint _tex;
	
	int width, height, comp;
	unsigned char* data = stbi_load(name.c_str(), &width, &height, &comp, STBI_rgb);
	
	glGenTextures(1, &_tex);
	glBindTexture(GL_TEXTURE_2D, _tex);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	if (comp == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	else if (comp == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	
	glGenerateMipmap(GL_TEXTURE_2D);
	
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);
	
	return _tex;
}

class Example : public App
{
protected:
	virtual bool OnInit() 
	{ 
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, -4.0f));
		proj = glm::perspective(glm::radians(45.0f), 800.f / 600.f, 0.1f, 100.0f);

		const GLchar* vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 position;\n"
			"layout (location = 1) in vec2 texCoord;\n"
			"uniform mat4 model;\n"
			"uniform mat4 view;\n"
			"uniform mat4 projection;\n"
			"out vec2 TexCoord;\n"
			"void main()\n"
			"{\n"
			"gl_Position = projection * view * model * vec4(position, 1.0f);\n"
			"TexCoord = texCoord;\n"
			"}\0";
		const GLchar* fragmentShaderSource = "#version 330 core\n"
			"in vec2 TexCoord;\n"
			"out vec4 color;\n"
			"uniform sampler2D ourTexture;\n"
			"void main()\n"
			"{\n"
			"color = texture(ourTexture, TexCoord);\n"
			"}\n\0";

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		GLint success;
		GLchar infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			Debug::Error("Vertex shader compilation failed - %s\n", infoLog);

			// TODO : use default material & don't stop init
			return false;
		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			Debug::Error("Fragment shader compilation failed - %s\n", infoLog);

			// TODO : use default material & don't stop init
			return false;
		}

		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			Debug::Error("Shader program linking failed - %s\n", infoLog);

			// TODO : use default material & don't stop init
			return false;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		glUseProgram(shaderProgram);
		
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(proj));
		
		glUseProgram(0);

		GLfloat points[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0,                   // number of attribute
			3,                   // size of "pos" (vec3) 
			GL_FLOAT,            // type of "pos"
			GL_FALSE,            // do not normalize
			5 * sizeof(GLfloat),   // step between vertex (pos - 3, uv - 2)
			(GLvoid*)0);         // offset


		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1,                   // number of attribute
			2,                   // size of "uv" (vec2) 
			GL_FLOAT,            // type of "uv"
			GL_FALSE,            // do not normalize
			5 * sizeof(GLfloat), // step between vertex (pos - 3, uv - 2)
			(GLvoid*)(3 * sizeof(GLfloat))); // offset (after pos)

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		_tex = CreateTexture("grid.png");

		glEnable(GL_DEPTH_TEST);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		return true;
	}

	virtual void OnShutdown()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);

		glDeleteProgram(shaderProgram);
	}

	virtual void OnRender()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _tex);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);
		glUseProgram(0);
	}

private:
	GLuint VBO, VAO, EBO;
	GLuint shaderProgram;
};

int main()
{
	Example app;
	return app.Run();
}