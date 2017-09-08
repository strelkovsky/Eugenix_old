//-----------------------------------------------------------------------------
// Eugenix Framework
// Copyright (C) strelkovsky.com, Inc.
//-----------------------------------------------------------------------------

#pragma once

#include "Core/Base.h"
#include "Debug.h"

namespace Eugenix
{
	namespace Debug
	{
		void Impl(const char *formatMessage, va_list args)
		{
			vprintf(formatMessage, args);
		}

		void Msg(const char *formatMessage, ...)
		{
			va_list args;
			va_start(args, formatMessage);
			Impl(formatMessage, args);
			va_end(args);
		}

		void Error(const char *formatMessage, ...)
		{
			va_list args;
			va_start(args, formatMessage);
			Impl(formatMessage, args);
			va_end(args);
		}

		void Fatal(const char *formatMessage, ...)
		{
			va_list args;
			va_start(args, formatMessage);
			Impl(formatMessage, args);
			va_end(args);
		}
	} // namespace Debug
} // namespace Eugenix
