#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include "pr.hpp"

void init(list_t* l)		//done
{
	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
}

void destroy(list_t* l)		//done
{
	node_t* cur = l->head;
	node_t* perv = NULL;
	while (cur != NULL)
	{
		perv = cur;
		cur = cur->next;
		free(perv);
	}
}

void push_back(list_t* l, char* val)	//done
{
	node_t* n;
	node_t* cur;
	n = (node_t*) malloc(sizeof(node_t));
	for (int i = 0; i < SIZE; ++i)
		n->value[i] = val[i];
       	n->next = NULL;
	if (l->head == NULL)
	{
		n->prev = NULL;
		l->head = n;
	}
	else
	{
		cur = l->tail; cur->next = n;
		n->prev = cur;
	}
	l->tail = n;
	++l->size;
}

int my_strcmp(char* str1, char* str2) // -1 <=; 1 >;
{
	int i = 0;
	while (str1[i] == str2[i] && str2[i] != '\0' && str1[i] != '\0')
		     ++i;
	if (str1[i] <= str2[i])
		return -1;
	if (str1[i] > str2[i])
		return 1;
	if (str2[i] == '\0')
		return 0;
	std::cout << "wtf" << std::endl;
	return -3;
}

void push_before(list_t* l, node_t* cur, char* val)	//done
{
	node_t* n;
	n = (node_t*) malloc(sizeof(node_t));
	for (int i = 0; i < SIZE; ++i)
		n->value[i] = val[i];
       	n->next = cur;
	if (l->head == cur)
	{
		l->head = n;
		n->prev = NULL;
	}
	else
	{
		cur->prev->next = n;
		n->prev = cur->prev;
	}
	cur->prev = n;

	++l->size;

}

void print(node_t* cur, size_t size) //done
{
	for (size_t i = 0; i < size; ++i)
	{
		std::cout << cur->value << std::endl;
		cur = cur->next;
		if (cur == NULL)
			break;
	}
	std::cout << std::endl;
}

void insert_sort(list_t* l, char* val)	//done
{
	if (l->head == NULL)
		push_back(l, val);
	else
	{
		node_t* cur;
		cur = l->head;
		while (my_strcmp(val, cur->value) == 1)
		{
			if (cur->next == NULL)
			{
				push_back(l, val);
				return;
			}
			cur = cur->next;
		}
		push_before(l, cur, val);
	}
}

void my_link(list_t* first, list_t* second) //not need done
{
//	std::cout << first->size << " " << second->size << std::endl;
	first->tail->next = second->head;
	second->head->prev = first->tail;
	first->tail = second->tail;
	second->head = first->head;
	first->size += second->size;
	second->size = first->size;
//	std::cout << first->size << " " << second->size << std::endl;
}

void sort_link(list_t* one, list_t* another, list_t* result)	// done
{
	node_t* first = one->head;
	node_t* second = another->head;
	while (first != NULL && second != NULL)
	{
		if (my_strcmp(first->value, second->value) == 1)
		{
			push_back(result, second->value);
			second = second->next;
		}
		else
		{
			push_back(result, first->value);
			first = first->next;
		}
	}
	if (first == NULL)
		while (second != NULL)
		{
			push_back(result, second->value);
			second = second->next;
		}
	else
		while (first != NULL)
		{
			push_back(result, first->value);
			first = first->next;
		}
}

void get_filename(char* n)	//done
{
	int check = -2;
	while (check <= 0)
	{
		if (check == -1)
			std::cout << "Try again" << std::endl;
		std::cout<< "Type file name" << std::endl;
		std::cin.getline(n, SIZE);
		for (int i = 0; i < SIZE; ++i)
		{
			if (n[i] == '\0')
			{
				check = i;
				break;
			}
			if (n[i] <= ' ')
			{
				check = -1;
				break;
			}
		}
	}
}

int open_file(char* name)	//done
{
	FILE* rFile = fopen(name, "r");
	if (!(rFile))
	{
		std::cout << "File doesnt exist" << std::endl;
		return 1;
	}
	fclose(rFile);
	return 0;
}

void insert_str(char* filename, list_t* l)	//done
{
	FILE* rFile = fopen(filename, "r");
	char str[SIZE] = {'\0'};
	char ch = '\0';
	int count = 0;

	while ((ch = char(fgetc(rFile))) != EOF)
	{
		if (ch > ' ')
		{
			str[count++] = ch;
		}
		else
		{
	  		if (count > 0)
			{
				insert_sort(l, str);
			}
			for (int i = 0; i < count; i++)
	    			str[i] = '\0';
			count = 0;
		}
	}
}
