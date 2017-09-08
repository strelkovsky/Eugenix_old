//-----------------------------------------------------------------------------
// Eugenix Framework
// Copyright (C) strelkovsky.com, Inc.
//-----------------------------------------------------------------------------

#pragma once

namespace Eugenix
{
	namespace Debug
	{
		void Msg(const char *formatMessage, ...);
		void Error(const char *formatMessage, ...);
		void Fatal(const char *formatMessage, ...);
	} // namespace Debug
} // namespace Eugenix
