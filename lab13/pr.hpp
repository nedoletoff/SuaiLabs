#pragma once 
#include <iostream>

class BinVect
{
	private:
		char* data;
		size_t size;
	public:
		BinVect();
		BinVect(size_t, char*);
		BinVect(BinVect&);
		~BinVect();
		BinVect& operator=(BinVect&);
		int set(size_t, char*);
		int get(char**);
		int get_number();
		void print();
		BinVect& operator+=(const BinVect&);
		BinVect& operator-=(const BinVect&);
		BinVect operator+(const BinVect&);
		BinVect operator-(const BinVect&);

		bool operator==(const BinVect&);
		bool operator!=(const BinVect&);
		bool operator>(const BinVect&);
		bool operator>=(const BinVect&);
		bool operator<(const BinVect&);
		bool operator<=(const BinVect&);
		BinVect operator>>(int);
		BinVect operator<<(int);
}



