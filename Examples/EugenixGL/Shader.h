#pragma once

struct ShaderProgram final
{
	ShaderProgram(const char* vsSource, const char* fsSource);
	~ShaderProgram();

	void Bind();
	void Unbind();
	
	void SetUniform(const char* name, const glm::mat4& mat);
	
private:
	GLuint _glProgram;
	std::map<std::string, GLint> _uniformLocations;
};
using ProgramPtr = std::shared_ptr<ShaderProgram>;

namespace ShaderEnv
{
	namespace Defaults
	{
		ProgramPtr SimpleDiffuse();
	} // namespace Defaults
} // namespace ShaderEnv