#include "double_list.hpp"

int main()
{

	DoubleList<int> lst_int;

	lst_int.push_back(2);	
	lst_int.push_back(1);

	
	lst_int.push_front(3);
	lst_int.push_front(1);
	lst_int.print();
	lst_int.push_back(1);
	lst_int.push_back(2);
	lst_int.push_back(1);
	lst_int.print();
	std::cout << "size - " << lst_int.get_size() << std::endl;
	try 
	{
		lst_int.at();
	}
	catch(int i)
	{
		std::cout << i << "\tCaught an exception" << std::endl;
	}

	lst_int.print();

	std::cout << "find_and_erase(1)" << std::endl;
	lst_int.find_and_erase(1);
	lst_int.print();

	DoubleList<int> lst_int2;

	lst_int2.push_back(10);
	lst_int2.push_back(20);
	lst_int2.push_back(30);
	lst_int2.push_back(40);
	lst_int2.print();

	DoubleList<int> lst_int3;

	lst_int3.unite( lst_int, lst_int);
	lst_int3.print();

	DoubleList<Point> point_lst;

	struct Point e;
	e.x = 1; e.y = 2; e.z = 3;
	std::cout << e.x << " " << e.y << " " << e.z << std::endl;

	point_lst.push_back(e);
	e.x = 11;
	point_lst.push_back(e);
	std::cout << e.x << " " << e.y << " " << e.z << std::endl;
	e = point_lst.pop_back();
	std::cout << e.x << " " << e.y << " " << e.z << std::endl;

	try 
	{
		e = point_lst.pop_back();
		std::cout << e.x << " " << e.y << " " << e.z << std::endl;
	}
	catch(double r)
	{
		std::cout << r << std::endl;
		std::cout << "list is empty" << std::endl;
	}

	return 0;
}
