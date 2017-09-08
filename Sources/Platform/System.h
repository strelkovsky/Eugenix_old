//-----------------------------------------------------------------------------
// Eugenix Framework
// Copyright (C) strelkovsky.com, Inc.
//-----------------------------------------------------------------------------

#pragma once

#include "Core/Base.h"

namespace Eugenix
{
	namespace System
	{
		void Error(const char* format, ...);
		void Exit(int32_t exitCode);
		void Message(const char* format, ...);
		void Sleep(const uint32_t msec);
	} // System
} // Eugenix
