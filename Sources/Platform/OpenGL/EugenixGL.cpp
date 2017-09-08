//-----------------------------------------------------------------------------
// Eugenix Framework
// Copyright (C) strelkovsky.com, Inc.
//-----------------------------------------------------------------------------

#include "EugenixGL.h"

#ifdef EUGENIX_OPENGL

#include "Core/Debug/Debug.h"

#define OPENGL_INT_PRINT_DEBUG(name) \
	GLint info_ ## name; \
	glGetIntegerv(name, &info_ ## name); \
	Debug::Msg(#name " = %d\n", info_ ## name);

namespace Eugenix
{
	namespace EugenixGL
	{
		bool Init()
		{
#ifdef EUGENIX_DEBUG
			Debug::Msg("Init dbg");
#else
			Debug::Msg("Init");
#endif

#ifdef EUGENIX_OPENGL_GLEW

			glewExperimental = GL_TRUE;

			GLenum result = glewInit();
			if (GLEW_OK != result)
			{
				Debug::Fatal("glewInit error: %s\n", glewGetErrorString(result));
				return false;
			}

#elif EUGENIX_OPENGL_NATIVE

#endif //EUGENIX_OPENGL_GLEW

#ifdef EUGENIX_DEBUG

			Debug::Msg("[ OpenGL dumps ]\n");

	#ifdef EUGENIX_OPENGL_GLEW
			Debug::Msg("Use GLEW impl. Version - %s\n", glewGetString(GLEW_VERSION));
	#elif EUGENIX_OPENGL_NATIVE
			Debug::Msg("Use navive gl impl\n");
	#endif 

			GLint major, minor;
			glGetIntegerv(GL_MAJOR_VERSION, &major);
			glGetIntegerv(GL_MINOR_VERSION, &minor);
			Debug::Msg("OpenGL render context information:\n"
				"  Renderer       : %s\n"
				"  Vendor         : %s\n"
				"  Version        : %s\n"
				"  GLSL version   : %s\n"
				"  OpenGL version : %d.%d\n\n",
				(const char*)glGetString(GL_RENDERER),
				(const char*)glGetString(GL_VENDOR),
				(const char*)glGetString(GL_VERSION),
				(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION),
				major, minor
			);
			Debug::Msg("----------------------------------------------------\n\n");

			Debug::Msg("Extensions:\n");

			GLint n, i;
			glGetIntegerv(GL_NUM_EXTENSIONS, &n);
			for (i = 0; i < n; i++)
			{
				Debug::Msg("\t%s\n", glGetStringi(GL_EXTENSIONS, i));
			}

			OPENGL_INT_PRINT_DEBUG(GL_MAX_VERTEX_ATTRIBS);
			OPENGL_INT_PRINT_DEBUG(GL_MAX_TEXTURE_IMAGE_UNITS);
#endif

			return true;
		}
	} // namespace EugenixGL
} // namespace Eugenix

#endif // EUGENIX_OPENGL