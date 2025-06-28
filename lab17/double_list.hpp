#include <iostream>
#include <string>
#pragma once

template <typename T>
class Node
{
	private:
		T data;
		Node<T>* next;
		Node<T>* prev;
	public:
		Node<T>()
		{
			next = NULL;
			prev = NULL;
		}

		void set_prev(Node<T>& a)
		{
			prev = &a;
		}

		void set_next(Node<T>& a)
		{
			next = &a;
		}

		void set_data(const T a)
		{
			data = a;
		}

		T get_data()
		{
			return data;
		}

		Node<T>* get_next()
		{
			return next;
		}

		Node<T>* get_prev()
		{
			return prev;
		}

		void make_head()
		{
			prev = NULL;
		}

		void make_tail()
		{
			next = NULL;
		}
		void print()
		{
			std::cout << data;
		}
		T erase()
		{
			if (next != NULL)
				next->set_prev(*get_prev());
			if (prev != NULL)
				prev->set_next(*get_next());
			return data;
		}
};

template <typename T>
class DoubleList
{
	private:
		Node<T>* head;
		Node<T>* tail;
		size_t size;
	public:
		DoubleList() 
		{
			size = 0;
			head = NULL;
			tail = NULL;
		}

		void push_back(const T d)
		{
			Node<T>* c = new Node<T>;
			if (head == NULL)
				head = c;

			c->set_data(d);

			if (tail != NULL)
			{
				Node<T>* t = tail;
				t->set_next(*c);
				c->set_prev(*t);
			}
			tail = c;
			++size;
//			std::cout << "push_back(" << d << ")" << std::endl;
		}

		T pop_back()
		{
			if (size)
			{
				Node<T>* cur = tail;
				T d = cur->get_data();
				if (tail->get_prev())
				{
					tail = tail->get_prev();
					tail->make_tail();
				}
				else 
				{
					tail = NULL;
					head = NULL;
				}
			
				delete cur;
				--size;
	
				return d;
			}
			else
			{
				throw 0.1;
			}
		}

		DoubleList<T>(DoubleList<T>& a)
		{
			head = NULL;
			tail = NULL;
			size = 0;
			if (a.size)
			{
				size = 0;
				Node<T>* cur = a.head;
				for (size_t i = 0; i < a.size; ++i)
				{
					push_back(cur->get_data());
					cur = cur->get_next();
				}
			}
		}

		DoubleList<T>& operator=(DoubleList<T>& a)
		{
			if (&a == this)
				return *this;
			while (head)
				pop_back();
			head = NULL;
			tail = NULL;
			size = 0;
			if (a.size)
			{
				size = 0;
				Node<T>* cur = a.head;
				for (size_t i = 0; i < a.size; ++i)
				{
					push_back(cur->get_data());
					cur = cur->get_next();
				}
			}
			return *this;
		}

		~DoubleList<T>()
		{
			while (tail) 
				pop_back();
		}

		void push_front(const T d)
		{
			Node<T>* h = head;
			Node<T>* c = new Node<T>;
			if (tail == NULL)
				tail = c;
			c->set_data(d);
			if (head != NULL)
			{
				h->set_prev(*c);
				c->set_next(*h);
			}
			head = c;
			++size;
//			std::cout << "push_front(" << d << ")" << std::endl;
		}

		void find_and_erase(const T value)
		{
			Node<T>* cur = head;
			while (cur != NULL)
			{
				if (cur->get_data() == value)
				{
					if (head == cur)
						head = cur->get_next();
					if (tail == cur)
						tail = cur->get_prev();
					cur->erase();
					--size;
				}
				cur = cur->get_next();
			}
		}

		void at()
		{
			throw 1;
		}

		size_t get_size()
		{
			return size;
		}

		void print()
		{
			std::cout << "print()" << std::endl;
			Node<T>* cur = head;
			for (size_t i = 0; i < size; ++i)
			{
				cur->print();
				std::cout << " \n";
				cur = cur->get_next();
			}
		}

		void unite(DoubleList<T>& a, DoubleList<T>& b)
		{
			*this = b;
			DoubleList<T> lst1(a);
			for (size_t i = 0; i < a.size; ++i)
				push_front(lst1.pop_back());

		}


};

struct Point
{
	int x;
	int y;
	int z;
};


