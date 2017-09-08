#pragma once

#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

//-----------------------------------------------------
// Forward declaration
//-----------------------------------------------------
struct Camera;

struct Frame
{
	glm::mat4 model;
};

struct RenderObject
{
	virtual ~RenderObject() {}

	virtual void Draw()
	{
		texture->Bind();
		mesh->Draw();
		texture->Unbind();
	}

	ProgramPtr program;
	TexturePtr texture;

	MeshPtr mesh;

	Frame transform;
};
using RenderObjectPtr = std::shared_ptr<RenderObject>;

struct RenderQueue
{
	void Push(RenderObjectPtr& ro)
	{
		robjs.push_back(ro);
	}

	void Clear()
	{
		robjs.clear();
	}

	const std::vector<RenderObjectPtr> GetRobjs() const { return robjs; }

private:
	std::vector<RenderObjectPtr> robjs;
};

struct RenderTarget
{
};

class Renderer
{
public:
	void Draw(const CameraPtr& cam, const RenderQueue& rq)
	{
		Color c = cam->GetClearColor();
		glClearColor(c.r, c.g, c.b, c.a);
		
		uint32_t flags = cam->GetClearMask();
		
		GLbitfield glMask = 0;
		if (flags & ClearBits::ColorBit)
			glMask |= GL_COLOR_BUFFER_BIT;
		if (flags & ClearBits::DepthBit)
			glMask |= GL_DEPTH_BUFFER_BIT;
		
		glClear(glMask);
		
		auto projView = cam->GetProjection() * cam->GetView();
		
		for (const auto ro : rq.GetRobjs())
		{
			ro->program->SetUniform("mvp", projView * ro->transform.model);
			ro->Draw();
			ro->program->Unbind();
		}
	}
};