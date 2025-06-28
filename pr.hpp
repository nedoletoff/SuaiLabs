#pragma once
#define N 5

typedef struct node_t
{
	int data;
	struct node_t* next;
	struct node_t* prev;
}	node_t;


class Stack
{
	private:
		int top;
		node_t* head;
		node_t* tail;
	public:
		Stack();
		Stack(Stack&);
		Stack& operator=(Stack&);
		~Stack();
		int set(int, int);
		int get(int, int*);
		void push(int);
		int pop(int*);
		int get_size();
		void print();
};

