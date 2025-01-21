#include "words.hpp"

Words::Words(std::string filename)
{
	std::list<std::string> words;
	numbers = 0;
	used_numbers = 0;
	std::ifstream file(filename);
	if (!file)
		throw Exception("file not found");

	std::string temp;
	file >> temp;
	words.push_back(temp);
	auto it = words.begin();
	std::cout << "Wrong words: ";
	for (file >> temp; !file.eof(); file >> temp)
        	if (temp.size() >= 3 && temp.size() <= 15)           
		{
			for (it = words.begin(); it  !=  words.end() && *it <= temp; it++)
				if (temp == *it)     
				{
					std::cout << temp << " (dublicate) ";
					words.erase(it--);
					break;
				}
			words.insert(it, temp);
       		}
		else
			std::cout << temp << " ";
	std::for_each(words.begin(), words.end(), [this](std::string a) { this->add_word(a); });
	std::cout << std::endl;
}

std::string Words::get_word(size_t n)
{
	if (n >= numbers)
		throw Exception("n out of range");

	return words_and_status[n].word;
}

bool Words::get_word_status(size_t n)
{
	if (n >= numbers)
		throw Exception("n out of range");

	return words_and_status[n].status;
}

void Words::change_word_status(size_t n, bool value)
{
	if (n >= numbers)
		throw Exception("n out of range");

	if (words_and_status[n].status != value)
	{
		if (value)
			used_numbers++;
		else
			used_numbers--;
	}
	words_and_status[n].status = value;
}

void Words::add_word(std::string value)
{	
	words_and_status.push_back({value, false});
	coordinates.push_back({0, 0, 0});
	numbers++;
}
size_t Words::get_words_numbers()
{
	return numbers;
}

size_t Words::get_words_used_numbers()
{
	return used_numbers;
}

bool Words::are_all_words_used()
{
    return (used_numbers == numbers);

}
Coordinates Words::get_coordinates(size_t n)
{
	if (n >= numbers)
		throw Exception("n out of range");
	return coordinates[n];
}

void Words::set_coordinates(size_t n, int o, size_t h, size_t w)
{
	if (n >= numbers)
		throw Exception("n out of range");
	coordinates[n].orientation = o;
	coordinates[n].h = h;
	coordinates[n].w = w;
}

void Words::set_coordinates(size_t n, int o)
{
	if (n >= numbers)
		throw Exception("n out of range");
	coordinates[n].orientation = o;
}
