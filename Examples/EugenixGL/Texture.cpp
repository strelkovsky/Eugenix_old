#include "Includes.h"
#include "Image.h"
#include "Texture.h"

Texture::Texture()
{
	glGenTextures(1, &_glTexture);
}

Texture::~Texture()
{
	glDeleteTextures(1, &_glTexture);
}

void Texture::UploadData(const ImagePtr& image)
{
	Bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if (image->Comp() == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->Width(), image->Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->Data().data());
	else if (image->Comp() == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->Width(), image->Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->Data().data());

	glGenerateMipmap(GL_TEXTURE_2D);

	Unbind();
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _glTexture);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}