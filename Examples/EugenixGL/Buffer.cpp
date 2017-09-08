#include "Includes.h"

#include "Buffer.h"

Buffer::Buffer(BufferTarget type)
{
	_type = type;
	glGenBuffers(1, &_glBuffer);
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &_glBuffer);
}

void Buffer::UploadData(const void* mem, size_t size)
{
	Bind();
	glBufferData(static_cast<GLenum>(_type), size, mem, GL_STATIC_DRAW);
}

void Buffer::Bind()
{
	glBindBuffer(static_cast<GLenum>(_type), _glBuffer);
}

void Buffer::Unbind()
{
	glBindBuffer(static_cast<GLenum>(_type), 0);
}