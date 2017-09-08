#pragma once

template<typename T>
size_t GetVectorSize(const typename std::vector<T> &vec)
{
	return sizeof(T) * vec.size();
}