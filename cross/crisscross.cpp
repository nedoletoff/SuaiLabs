#include "crisscross.hpp"
#include <iostream>

bool check_word_g(Words& words, size_t n, Matrix& matrix, size_t h, size_t w)
{
	std::string value = words.get_word(n);
	size_t word_size = value.size();

	if (!(w + word_size < matrix.get_width()))
		return false;

	if (matrix.legal(h, w - 1) &&
	matrix.get_cell_status(h, w - 1) % used == 0)
		return false;

	if (matrix.legal(h, w + word_size) &&
	matrix.get_cell_status(h, w + word_size) % ::used == 0)
		return false;

	for (size_t i = 0; i < word_size; i++)
		if (matrix.get_cell_status(h, w + i) %
		::gorizontal == 0 || (matrix.get_cell_status(h, w + i) %
		::used == 0 && matrix.get_cell(h, w + i) != value[i]))
			return false;
	return true;
}

bool add_word_g(Words& words, size_t n, Matrix& matrix, size_t h, size_t w)
{
	if (check_word_g(words, n, matrix, h, w))
	{
		std::string value = words.get_word(n);
		size_t word_size = words.get_word(n).size();

		for (size_t i = 0; i < word_size; i++)
		{
			matrix.set_cell(h, w + i, value[i]);
			matrix.multiply_cell_status(h, w + i, ::used);
			if (matrix.legal(h - 1, w + i))
				matrix.multiply_cell_status(h - 1, w + i, ::gorizontal);
			if (matrix.legal(h + 1, w + i))
				matrix.multiply_cell_status(h + 1, w + i, ::gorizontal);
		}
		if (matrix.legal(h, w + word_size))
			matrix.multiply_cell_status(h, w + word_size, ::used);
		if (matrix.legal(h, w - 1))
				matrix.multiply_cell_status(h, w - 1, ::used);
		words.change_word_status(n, true);
		words.set_coordinates(n, -1, h, w);
		return true;
	}
	return false;
}

bool check_word_v(Words& words, size_t n, Matrix& matrix, size_t h, size_t w)
{
	std::string value = words.get_word(n);
	size_t word_size = value.size();

	if (!(h + word_size < matrix.get_height()))
		return false;

	if (matrix.legal(h - 1, w) &&
	matrix.get_cell_status(h - 1, w) % used == 0)
		return false;

	if (matrix.legal(h + word_size + 1, w) &&
	matrix.get_cell_status(h + word_size, w) % used == 0)
		return false;

	for (size_t i = 0; i < word_size; i++)
		if (matrix.get_cell_status(h + i, w) % ::vertical == 0 ||
		(matrix.get_cell_status(h + i, w) % ::used == 0 &&
		matrix.get_cell(h + i, w) != value[i]))
			return false;
	return true;
}

bool add_word_v(Words& words, size_t n, Matrix& matrix, size_t h, size_t w)
{
	if (check_word_v(words, n, matrix, h, w))
	{
		std::string value = words.get_word(n);
		size_t word_size = words.get_word(n).size();

		for (size_t i = 0; i < word_size; i++)
		{
			matrix.set_cell(h + i, w, value[i]);
			matrix.multiply_cell_status(h + i, w, ::used);
			if (matrix.legal(h + i, w - 1))
				matrix.multiply_cell_status(h + i, w - 1, ::vertical);
			if (matrix.legal(h + i, w + 1))
				matrix.multiply_cell_status(h + i, w + 1, ::vertical);
		}
		if (matrix.legal(h + word_size, w))
			matrix.multiply_cell_status(h + word_size, w, ::used);
		if (matrix.legal(h - 1, w))
				matrix.multiply_cell_status(h - 1, w, ::used);
		words.change_word_status(n, true);
		words.set_coordinates(n, 1, h, w);
		return true;
	}
	return false;
}

bool add_word(Words& words, size_t n, Matrix& matrix, size_t h, size_t w)
{
	if (add_word_g(words, n, matrix, h, w))
			return true;
	return add_word_v(words, n, matrix, h, w);
}

void delete_word_g(std::string value, Matrix& matrix, size_t h, size_t w)
{
	size_t word_size = value.size();
	if (w + word_size > matrix.get_width())
		throw Exception("w + word_size");

	for (size_t i = 0; i < word_size; i++)
		if (matrix.get_cell(h, w + i) && matrix.get_cell(h, w + i) != value[i])
			throw Exception("words is not in place" );
	for (size_t i = 0; i < word_size; i++)
	{
		if (matrix.get_cell_status(h, w + i) / (::used*::used) == 0)
			matrix.set_cell(h, w + i, '\0');
		matrix.divide_cell_status(h, w + i, ::used);

		if (matrix.legal(h - 1, w + i))
			matrix.divide_cell_status(h - 1, w + i, ::gorizontal);

		if (matrix.legal(h + 1, w + i))
			matrix.divide_cell_status(h + 1, w + i, ::gorizontal);
	}
	if (matrix.legal(h, w + word_size))
		matrix.divide_cell_status(h, w + word_size, ::used);
	if (matrix.legal(h, w - 1))
			matrix.divide_cell_status(h, w - 1, ::used);
}


