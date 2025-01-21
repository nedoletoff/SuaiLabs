#include <stdio.h>
#define N 128
// A = 65; z = 122; 0 = 48; Z = 90; a = 97; 
int main()
{
	char str[N] = {'\0'};
	int num[N] = {0};
	printf("Type string: ");
	str[0] = getchar();
	num[0] = str[0];
	for (int i = 1; i < N - 1; ++i)
	{
		str[i] = getchar();
		if ( str[i-1] == ' ' || str[i] == ' ') 
			num[i] = str[i];
		if (str[i] == '\0' || str[i] == '\n')
		{
			num[i] = ' ';
			break;
		}
	}
//	printf("\n");
		for (int i = 'A'; i <= 'z'; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (i == num[j])
			{
				while (num[j] != ' ')
				{
				       putchar(str[j]);
				       ++j;
				}
				printf("\n");
			}
		}
	}
	for (int i = 0; i < N; ++i)
		printf("%d ", num[i]);
	printf("\n");
	for (int i = 0; i < N; ++i)
		printf("%d ",str[ i]);
	printf("\n");

	return 0;
}
