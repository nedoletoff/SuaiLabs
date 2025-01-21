#include "myset.hpp"
#include <iostream>
/* raznost, smeznost, union */
int main()
{
	mySet a;
	mySet aa;
	mySet b;
	a.insert(1);
	a.insert(2);
	a.insert(21);
	a.insert(4);

	aa.insert(13);
	aa.insert(1);
	b = aa.intersect(a);

	for (auto bi : b) {
		std::cout << bi << " ";
	}
	std::cout << std::endl;
	mySet bb;
	bb = a.combine(aa);
	for (auto bi : bb) {
		std::cout << bi << " ";
	}
	std::cout << std::endl;
	mySet bbb;
	bbb = a.minus(aa);
	for (auto bi : bbb) {
		std::cout << bi << " ";
	}
	std::cout << std::endl;
	return 0;
}
