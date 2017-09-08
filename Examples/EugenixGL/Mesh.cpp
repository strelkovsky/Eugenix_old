#include "Includes.h"
#include "Mesh.h"

Mesh::Mesh(const BufferPtr& vertexBuffer, const std::vector<VertexAttribute>& vertexAttributes, const BufferPtr& indexBuffer, uint32_t indexSize, uint32_t indexCount)
{
	_vertexBuffer = vertexBuffer;
	_indexBuffer = indexBuffer;

	const size_t vertexSize = std::accumulate(vertexAttributes.begin(), vertexAttributes.end(), 0,
		[](size_t size, VertexAttribute attribute) { return size + VertexAttribute::GetTypeSize(attribute.GetAttribType()); });

	switch (indexSize)
	{
	case 2:
		_indexType = GL_UNSIGNED_SHORT;
		break;
	case 4:
		_indexType = GL_UNSIGNED_INT;
		break;
	default:
		_indexType = 0;
		printf("Invalid index size\n");
	}

	GLuint offset = 0;
	_vertexAttribs.clear();
	for (const auto& vertexAttribute : vertexAttributes)
	{
		GLboolean normalized = vertexAttribute.IsNormalized() ? GL_TRUE : GL_FALSE;

		_vertexAttribs.push_back(
		{
			VertexAttribute::GetAttribSize(vertexAttribute.GetAttribType()),
			VertexAttribute::GetAttribType(vertexAttribute.GetAttribType()),
			normalized,
			static_cast<GLsizei>(vertexSize),
			reinterpret_cast<const GLvoid*>(offset)
		});
		offset += VertexAttribute::GetTypeSize(vertexAttribute.GetAttribType());
	}

	if (offset != vertexSize)
	{
		printf("Invalid vertex size\n");
	}

	glGenVertexArrays(1, &_vertexArrayId);
	glBindVertexArray(_vertexArrayId);

	_vertexBuffer->Bind();
	_indexBuffer->Bind();

	for (uint16_t index = 0; index < (uint16_t)VertexAttribute::Usage::Count; ++index)
	{
		if (index < _vertexAttribs.size())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				_vertexAttribs[index].size,
				_vertexAttribs[index].type,
				_vertexAttribs[index].normalized,
				_vertexAttribs[index].stride,
				_vertexAttribs[index].pointer);
		}
		else
		{
			glDisableVertexAttribArray(index);
		}
	}
}

void Mesh::Draw()
{
	glBindVertexArray(_vertexArrayId);

	if (_indexCount > 0)
		glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}
