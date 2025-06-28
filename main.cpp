#include "pr.hpp"
#include <iostream>


int main()
{
	Stack a;
	int v = 0, r, s;

	a.push(22);
	v = a.get_size();
	a.get(v, &r);
	std::cout << r << " - Stack a\n";

	a.push(34);
	v = a.get_size();
	a.get(1, &r);
	std::cout << r << " - Stack a\n";

	std::cout << "Stack a:\n";
	a.print();

	Stack b(a);
	std::cout << a.get_size() << std::endl;
	std::cout << b.get_size() << std::endl;
	b.push( 99);
	std::cout << "Stack b:\n";
	b.print();

	std::cout << "Stack a:\n";
	a.print();


	std::cout << "a[0] = 54\n";
	a.set(0, 54);
	a.print();

	s = a.get_size();
	for (int i = s; i >= 0; --i)
	{
		a.pop(&r);
		std::cout << r << " - a[" << i << "]\n";
	}

	s = b.get_size();
	for (int i = s; i >= 0; --i)

	{
		b.pop(&r);
		std::cout << r << " - b[" << i << "]\n";
	}

	std::cout << "Stack a:\n";
	a.print();
	a.pop(&r);

	std::cout << "Stack b:\n";
	b.print();
	b.pop(&r);

	for (int i = 0; i < 20; ++i)
		a.push(i*10);
	std::cout << "Stack a:\n";
	a.print();
	std::cout << "\n";

	s = a.get_size();
	for (int i = s; i >= 15; --i)
	{
		a.pop(&r);
		std::cout << r << " - a[" << i << "]\n";
	}

	std::cout << "Stack a:\n";
	a.print();

	b = a;
	std::cout << "Stack b:\n";
	b.print();

	return 0;
}


