#include "pr.hpp"
#include <iostream>


int main()
{
	char cppfile[SIZE] = {'\0'};
	char txtfile[SIZE] = {'\0'};
	std::cout << "File to read:" << std::endl;
	do 
		get_filename(cppfile);
	while (open_file(cppfile, 1));
	std::cout << "File to write:" << std::endl;
	do 
		get_filename(txtfile);
	while (open_file(txtfile, 0));
	read_and_write(cppfile, txtfile);	
	return 0;
}
