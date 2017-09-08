#pragma once

enum struct BufferTarget : GLenum
{
	ArrayBuffer = GL_ARRAY_BUFFER,
	ElementArrayBuffer = GL_ELEMENT_ARRAY_BUFFER,
	Uniform = GL_UNIFORM_BUFFER
};

struct Buffer
{
	Buffer(BufferTarget type);
	~Buffer();

	void UploadData(const void* mem, size_t size);

	void Bind();
	void Unbind();

private:
	GLuint _glBuffer = 0;
	BufferTarget _type = BufferTarget::ArrayBuffer;
};
using BufferPtr = std::shared_ptr<Buffer>;