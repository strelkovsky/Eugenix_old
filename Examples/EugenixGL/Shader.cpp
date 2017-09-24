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

	CheckShader(glShader);

	return glShader;
}

static std::map<std::string, GLint> GetUniformLocations(GLuint program)
{
	int numUni = -1;
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &numUni);

	std::map<std::string, GLint> outUniforms;

	for (int i = 0; i < numUni; ++i)
	{
		int namelen;
		int num;
		GLenum type;
		char name[128];

		glGetActiveUniform(program, static_cast<GLuint>(i), sizeof(name) - 1, &namelen, &num, &type, name);
		name[namelen] = 0;
		GLuint location = glGetUniformLocation(program, name);
		outUniforms[name] = location;
	}
	return outUniforms;
}

namespace ShaderEnv
{
	GLuint currentProgram = -1;

	namespace Defaults
	{
		ProgramPtr SimpleDiffuse()
		{
			static ProgramPtr simpleDiffuseProgram = nullptr;
			if (simpleDiffuseProgram == nullptr)
			{
				const char* vsSource = R"(
				#version 330 core
				layout (location = 0) in vec3 position;
				layout (location = 1) in vec2 texCoord;
				uniform mat4 mvp;
				out vec2 TexCoord;
				void main()
				{
					gl_Position = mvp * vec4(position, 1.0f);
					TexCoord = texCoord;
				})";

				const char* fsSource = R"(
				#version 330 core
				in vec2 TexCoord;
				out vec4 color;
				uniform sampler2D ourTexture;
				void main()
				{
					color = texture(ourTexture, TexCoord);
				})";

				simpleDiffuseProgram = std::make_shared<ShaderProgram>(vsSource, fsSource);
				//glBindAttribLocation(simpleDiffuseProgram, StandartAttribs::PositionAttrib, "position");
				//glBindAttribLocation(simpleDiffuseProgram, StandartAttribs::UvAttrib, "uv");
			}
			return simpleDiffuseProgram;
		}
	} // namespace Defaults
} // namespace ShaderEnv

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

	_uniformLocations = GetUniformLocations(_glProgram);
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(_glProgram);
}

void ShaderProgram::Bind()
{
	glUseProgram(_glProgram);
}

void ShaderProgram::Unbind()
{
	glUseProgram(0);
}

void ShaderProgram::SetUniform(const char* name, const glm::mat4& mat)
{
	if (ShaderEnv::currentProgram != _glProgram)
		Bind();

	glUniformMatrix4fv(_uniformLocations[name], 1, GL_FALSE, glm::value_ptr(mat));
}