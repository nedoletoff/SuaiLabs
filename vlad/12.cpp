#include "12.hpp"
#include <iostream>
#include <cstring>

String::String()
{
	size = 0;
	string = NULL;
}

String::~String()
{
	delete[] string;
}

String::String(String& a)
{
	size = a.size;
	string = new char[size];
	for (int i = 0; i < size; ++i)
		string[i] = a.string[i];
}

String::String(char* str, int s)
{
	size = s;
	string = new char[size];
	for (int i = 0; i < size; ++i)
		string[i] = str[i];
}

String& String::operator=(const String& a)
{
	if (&a == this)
		return *this;

	size = a.size;
	string = new char[size];
	for (int i = 0; i < size; ++i)
		string[i] = a.string[i];
	return *this;
}

int String::len()
{
	return size;
}

int String::add_string(char* str, int str_size)
{
//	std::cout << "add string started\n";
	char* temp = new char[size];
	int s = size;
	for (int i = 0; i < s; ++i)
		temp[i] = string[i];

	if (str_size <= 0)
		size += strlen(str) + 1;
	else
		size += str_size;
	delete [] string;
	string = new char[size];

	for (int i = 0; i < s; ++i)
		string[i] = temp[i];
	for (int i = s; i < size; ++i)
		string[i] = str[i - s];
	delete [] temp;
//	std::cout << "add string done\n";
	return 0;

}

int String::remove(int f, int l)
{
	if  (!((l > f) && l < size))
		return -1;

	char* temp = new char[size];
	int k = 0;
	for (int i = 0; i < size; ++i)
		if (i >= f && i < l)
			continue;
		else
			temp[k++] = string[i];
	delete [] string;
	size = k;
	
	string = new char[size];

	for (int i = 0; i < size; ++i)
		string[i] = temp[i];
	delete [] temp;
	return 0;

}

const String String::operator-(const String& other)
{
	char* temp;
	int s = 0;
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < other.size; ++j)
			if (string[i] == other.string[j] && string[i] != '\0')
			{
				++s;
				break;
			}
//	std::cout << s << "n to remove\n" << size << "size of string\n";
	s = size - s;
	temp = new char[s];
	
	int check = 1, count = 0;
	for (int i = 0; i < size; ++i)
	{
		check = 1;
		for (int j = 0; j < other.size; ++j)
			if (string[i] == other.string[j] && string[i] != '\0')
			{
				check = 0;
				break;
			}
		if (check)
			temp[count++] = string[i];
	}
//	std::cout << count <<  " - count\n";

	String r(temp, count);

	return r;
}       

int String::remove(int n)
{
//	std::cout << size << "size before remove one symbol\n";
	if (n < 0 || n > size)
		return 1;
	char* temp = new char[size - 1];
	int k = 0;
	for (int i = 0; i < size; ++i)
		if (i != n)
			temp[k++] = string[i];
	delete [] string;
	string = new char[--size];
	for (int i = 0; i < size; ++i)
		string[i] = temp[i];
	delete [] temp;
//	std::cout << size << "size after remove one symbol\n";
	return 0;
}


void String::insert(char st)
{
	char* temp = new char [++size];
	for (int i = 0; i < size - 1; ++i)
		temp[i] = string[i];
	temp[size-2] = st;
	temp[size-1] = '\0';
	delete [] string;
	string = new char[size];
	for (int i = 0; i < size; ++i)
		string[i] = temp[i];
	delete [] temp;
}

void String::conc(String& p)
{
	if (size)
	{
//		std::cout << "\n\n\nremove worked\n\n\n";
		remove(size);
	}
	add_string(p.string, p.size);
}

void String::print()
{
//	char b[]  = " - ";
//	for (int i = 0; i < size; ++i)
//		std::cout << i << b << string[i] << b << int(string[i]) << std::endl; 

//	std::cout << size << " - Size of string\n";
	for (int i = 0; i < size; ++i)
	       std::cout << string[i];
	std::cout << '\n';	
}
