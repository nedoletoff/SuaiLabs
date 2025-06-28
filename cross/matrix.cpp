#include "matrix.hpp"

Matrix::Matrix(size_t h, size_t w)
{
	height = h;
	width = w;
	data = new char*[h];
	status = new int*[h];
	for (size_t i = 0; i < h; i++)
	{
		data[i] = new char[w]; 
		status[i] = new int[w];
	}
	for (size_t i = 0; i < height; i++)
		for (size_t j = 0; j < width; j++)
		{
			status[i][j] = not_used;
			data[i][j] = '\0';
		}
}

Matrix::~Matrix()
{
	for (size_t i = 0; i < height; i++)
	{
		delete[] data[i];
		delete[] status[i];
	}
	delete[] data;
	delete[] status;
}

Matrix::Matrix(Matrix& a)
{
	height = a.height;
	width = a.width;
	data = new char*[height];
	status = new int*[height];
	for (size_t i = 0; i < height; i++)
	{
		data[i] = new char[width];
		status[i] = new int[width];
	}

	for (size_t i = 0; i < height; i++)
		for (size_t j = 0; j < width; j++)
		{
			status[i][j] = a.status[i][j];
			data[i][j] = a.data[i][j];
		}
}

Matrix& Matrix::operator=(Matrix& a)
{
	if (&a == this)
		return *this;

	for (size_t i = 0; i < height; i++)
	{
		delete[] data[i];
		delete[] status[i];
	}
	delete[] data;
	delete[] status;

	height = a.height;
	width = a.width;
	data = new char*[height];
	status = new int*[height];
	for (size_t i = 0; i < height; i++)
	{
		data[i] = new char[width];
		status[i] = new int[width];
	}
	for (size_t i = 0; i < height; i++)
		for (size_t j = 0; j < width; j++)
		{
			status[i][j] = a.status[i][j];
			data[i][j] = a.data[i][j];
		}
	return *this;
}

void Matrix::set_cell(size_t h, size_t w, char value)
{
	if (h >= height)
        throw Exception("h out of range");
	if (w >= width)
		throw Exception("w out of range");
	data[h][w] = value;
}

void Matrix::set_cell_status(size_t h, size_t w, int value)
{
	if (h >= height)
        throw Exception("h out of range");
	if (w >= width)
		throw Exception("w out of range");
	status[h][w] = value;
}

void Matrix::multiply_cell_status(size_t h, size_t w, int value)
{
	if (h >= height)
        throw Exception("h out of range");
	if (w >= width)
		throw Exception("w out of range");
	status[h][w] *= value;
//	std::cout << status[h][w] << std::endl;
}

void Matrix::divide_cell_status(size_t h, size_t w, int value)
{
	if (h >= height)
        throw Exception("h out of range");
	if (w >= width)
		throw Exception("w out of range");
	status[h][w] /= value;
//	std::cout << status[h][w] << std::endl;
}
	
char Matrix::get_cell(size_t h, size_t w)
{
	if (h >= height)
        throw Exception("h out of range");
	if (w >= width)
		throw Exception("w out of range");
	return data[h][w];
}

int Matrix::get_cell_status(size_t h, size_t w)
{
	if (h >= height)
        throw Exception("h out of range");
	if (w >= width)
		throw Exception("w out of range");
	return status[h][w];
}
size_t Matrix::get_height()
{
	return height;
}

size_t Matrix::get_width()
{
	return width;
}

size_t Matrix::get_unfilled(char check)
{
	size_t count = 0;
	for (size_t i = 0; i < height; i++)
		for (size_t j = 0; j < width; j++)
			if (data[i][j] == check)
				count++;
	return count;
}

size_t Matrix::get_unfilled()
{
	size_t count = 0;
	for (size_t i = 0; i < height; i++)
		for (size_t j = 0; j < width; j++)
			if (status[i][j] != used)
				count++;
	return count;
}

void Matrix::change_unfilled(char check, char value)
{
	for (size_t i = 0; i < height; i++)
		for (size_t j = 0; j < width; j++)
			if (data[i][j] == check)
				data[i][j] = value;
}

void Matrix::increase_size(size_t h, size_t w)
{
	if (h <= height)
		throw Exception("h <= height");
	if (w <= width)
		throw Exception("w <= width");

	Matrix temp(*this);
	for (size_t i = 0; i < height; i++)
	{
		delete[] status[i];
		delete[] data[i];
	}
	delete[] status;
	delete[] data;

	data = new char*[h];
	status = new int*[h];
	for (size_t i = 0; i < h; i++)
	{
		status[i] = new int[w];
		data[i] = new char[w];
	}

	for (size_t i = 0; i < h; i++)
		for (size_t j = 0; j < w; j++)
		{
			status[i][j] = not_used;
			data[i][j] = '\0';
		}

	for (size_t i = 0; i < height; i++)
		for (size_t j = 0; j < width; j++)
		{

			status[i][j] = temp.status[i][j];
			data[i][j] = temp.data[i][j];
		}
	height = h; width = w;

}

void Matrix::shrink_to_fit(char check)
{
	size_t h = height;
	size_t w = width;
	bool temp;

	for (size_t i =	0; i <	height; i++)
	{
		temp  = true;
		for (size_t j = 0; j < width; j++)
			if (data[i][j] != check)
			{
				temp = false;
				break;
			}
		if (temp)
		{
			h = i;
			break;
		}
	}
	for (size_t i =	0; i <	width; i++)
	{
		temp = true;
		for (size_t j = 0; j < height; j++)
			if (data[j][i] != check)
			{
				temp = false;
				break;
			}
		if (temp)
		{
			w = i;
			break;
		}
	}

	Matrix a(*this);
		for (size_t i = 0; i < height; i++)
		{
			delete[] data[i];
			delete[] status[i];
		}
	delete[] data;
	delete[] status;

	height = h; width = w;
	data = new char*[height];
	status = new int*[height];
	for (size_t i = 0; i < height; i++)
	{
		status[i] = new int[width];
		data[i] = new char[width];
	}
	for (size_t i = 0; i < height; i++)
		for (size_t j = 0; j < width; j++)
		{
			status[i][j] = a.status[i][j];
			data[i][j] = a.data[i][j];
		}
}

double Matrix::get_coef()
{
	double count = 0.0;
	for (size_t  i = 0; i < height; i++)
		for (size_t j = 0; j < width; j++)
			if (status[i][j] % (used * used) == 0)
				count++;
	if (get_unfilled() == height * width)
		return -1;
	return count / (height * width);
}

bool Matrix::legal(size_t h, size_t w)
{
	if ( h < height && w < width)
		return true;
	return false;
}
