#include <iostream>
#include "12.hpp"

int main()
{
	std::cout << "Start\n";
	String test1;
	String test2;
	char text[] = "Helloff";
	char t[] = "do";

	std::cout << "Insert test1\n";
	test1.add_string(t);
	test1.print();

	std::cout << "Insert test1\n";
	test1.insert('i');
	test1.print();

	std::cout << "Add string test2\n";
	test2.add_string(text);
	test2.print();

	std::cout << "Remove test2\n";
	test2.remove(2, 4);
	test2.print();
	
	std::cout << "test3 = test1\n";
	String test3 = test1;
	test3.print();

	std::cout << "test3 conc test2\n";
	test3.conc(test2);
	test3.print();
	
	std::cout << "test1\n";
	test1.print();

	String test4;
	test4	= test3 - test1;
	test1.print();
	test3.print();
	test4.print();

//	std::cout<< "operator-\n";
//	test1 - test2;
//	test1.print();
	return 0;
}
