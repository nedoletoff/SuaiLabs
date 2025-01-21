#include "pr.hpp"
#include <iostream>

#define NUM 3

int main()
{
	char txtfile[NUM][SIZE] = {'\0'};
	list_t l[NUM];
	list_t res[2];

	for (int i = 0; i < NUM; ++i)
		init(&(l[i]));
	for (int i = 0; i < 2; ++i)
		init(&(res[i]));

	std::cout << "File to read:" << std::endl;
	for (int i = 0; i < NUM; ++i)
		do
		  get_filename(txtfile[i]);
		while (open_file(txtfile[i]));


	for (int i = 0; i < NUM; ++i)
	{
		insert_str(txtfile[i], &(l[i]));
	}

	sort_link(&(l[0]), &(l[1]), &(res[0]));

	for (int i = 0; i < NUM-2; ++i)
		sort_link(&(l[i+2]), &(res[i%NUM]), &(res[(i+1)%NUM]));


	for (int i = 1; i < NUM; i++)
		my_link(&(l[i-1]), &(l[i]));

	node_t* n = res[NUM%2].head;
	node_t* p = l[0].head;

	std::cout << "Ans 1:" << std::endl;
	print(n, res[NUM%2].size);
	std::cout << "Ans 2:" << std::endl;
	print(p, l[NUM-1].size);

	destroy(&l[NUM-1]);
//	for (int i = 0; i < NUM; ++i)
//		destroy(&(l[i]));
	for (int i = 0; i < 2; ++i)
		destroy(&(res[i]));
	return 0;
}
