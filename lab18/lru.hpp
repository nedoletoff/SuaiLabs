#pragma once
#include <list>
#include <map>
#include <string>
#include <iostream>

class LruCashe
{
	private:
		size_t max_size;
		size_t capacity;
		std::list<std::string> cashe;
		std::map<std::string, std::list<std::string>::iterator> data;
	private:
		void replace(const std::string&);
		void add(const std::string&);
		bool find(const std::string&);
	public:
		LruCashe(size_t);
		size_t size();
		bool find_and_add(const std::string&);

	friend std::ostream& operator<<(std::ostream& os, const LruCashe& value)
	{
		for(std::string e : value.cashe)
			os << e <<  " ";
		return os;
	}
};
