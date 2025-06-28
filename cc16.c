#include <stdio.h>
#define N 128
// A = 65 z = 122
int main()
{
	char str[N] = {'\0'};
	int num[N] = {0};
	printf("Type string: ");
	for (int i = 0; i < N - 1; ++i)
	{
		str[i] = getchar();
		if (i == 0 || str[i-1] == 32 || str[i] == 32) 
			num[i] = str[i];
		if (str[i] == '\0' || str[i] == '\n')
		{
			num[i] = 32;
			break;
		}
	}
	/*
	for (int i = 0; i < N - 1; ++i)
	{
		putchar(str[i]);
		if (num[i] == 32)
			printf("\n");
	}
	
	for (int i = 0; i < N - 1; ++i)
		printf("%d ",num[i]);
	*/
	for (int i = 65; i < 123; ++i)
	{
		for (int j = 0; j < N - 1; ++j)
		{
			if (i == num[j])
			{
				while (num[j] != 32)
				{
				       putchar(str[j]);
				       ++j;
				}
				printf("\n");
			}
		}
	}


	return 0;
}
