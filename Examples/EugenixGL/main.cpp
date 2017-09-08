
#include "Includes.h"

#include "Core/Debug/Debug.h"
#include "Platform/Runtime.h"

#include "App/App.h"

#include "Buffer.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

using namespace Eugenix;

template<typename T>
size_t GetVectorSize(const typename std::vector<T> &vec)
{
	return sizeof(T) * vec.size();
}

class Example : public App
{
protected:
	virtual bool OnInit() 
	{ 
		_model = glm::rotate(_model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		_view = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, -4.0f));
		_proj = glm::perspective(glm::radians(45.0f), 800.f / 600.f, 0.1f, 100.0f);

		_program = std::make_shared<ShaderProgram>(diffuseVs, diffuseFs);
		_program->Use();
		_program->SetUniform("model", _model);
		_program->SetUniform("view", _view);
		_program->SetUniform("projection", _proj);
		_program->Unuse();

		glGenVertexArrays(1, &_meshVao);
		glBindVertexArray(_meshVao);
		
		_vertexBuffer = CreateBuffer(GL_ARRAY_BUFFER, cubeVertices.data(), GetVectorSize(cubeVertices));

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

		glBindVertexArray(0);

		_tex = CreateTexture("grid.png");

		glEnable(GL_DEPTH_TEST);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		return true;
	}

	virtual void OnShutdown()
	{
		glDeleteVertexArrays(1, &_meshVao);
		glDeleteBuffers(1, &_vertexBuffer);
	}

	virtual void OnRender()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_program->Use();
		glBindVertexArray(_meshVao);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _tex);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);
		_program->Unuse();
	}

private:
	GLuint _vertexBuffer = 0;
	GLuint _meshVao = 0;

	GLuint _tex;
	ProgramPtr _program;
	
	glm::mat4 _model;
	glm::mat4 _view;
	glm::mat4 _proj;
};

int main()
{
	Example app;
	return app.Run();
}