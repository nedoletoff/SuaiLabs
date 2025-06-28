#include "dfs.hpp"

Dfs::Dfs(std::string file_name)
{
	std::string tresh;
	char t;
	std::ifstream file(file_name);
	if (!file)
		throw -1;	//file doesnt exist

	file >> tresh >> tresh;
	file >> start_pos;
	file >> tresh >> tresh;
	file >> size;
		
	file >> tresh;
	while (stoi(tresh) != size)
		file >> tresh >> tresh;

	matrix = new bool*[size];
	for (size_t i  = 0; i < size; ++i)
		matrix[i] = new bool[size];

	for (size_t i = 0; i < size; ++i)
	{
		file >> tresh;
		for (size_t j = 0; j < size; ++j)
		{
			file >> matrix[i][j];
		}
	}
}

Dfs::~Dfs()
{
	for (size_t i = 0; i < size; ++i)
		delete[] matrix[i];
	delete[] matrix;
}

size_t Dfs::get_ancestors(size_t p, bool** mas)
{
	size_t count = 0;
	*mas = new bool[size];
	for (size_t i = 0; i < size; ++i)
		{
			mas[0][i] = matrix[i][p-1];
			if (matrix[i][p-1])
			{
				++count;
			}
		}
				
	return count;
}

size_t Dfs::get_descendants(size_t p, bool** mas)
{
	size_t count = 0;
	*mas = new bool[size];
	for (size_t i = 0; i < size; ++i)
		{
			mas[0][i] = matrix[p-1][i];
			if (matrix[p-1][i])
			{
				++count;
			}
		}
				
	return count;
}

size_t Dfs::get_size()
{
	return size;
}

size_t Dfs::get_start_pos()
{
	return start_pos;
}


