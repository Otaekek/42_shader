#pragma once

typedef uint32_t int

template <typename T, uint32_t S> class JConstantArray {
	uint32_t	size;
	T			elem[S];

	JConstantArray<T, S>& operator[](uint32_t i)
	{
		return (elem[S]);
	}

};