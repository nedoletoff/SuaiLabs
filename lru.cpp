#include "lru.hpp"

LruCashe::LruCashe(size_t s)
{
	max_size = s;
	capscity = 0;
}

//LruCashe& LruCashe::operator=(const LruCashe& a);

size_t LruCashe::size()
{
	return capacity;
}


bool LruCashe::find(const std::string& value)
{
	if (data.find(value) != data.end())
		return true;
	return false;
}

void LruCashe::add(const std::string& value)
{
	if (capacity == max_size)
	{
		auto it = cashe.rbegin();
		std::string temp = *it;
		cashe.pop_back();
		data.erase(temp);
		--capacity;
	}
	cashe.push_front(value);
	data.insert({value, cashe.begin()});
	++capacity;
}

bool LruCashe::find_and_add(const std::string& value)
{
	bool res = find(value);
	if (!res)
		add(value);
	else
		replace(value);
	return res;
}

void LruCashe::replace(const std::string& value)
{
	auto ad = data[value];
	cashe.erase(ad);
	cashe.push_front(value);
	data[value] = cashe.begin();
}

