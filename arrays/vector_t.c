#include <stdio.h>
#include <stdlib.h>
#include "vector_t.h"

void init(vector_t* v) 		//O(1)
{
	v->data = NULL;
	v->size = 0;
	v->capacity = 0;
}

void destroy(vector_t* v) 	//O(1)
{
	if (v->data != NULL) free(v->data);
}

void push_back(vector_t* v, int val)	//O(n) or O(1)
{
	int* tmp = NULL;
	if (v->capacity == v->size)
	{
		if (v->capacity == 0) v->capacity = 1;
		v->capacity *= 2;
		tmp = (int*) malloc(v->capacity * sizeof(int));
		for (int i = 0; i < v->size; ++i) tmp[i] = v->data[i];
		free(v->data);
		v->data = tmp;
	}
	v->data[v->size++] = val;
}

int set(vector_t* v, int i, int val)
{
	if (i >= 0 && i < v->size)
		v->data[i] = val;
	return 0;
}

int get(vector_t* v, int i, int ans) 	//O(1)
{
	if (i >= 0 && i < v->size)
	{
		ans = v->data[i];
		return 1;
	}
	printf("Element %d doesnt exist", i);
	return 0;
}

void insert(vector_t* v, int i, int val)	//O(n)
{
	push_back(v, 0);
	for( int j = v->size - 1; j > i; --j)
		v->data[j] = v->data[j - 1];
	v->data[i] = val;
}

void erase(vector_t* v, int i)		//O(n)
{
	for ( int j = i; j < v->size - 1; ++j)
		v->data[j] = v->data[j + 1];
	--v->size;
}

void pop_back(vector_t* v)	//O(1)
{
	v->data[--v->size] = 0;
}

void shrink_to_fit(vector_t* v)		//O(n)
{
	if (v->capacity && v->size != v->capacity)
	{
		int* temp = NULL;
		temp = (int*) malloc(v->size * sizeof(int));
		for (int i = 0; i < v->size; ++i)
			temp[i] = v->data[i];
		free(v->data);
		v->capacity = v->size;
		v->data = temp;
	}
}

void print(vector_t* v) 	//O(n)
{
	for (int i = 0; i < v->size; ++i)
		printf("%d ", v->data[i]);
	printf("\n");
}
		
int find(vector_t* v, int value)         //O(n)
{
	for (int i = 0; i < v->size; ++i)
		if (value == v->data[i])
			return i;
	return -1;
}

