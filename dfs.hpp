#pragma once
#include <string>
#include <fstream>
//#include <vector>
#include <iostream>

class Dfs
{
	private:
		size_t size;
		size_t start_pos;
		bool** matrix;
	public:
		Dfs(std::string);
		~Dfs();
		size_t get_ancestors(size_t p, bool** mas);	
		size_t get_descendants(size_t p, bool** mas);
		size_t get_size();
		size_t get_start_pos();
	friend std::ostream& operator<<(std::ostream& os, const Dfs& value)
	{
		os << "start - " << value.start_pos << std::endl;
		os << "size - " << value.size << std::endl;
		os << "  ";
		for (size_t i = 1; i <= value.size; ++i)
			os << i << " ";
		for (size_t i = 1; i <= value.size; ++i)
		{
			os << std::endl;
			os << i << " ";
			for (size_t j = 0; j < value.size; ++j)
				os << value.matrix[i-1][j] << " ";
		}
		return os;
	}
};


