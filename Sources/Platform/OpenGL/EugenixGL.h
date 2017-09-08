//-----------------------------------------------------------------------------
// Eugenix Framework
// Copyright (C) strelkovsky.com, Inc.
//-----------------------------------------------------------------------------

#pragma once

#include "Platform/Platform.h"

#ifdef EUGENIX_OPENGL_GLEW
#define GLEW_STATIC
#include <GL/glew.h>
#endif

#include <gl/glext.h>
#include <gl/wglext.h>

#ifdef EUGENIX_OPENGL

namespace Eugenix
{
	namespace EugenixGL
	{
		bool Init();
	} // namespace EugenixGL
} // namespace Eugenix

#endif // EUGENIX_OPENGL

