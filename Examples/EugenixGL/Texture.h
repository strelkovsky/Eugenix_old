#pragma once

#include "Image.h"

struct Texture final
{
	Texture();
	~Texture();
	
	void UploadData(const ImagePtr& image);

	void Bind();
	void Unbind();

private:
	GLuint _glTexture = 0;
};
using TexturePtr = std::shared_ptr<Texture>;