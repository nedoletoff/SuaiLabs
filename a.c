#define _CRT_SECURE_NO_WARNINGS
#define BLOCK_SIZE 5
#include <stdio.h>
#include <stdlib.h>


int input(int** lst)
{
	int count = 0;
	int x = 1;
	int arr[BLOCK_SIZE] = {0};
	int** list = NULL;
	int** mas = (int**) malloc(1 * sizeof(int*));
	int* array;

	while (x != 0)
	{
		while(scanf("%d", &x) != 1 || getchar() != '\n')
		{
			printf("Error, try again\n");
			while (getchar() != '\n');
		}
		if (x)
			arr[count % BLOCK_SIZE] = x;
		if (x && ++count % BLOCK_SIZE == 0)
		{
			list = (int**) calloc(((count / BLOCK_SIZE) + 1 ), sizeof(int*));
			list[(count / BLOCK_SIZE) - 1] = (int*) calloc(BLOCK_SIZE, sizeof(int));

			for (int i = 0; i < (count / BLOCK_SIZE) - 1; ++i)
				list[i] = (int*) mas[i];

			for (int j = 0; j < BLOCK_SIZE; ++j)
				list[(count / BLOCK_SIZE) - 1][j] = (int) arr[j];
			mas = (int**) list;
		}
	}

	mas[count / BLOCK_SIZE] = (int*) malloc(count % BLOCK_SIZE * sizeof(int));
	for (int i = 0; i < count % BLOCK_SIZE; ++i)
		mas[count / BLOCK_SIZE][i] = arr[i];

	array = (int*) calloc((count), sizeof(int));
	for (int i = 0; i < count; ++i)
		array[i] = mas[i / BLOCK_SIZE][i % BLOCK_SIZE];
	for (int i = 0; i <  count / BLOCK_SIZE; ++i)
	{	
		free(mas[i]);
	}
	free(mas);

	*lst =  array;

	return count-1;

}

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void erase(int* arr, unsigned int  size, unsigned int number) 
{
	for (int i = number; i < size; ++i)
		swap(&arr[i], &arr[i+1]);
	arr[size] = 0;
}

int find(int* arr, int len)
{
        int check = 0;
	int size = len;
        for (int k = 1; k < len; ++k) //ищем локальные минимумы 
                if ((arr[k] < arr[k - 1]) && (arr[k] < arr[k + 1]))
                {
			erase(arr, size--, k);
                        check++;
                }
        return check;
}


int main()
{
        int  len = 0;
	int* arr = NULL;
	len = input(&arr);
        if (find(arr, len) != 0)
                for (int i = 0; i <= len; i++)
                        printf("%d ", arr[i]);
        else
                printf("The array does not contain local minima");
	putchar('\n');
	free(arr);
        return 0;
}
