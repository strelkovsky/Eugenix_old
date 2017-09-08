#pragma once

#include "Buffer.h"
#include "Vertex.h"

struct Mesh
{
	Mesh(const BufferPtr& vertexBuffer, const std::vector<VertexAttribute>& vertexAttributes, const BufferPtr& indexBuffer, uint32_t indexSize, uint32_t indexCount);

	// TODO : replace with gatherRenderOps
	void Draw();

private:
	struct glVertexAttrib
	{
		GLint size;
		GLenum type;
		GLboolean normalized;
		GLsizei stride;
		const GLvoid* pointer;
	};

	BufferPtr  _vertexBuffer;
	BufferPtr _indexBuffer;
	std::vector<glVertexAttrib> _vertexAttribs;

	uint32_t _indexCount = 0;
	GLenum _indexType = 0;

public:
	GLuint _vertexArrayId = 0;
};
using MeshPtr = std::shared_ptr<Mesh>;