#include <stdio.h>
#include <stdlib.h>
#define N 256

void inputs(char* string)
{
	int len = 0;
	printf("Type string: ");
	for (len = 0; len < N - 1; ++len)	
	{
		string[len] = getchar();
		if (string[len] == '\n')
		{
			string[len] = '\0';
			break;
		}
	}
}

int create_words(char* string, char** words)
{
	int count = 0;
	int len = 0;
	int first = 0;
	for (int j = 0; j < N; ++j)		
	{
		if (string[j] != ' ' && string[j] != '\0' && string[j] != '\t')
		{
			len = 0;
			first = j;
			while (string[j] != ' ' && string[j] != '\0' && string[j] != '\t')
			{
				++len;
				++j;
			}
			words[count] = (char*) malloc((len) * sizeof(char));
			for (int i = 0; i < len; ++i)
				words[count][i] = string[first++];
			words[count++][len] = '\0';
		}
	}
	return count;
}

void put_words(char** words, int count, int check)
{
	int lenw = 0;
	for (int i = 0; i < count; ++i)		//вывести слова в нужном порядке
	{
		lenw = 0;
		while (words[i][++lenw] != '\0');
		if (check)
		while (lenw >= 0)
			putchar(words[i][--lenw]);
		else 
		{
			for (int j = 0; j < lenw; ++j)
				if (j % 2)
					putchar(words[i][j-1]);
				else
					putchar(words[i][j+1]);
			if (lenw % 2)
				putchar(words[i][lenw-1]);
		}
		printf("\n");
		free(words[i]);		
	}
}

int main()
{
	char str[N] = {'\0'};
	int count = 0;
	char* words[N/2];
	int check = 0;
	
	printf("Type number: ");
    	while(scanf("%d", &check) != 1 || getchar() != '\n')
    	{
        	printf("Error, try again\n");
        	while (getchar() != '\n');
   	}
	inputs(str);
	count = create_words(str, words);
	put_words(words, count, check);


		
	return 0;
}
