#pragma once

typedef struct node_t 
{
	int value;
	struct node_t* prev;
	struct node_t* next;
} node_t;

typedef struct
{
	node_t* head;
	node_t* tail;
	size_t size;
} list_t;

void init(list_t*);
void destroy(list_t*);
void push_back(list_t*, int);
void print(list_t*);
int set(list_t*, int, int);
int get(list_t*, int, int*);
void erase(list_t*, node_t*);
void push_front(list_t*, int);
int find(list_t*, int, node_t**);
