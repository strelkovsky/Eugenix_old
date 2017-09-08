//-----------------------------------------------------------------------------
// Eugenix Framework
// Copyright (C) strelkovsky.com, Inc.
//-----------------------------------------------------------------------------

#include "Platform/Platform.h"

#ifdef EUGENIX_GLFW_RUNTIME

#include "Platform/OpenGL/EugenixGL.h"
#include <glfw/glfw3.h>

#include "Core/Debug/Debug.h"
#include "Platform/Runtime.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	////if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	////	glfwSetWindowShouldClose(window, GL_TRUE);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
}

namespace Eugenix
{
	namespace Runtime
	{
		DisplaySetup _setup;

		GLFWwindow* _window = nullptr;

		bool Init(const DisplaySetup& setup)
		{
			_setup = setup;

			if (glfwInit() != GLFW_TRUE)
			{
				Debug::Fatal("glfwInit error");
				return false;
			}

#ifdef EUGENIX_OPENGL
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif // EUGENIX_OPENGL
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

#ifdef EUGENIX_DEBUG
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif // EUGENIX_DEBUG

			_window = glfwCreateWindow(_setup.width, _setup.height, "Eugenix", nullptr, nullptr);
			if (!_window)
			{
				Debug::Fatal("Window could not be created!");
				return false;
			}

			glfwMakeContextCurrent(_window);

			glfwSetKeyCallback(_window, key_callback);
			glfwSetMouseButtonCallback(_window, mouse_button_callback);

#ifdef EUGENIX_OPENGL
			if (!EugenixGL::Init())
			{
				Debug::Fatal("EugenixGL init failed!");
				return false;
			}
#endif // EUGENIX_OPENGL

			return true;
		}

		void Term()
		{
			glfwTerminate();
		}

		bool RunFrame()
		{
			glfwPollEvents();

			return !glfwWindowShouldClose(_window);
		}

		void CommitFrame()
		{
			glfwSwapBuffers(_window);
		}

		const DisplaySetup& Setup()
		{
			return _setup;
		}
	} // namespace Runtime
} // namespace Eugenix

#endif // EUGENIX_SDL_RUNTIME