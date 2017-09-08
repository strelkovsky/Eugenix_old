//-----------------------------------------------------------------------------
// Eugenix Framework
// Copyright (C) strelkovsky.com, Inc.
//-----------------------------------------------------------------------------

#pragma once

namespace Eugenix
{
	namespace Memory
	{
		void Clear(void* dst, size_t size);

		/*
		struct IAllocator
		{
		virtual void* Malloc(unsigned long Count, const char* Tag) = 0;
		virtual void* Realloc(void* Original, unsigned long Count, const char* Tag) = 0;
		virtual void Free(void* Original) = 0;
		virtual void DumpAllocs() = 0;
		virtual void HeapCheck() = 0;
		};

		*/
	} // namespace Memory
} // namespace Eugenix
