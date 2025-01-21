#pragma once
typedef struct
{
	int* data;
	size_t size;
	size_t capacity;
} vector_t;

void init(vector_t*);
void destroy(vector_t*);
void push_back(vector_t*, int);
int set(vector_t*, int, int);
int get(vector_t*, int, int);
void insert(vector_t*, int, int);
void erase(vector_t*, int);
void pop_back(vector_t*);
void shrink_to_fit(vector_t*);
void print(vector_t*);
int find(vector_t*, int);