void delete_word_v(std::string value, Matrix& matrix, size_t h, size_t w)
{
	size_t word_size = value.size();

	if (h + word_size > matrix.get_height())
		throw Exception("h + word_size");

	for (size_t i = 0; i < word_size; i++)
		if (matrix.get_cell(h + i, w) && matrix.get_cell(h + i, w)!= value[i])
			throw Exception("words is not in place");

	for (size_t i = 0; i < word_size; i++)
	{
		if (matrix.get_cell_status(h + i, w) / (::used*::used) == 0)
			matrix.set_cell(h + i, w, '\0');
		matrix.divide_cell_status(h + i, w, ::used);

		if (matrix.legal(h + i, w + 1))
			matrix.divide_cell_status(h + i, w + 1, ::vertical);

		if (matrix.legal(h + i, w - 1))
			matrix.divide_cell_status(h + i, w - 1, ::vertical);
	}
	if (matrix.legal(h + word_size, w))
		matrix.divide_cell_status(h + word_size, w, ::used);
	if (matrix.legal(h - 1, w))
			matrix.divide_cell_status(h - 1, w, ::used);

}

bool delete_word(Words& words, size_t n, Matrix& matrix)
{
	if (!words.get_word_status(n))
		return false;

	std::string value = words.get_word(n);
	Coordinates c = words.get_coordinates(n);
	if (c.orientation > 0)
		delete_word_v(value, matrix, c.h, c.w);
	if (c.orientation < 0)
		delete_word_g(value, matrix, c.h, c.w);

	words.change_word_status(n, false);
	words.set_coordinates(n, 0);
	return true;
}

bool check_word(Words& words, size_t n, Matrix& matrix, size_t h, size_t w, double& m_coef)
{
	size_t count = 0;

	if (check_word_g(words, n, matrix, h, w))
	{
		for(size_t i = 0; i < words.get_word(n).size(); i++)
			if (matrix.get_cell_status(h, w + i) == ::used)
				count++;
	}
	else if (check_word_v(words, n, matrix, h, w))
	{
		for(size_t i = 0; i < words.get_word(n).size(); i++)
			if (matrix.get_cell_status(h + i, w) == ::used)
				count++;
	}

	if (count)
		m_coef += double(count) / (::used * ::used);
	
	if (m_coef > matrix.get_coef())
		return true;
	return false;

}

bool add_word(Words& words, size_t n, Matrix& matrix)
{
	double m_coef = matrix.get_coef();
	bool check = false;
	size_t h, w;

	if (m_coef < 0)
		m_coef = 0;

	if (words.get_word_status(n))
		return false;

	for (size_t i = 0; i < matrix.get_height(); i++)
		for (size_t j = 0; j < matrix.get_width(); j++)
			if (check_word(words, n, matrix, i, j, m_coef))
			{
				check = true;
				h = i; w = j;
				m_coef = matrix.get_coef();
			}
	if (check)
		return (add_word(words, n, matrix, h, w));
	return false;
}


void cross(Words& words, Matrix& matrix, Matrix& res, std::list<size_t>& saved, std::list<size_t>& l)
{
	for (size_t k = 0; k < words.get_words_numbers(); k++)
		if (add_word(words, k, matrix))
		{
			l.push_back(k);

			cross(words, matrix, res, saved, l);
		}

	if (matrix.get_coef() > res.get_coef())
	{
		saved = l;
		res = matrix;
	}
	delete_word(words, l.back(), matrix);
	if (l.size())
		l.pop_back();
}


void crisscross(Words& words, Matrix& matrix)
{
	Matrix res(matrix);
	std::list<size_t> l, saved;
	cross(words, matrix, res, saved, l);
	if (res.get_coef() == 0)
	{
		add_word_g(words, 0, matrix, 5, 0);
		cross(words, matrix, res, saved, l);
	}
	matrix = res;
	matrix.shrink_to_fit('\0');
	matrix.change_unfilled('\0', ' ');
	for (auto& e : saved)
		words.change_word_status(e, true);
	std::cout << "List of not used words: ";
	for (size_t i = 0; i < words.get_words_numbers(); i++)
		if (!words.get_word_status(i))
			std::cout << words.get_word(i) << " ";
	std::cout << std::endl;
}
