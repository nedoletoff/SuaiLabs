#include "pr.hpp"

int main()
{
	char ad[] = {0, 0, 1, 0, 1};
	size_t s = sizeof(ad);
	BinVect b1(s, ad);
	std::cout << "print b1\n";
	b1.print();
	BinVect b2;
	std::cout << "print b2\n";
	b2.print();
	b2 = b1;
	std::cout << "print b2\n";
	b2.print();
	std::cout << b2 == b1 << std::endl;
}

