
#include <vector>
namespace tools
{
	template <typename T>
	struct mat
	{
	private:
		std::vector<T> matrix;

	public:
		size_t column_size;
		mat(size_t column_size) : column_size(column_size)
		{
			
		}

		T at(size_t i, size_t j)
		{
			return matrix[i * column_size + j];
		}
		void set(size_t i, size_t j, T val)
		{
			matrix[i * column_size + j] = val;
		}
		void push_back(T val)
		{
			matrix.push_back(val);
		}
		size_t len()
		{
			size_t roundedUp = matrix.size();
			while (roundedUp % column_size != 0)
				roundedUp++;

			return roundedUp / column_size;
		}

	};
}

