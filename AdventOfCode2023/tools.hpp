#pragma once

#include <vector>
namespace tools
{
	template <class T>
	struct mat
	{
	private:
		std::vector<T> matrix;
		size_t column_size;
	public:
		
		mat(size_t column_size);

		T at(size_t i, size_t j);
		void set(size_t i, size_t j, T val);
		void push_back(T val);

	};
}