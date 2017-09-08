#include "../3rdParty/glew/include/gl/glew.h"

#include "Buffer.h"

GLuint CreateBuffer(GLenum type, const void* mem, size_t size)
{
	GLuint glBuffer;

	glGenBuffers(1, &glBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, glBuffer);
	glBufferData(GL_ARRAY_BUFFER, size, mem, GL_STATIC_DRAW);

	return glBuffer;
}