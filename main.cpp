#include "pr.hpp"
#include <iostream>


int main()
{
	char txtfile[SIZE] = {'\0'};
	int size = 0;
	char** mas = NULL;
	std::cout << "File to read:" << std::endl;
	do 
		get_filename(txtfile);
	while (open_file(txtfile));

	size = count_words(txtfile);
	read_and_pull(txtfile, &mas, size);
	print_words(mas, size);

	for (int i = 0; i < size; ++i)
		delete[] mas[i];
	delete[] mas;

	return 0;
}
