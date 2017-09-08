#define GLEW_STATIC
#include "../3rdParty/glew/include/gl/glew.h"

#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "../3rdParty/stb_image.h"

#include "Texture.h"

GLuint CreateTexture(const std::string& name)
{
	GLuint _tex;

	int width, height, comp;
	unsigned char* data = stbi_load(name.c_str(), &width, &height, &comp, STBI_rgb);

	glGenTextures(1, &_tex);
	glBindTexture(GL_TEXTURE_2D, _tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if (comp == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	else if (comp == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);

	return _tex;
}