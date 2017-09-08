#pragma once

static const GLchar* diffuseVs = "#version 330 core\n"
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

static const GLchar* diffuseFs = "#version 330 core\n"
"in vec2 TexCoord;\n"
"out vec4 color;\n"
"uniform sampler2D ourTexture;\n"
"void main()\n"
"{\n"
"color = texture(ourTexture, TexCoord);\n"
"}\n\0";

struct ShaderProgram final
{
	ShaderProgram(const char* vsSource, const char* fsSource);
	~ShaderProgram() {}

	void Use();
	void Unuse();
	
	void SetUniform(const char* name, const glm::mat4& mat);
	
private:
	GLuint _glProgram;
};
using ProgramPtr = std::shared_ptr<ShaderProgram>;