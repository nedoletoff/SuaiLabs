#include "pr.hpp"

BinVect::BinVect()
{
	data = NULL;
	size = 0;
}

BinVect::BinVect(size_t s, char* d)
{
	size = s;
	data = new char [size];
	for (size_t i = 0; i < size; ++i)
		data[i] = d[i] % 2;
}

BinVect::~BinVect()
{
	delete [] data;
}

BinVect BinVect::(BinVect& a)
{
	size = a.size;
	data = new char [size];
	for (size_t i = 0; i < size; ++i)
		data[i] = a.data[i];
}

BinVect& BinVect::operator=(Stack& a);
{
	if (&a == this)
		return *this;
	delete [] data;
	size = a.size;
	data = new char [size];
	for (size_t i = 0; i < size; ++i)
		data[i] = a.data[i];
	return *this;
}

int BinVect::set(size_t s, char* d)
{
	delete [] data;
	size = s;
	data = new char [size];
	for (size_t i = 0; i < size; ++i)
		data[i] = d[i] % 2;
	return 0;
}

int BinVect::get(char** rv)
{
	*rv = new char [size];
	for (size_t i = 0; i < size; ++i)
		*rv[i] = data[i];
	return 0;
}

void BinVect::print()
{
	 for (size_t i = 0; i < size; ++i)
		 if (data[i] % 2)
			 std::cout << "1 ";
		 else
			 std::cout << "0 ";
	 std::cout << "\n";
}

int BinVect::get_number()
{
	int r = 0;
	for (size_t i = 0; i < size; ++i)
	{
		r *= 2;
		r += data[i];
	}
	return r;
}		

BinVect BinVect::operator+(const BinVect& other)
{
	char* d;
	size_t s = other.size;
	if (size > other.size)
		s = size;
	d = new char [s];

	for (size_t i = 0; i < s; ++i)
		d[i] = 0;

	for (size_t i = 0; i < size; ++i)
		d[i] = data[i];

	for (size_t i = 0; i < other.size; ++i)
		d[i] = (d[i] + other.data[i]) % 2;
	BinVect temp(s, d);
	return temp;
}

BinVect BinVect::operator-(const BinVect& other)
{
	char* d;
	size_t s = other.size;
	if (size > other.size)
		s = size;
	d = new char [s];

	for (size_t i = 0; i < s; ++i)
		d[i] = 0;

	for (size_t i = 0; i < size; ++i)
		d[i] = data[i];

	for (size_t i = 0; i < other.size; ++i)
		d[i] = (d[i] + other.data[i]) % 2;
	BinVect temp(s, d);
	return temp;
}

BinVect BinVect::operator-=(const BinVect& other)
{
	return *this-other;
}

BinVect BinVect::operator+=(const BinVect& other)
{
	return *this+other;
}

bool BinVect::operator==(const BinVect& other)
{
	return (this->get_number() == other.get_number());
}

bool BinVect::operator<const BinVect& other)
{
	return (this->get_number() < other.get_number());
}

bool BinVect::operator>(const BinVect& other)
{
	return (this->get_number() > other.get_number());
}

bool BinVect::operator<=(const BinVect& other)
{
	return (this->get_number() <= other.get_number());
}

bool BinVect::operator>=(const BinVect& other)
{
	return (this->get_number() >= other.get_number());
}

bool BinVect::operator!=(const BinVect& other)
{
	return (this->get_number() != other.get_number());
}

BinVect BinVect::operator>>(int gap)
{
	BinVect temp(*this);
	size_t g = (size_t) gap;
	for (size_t i = size-1; i >= g; --i)
		temp.data[i] = temp.data[i-g];
	for (size_t i = 0; i < g; ++i)
		temp.data[i] = 0;
	return temp;
}

BinVect BinVect::operator<<(int gap)
{
	BinVect temp(*this);
	size_t g = (size_t) gap;
	for (size_t i = 0; i < size - gap; ++i)
		temp.data[i] = temp.data[i+gap];
	for (size_t i = size - gap; i < size; ++i)
		temp.data[i] = 0;
	return temp;
}
