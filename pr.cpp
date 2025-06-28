#include "pr.hpp"
#include <iostream>

Stack::Stack()
{
	top = -1;
	head = NULL;
	tail = NULL;
}

Stack::~Stack()
{
	node_t* cur = head;
	node_t* perv = NULL;
	for (int i = 0; i <= top; ++i)		
	{
		perv = cur;
		cur = cur->next;
		delete perv;
	}
}

Stack& Stack::operator=(Stack& a)
{
	if (&a == this)
		return *this;
	top = -1;
	if (a.head == NULL)
	{
		head = NULL;
		tail == NULL;
	}
	else 
	{
		node_t* cur = a.head;
		for (int i = 0; i <= a.top; ++i)		
		{
			this->push(cur->data);
			cur = cur->next;
		}
	}
	return *this;
}

Stack::Stack(Stack& a)
{
	top = -1;
	if (a.head == NULL)
	{
		head = NULL;
		tail == NULL;
	}
	else 
	{
		node_t* cur = a.head;
		for (int i = 0; i <= a.top; ++i)		
		{

			this->push(cur->data);
			cur = cur->next;
		}
	}
}


int Stack::get(int index, int* rv)
{
	if (index > top || index < 0)
	{
		std::cout << "Index out of scope" << std::endl;
		return 1;
	}
	node_t* cur = tail;
	for (int i = top; i != index; --i)
		cur = cur->prev;
	*rv = cur->data;
	return 0;
}

int Stack::set(int index, int value)
{
	if (index > top || index < 0)
	{
		std::cout << "Index out of scope" << std::endl;
		return 1;
	}
	node_t* cur = tail;
	for (int i = top; i != index; --i)
		cur = cur->prev;
	cur->data = value;
	std::cout << cur->data << "\n";
	return 0;
}

void Stack::push(int value)
{
//	std::cout << "push\n";
	top++;
	node_t* cur = tail;
	node_t* n = new node_t;
	n->data = value;
	n->next = NULL;
	if (head == NULL)
	{
		n->prev = NULL;
		head = n;
	}
	if (tail != NULL) 
	{
		cur->next = n;
		n->prev = cur;
	}
	tail = n;
}

int Stack::pop(int* rv)
{
	if (top < 0)
	{
		std::cout << "Stack is empty" << std::endl;
		return 1;
	}
	
	node_t* n = tail;
	top--;
	*rv = n->data;
	tail = n->prev;
	n->next = NULL;
	delete n;
	if (top == -1)
		head = NULL;
	
	return 0;
}

int Stack::get_size()
{
	return top;
}

void Stack::print()
{
	node_t* cur  = tail;
	for (int i = top; i >= 0; --i)
	{
		std::cout << "Stack[" << i << "] - " << cur->data << std::endl;
		cur = cur->prev;
	}
}

