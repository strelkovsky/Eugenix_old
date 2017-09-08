//-----------------------------------------------------------------------------
// Eugenix Framework
// Copyright (C) strelkovsky.com, Inc.
//-----------------------------------------------------------------------------

#include "Platform/Platform.h"

#ifdef EUGENIX_SDL_RUNTIME

#include <SDL.h>

#include "Platform/OpenGL/EugenixGL.h"

#include "Core/Base.h"
#include "Core/Debug/Debug.h"
#include "Platform/Runtime.h"

namespace Eugenix
{
	namespace Runtime
	{
		DisplaySetup _setup;

		SDL_Window* _window = nullptr;
#ifdef EUGENIX_OPENGL
		SDL_GLContext _context = nullptr;
#endif // EUGENIX_DEBUG

		bool Init(const DisplaySetup& setup)
		{
			_setup = setup;

			if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
			{
				Debug::Fatal("SDL_Init error - %s\n", SDL_GetError());
				return false;
			}

#ifdef EUGENIX_OPENGL
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	#ifdef EUGENIX_DEBUG
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	#endif // EUGENIX_DEBUG
#endif // EUGENIX_OPENGL

			uint32_t flags = SDL_WINDOW_SHOWN;
#ifdef EUGENIX_OPENGL
			flags |= SDL_WINDOW_OPENGL;
#endif // EUGENIX_OPENGL

			_window = SDL_CreateWindow("EugenixFramework", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _setup.width, _setup.height, flags);
			if (!_window)
			{
				Debug::Fatal("Window could not be created! - %s", SDL_GetError());
				return false;
			}

#ifdef EUGENIX_OPENGL
			_context = SDL_GL_CreateContext(_window);
			if (!_context)
			{
				Debug::Error("OpenGL context could not be created! - %s", SDL_GetError());
				return false;
			}

			if (SDL_GL_SetSwapInterval(1) < 0)
			{
				Debug::Error("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
			}

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
#ifdef EUGENIX_OPENGL
			if (_context)
				SDL_GL_DeleteContext(_context);
#endif // EUGENIX_OPENGL

			if (_window)
				SDL_DestroyWindow(_window);
			SDL_Quit();
		}

		bool RunFrame()
		{
			bool quit = false;

			SDL_Event e = { 0 };
			while (SDL_PollEvent(&e) != 0)
			{
				switch (e.type)
				{
				case SDL_QUIT:
					quit = true;
					break;
				
				case SDL_MOUSEBUTTONUP:
					break;
				case SDL_MOUSEBUTTONDOWN:
					break;
				case SDL_MOUSEMOTION:
					break;
				case SDL_MOUSEWHEEL:
					break;
				
				case SDL_KEYDOWN:
					break;
				case SDL_KEYUP:
					break;
				}

				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
			}

			return !quit;
		}

		void CommitFrame()
		{
#ifdef EUGENIX_DEBUG
			SDL_GL_SwapWindow(_window);
#endif // EUGENIX_OPENGL
		}

		void Resize(uint32_t width, uint32_t height)
		{
			SDL_SetWindowSize(_window, width, height);
		}
	} // namespace Runtime
} // namespace Eugenix

#endif // EUGENIX_SDL_RUNTIME