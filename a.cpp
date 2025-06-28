#include "a.hpp"
#include <stdio.h>
#include <stdlib.h>
#define N 5

int type_int(int check)
{
	int n = 0, r = 1;
	while (r)
	{
		n = 0;
		if (!check)
			n = N;
		printf("Number should be greater then %d\n", n); 
		printf("Type int number: ");
		while (scanf("%d", &n) != 1 || getchar() != '\n') 
		{
			printf("Error, try again\n");
			while (getchar() != '\n');
		}
		if (check && n > 0 || n > N)
			r = 0;
	}
	return n;
}

double type_double()
{
	double n = 0;
	printf("Type number: ");
	while (scanf("%lf", &n) != 1 || getchar() != '\n')
	{
		printf("Error, try again\n");
		while (getchar() != '\n');
	}
	return n;
}

void pull_arr(double* arr, int size)
{
	for (int i = 0; i < size; ++i)
		arr[i] = type_double();
	putchar('\n');
}

void update_abs_arr(double* abs_arr, double* arr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < N; ++j)
			abs_arr[i] += arr[(i+j) % size];
		abs_arr[i] /= N;
	}
}

void print_arr(double* abs_arr, double* arr, int size)
{
	double max = abs_arr[0];
	int num = 0;
	for (int i = 0; i < size; ++i)
		if (abs_arr[i] > max)
		{
			max = abs_arr[i];
			num = i;
		}
	printf("Answer:");
	for (int i = 0; i < N; ++i)
		printf("\t%lf", arr[(num + i) % size]);
	putchar('\n');
}

int get_index(double* arr, int size, int gap)
{
	double max;
	double temp = 0;
	int index = -1;
	for (int i = 0; i < size; ++i)
	{
		temp = 0;
		for (int j = 0; j < gap; ++j)
			temp += arr[(i + j) % size];
		temp /= gap;
		if (index == -1 || temp > max)
		{
			max = temp;
			index = i;
		}
	}
	printf("Ans = %d\n", index);
	return index;
}
