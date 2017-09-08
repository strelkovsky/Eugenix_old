
#include "Includes.h"

#include "Core/Debug/Debug.h"
#include "Platform/Runtime.h"

#include "App/App.h"

#include "Buffer.h"
#include "Image.h"
#include "Vertex.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"

#include "Camera.h"

using namespace Eugenix;

class Example : public App
{
protected:
	virtual bool OnInit() 
	{ 
		_camera = Perspective(glm::radians(45.0f), (float)Runtime::Setup().width / (float)Runtime::Setup().height, 0.1f, 100.0f);
		_camera->LookAt(glm::vec3(0, -3, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		_camera->SetClearMask(ClearBits::All);
		_camera->SetClearColor(Color{ 0.2f, 0.3f, 0.3f, 1.0f });

		_projView = _camera->GetProjection() * _camera->GetView();

		auto texture = std::make_shared<Texture>();
		texture->UploadData(ImageLoader::LoadImage("texture.tga"));

		auto renderObject = std::make_shared<RenderObject>();
		renderObject->mesh = MeshBuilder::CreateCube();
		renderObject->program = ShaderEnv::Defaults::SimpleDiffuse();
		renderObject->texture = texture;
		renderObject->transform.model = glm::rotate(renderObject->transform.model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		renderObject->transform.model = glm::translate(renderObject->transform.model, glm::vec3(1.0f, 0.0f, 0.0f));
		_renderQueue.Push(renderObject);
		
		auto renderObject2 = std::make_shared<RenderObject>();
		renderObject2->mesh = MeshBuilder::CreateCube();
		renderObject2->program = ShaderEnv::Defaults::SimpleDiffuse();
		renderObject2->texture = texture;
		renderObject2->transform.model = glm::rotate(renderObject2->transform.model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		renderObject2->transform.model = glm::translate(renderObject2->transform.model, glm::vec3(-1.0f, 0.0f, 0.0f));
		_renderQueue.Push(renderObject2);

		glEnable(GL_DEPTH_TEST);

		return true;
	}

	virtual void OnShutdown()
	{
	}

	virtual void OnRender()
	{
		_renderer.Draw(_camera, _renderQueue);
	}

private:
	
	CameraPtr _camera;
	Renderer _renderer;
	RenderQueue _renderQueue;
	
	glm::mat4 _projView;
};

int main()
{
	Example app;
	return app.Run();
}