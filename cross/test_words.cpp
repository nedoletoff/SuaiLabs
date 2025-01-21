#include <fstream>
#include <iostream>
#include "words.hpp"

int main()
{
	try
	{
		Words w("inputfile.txt");
		for (size_t i = 0; i < w.get_words_numbers(); i++)
		{
			std::cout << w.get_word(i) << std::endl;
			w.change_word_status(i, true);
		}
		for (size_t i = 0; i < w.get_words_numbers(); i++)
			std::cout << w.get_word_status(i) << " - " << i << std::endl;
		w.get_word_status(43);
	}
	catch (Exception e)
	{
		std::cout << e << std::endl;
	}

	return 0;
}

