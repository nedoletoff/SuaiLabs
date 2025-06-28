#include <iostream>
#include "matrix.hpp"

size_t h(10);
size_t w(5);

int main()
{
	Matrix m(h, w);
	for (size_t i = 0; i < h; i++)
		for (size_t j = 0; j < w-1; j++)
			m.set_cell(i, j, 'a'+i);
	std::cout << m;
	std::cout << m.get_height() << " - " << m.get_width() << std::endl;
	m.shrink_to_fit('\0');
	std::cout << m.get_height() << " - " << m.get_width() << std::endl;
	m.increase_size(15, 7);
	m.set_cell(13, 6, 't');
	m.change_unfilled('\0', ' ');
	std::cout << m;
	std::cout << m.get_height() << " - " << m.get_width() << std::endl;
	for (size_t i = 0; i < m.get_width(); i++)
		std::cout << m.get_cell(0, i) << std::endl;
	std::cout << m.get_unfilled(' ') << std::endl;
	return 0;
}
