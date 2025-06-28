#include <stdio.h>
#include <stdlib.h>
#define N 256

int inputs(char* str)
{
        int numw = 0;
	for (int i = 0; i < N - 1; ++i)	
	{
		str[i] = getchar();
		if (str[i] == ' ')
		       ++numw;
		if (str[i] == '\n')
		{
			str[i] = '\0';
			++numw;
			break;
		}
	}
        return numw;
} 

void inputn(int* number)
{
	printf("Type number: ");
	while(scanf("%d", number) != 1 && getchar() != '\n')
	{
		printf("Try again\n");
		while (getchar() != '\n');
	}
	while (getchar() != '\n');
}



int create_words(char* str, char** words, int* max_min, int check)
{
	int first = 0;
	int len = 0;
	int count = 0;

	for (int j = 0; j < N; ++j)
		if (str[j] != ' ' && str[j] != '\0' && str[j] != '\t')
		{
			len = 0;
			first = j;
			while (str[j] != ' ' && str[j] != '\0' && str[j] != '\t')
			{
				++len;
				++j;
			}
			words[count] = (char*) malloc(len * sizeof(char));
			for (int i = 0; i < len; ++i)
				words[count][i] = str[first++];
			words[count++][len] = '\0';
			if (check)
			{
				if (*max_min < len)
					*max_min = len;
			}
			else
			       if (*max_min > len)
					*max_min = len;
		}
	return count;
}

void clear_words(char** words, int start, int stop)
{
	for (int i = start; i < stop; ++i)
	{
		free(words[i]);	
		words[i] = NULL;
	}
}

int count_lenw(char* word)
{	
	int len = 0;
	while (word[++len] != '\0');
	return len;
		
	
}

void put_words(char** words, char* word, int max_min, int count)
{

	for (int i = 0; i < count; ++i)	
	{
		if (count_lenw(words[i]) != max_min)
			printf("%s ", words[i]);
		else 
			printf("%s ", word);
		free(words[i]);
		words[i] = NULL;
	}
	putchar('\n');
}

int main()
{
	char str[N] = {'\0'};
	char word[N] = {'\0'};
	int count = 0;
	int numw = 0;
	char** words = NULL;
	int check = 0;
	int max_min = N;

	inputn(&check);
	printf("Type string: ");	
	numw = inputs(str);
	printf("Type word: ");
	inputs(word);

	if (check) 
		max_min = 0;

	words = (char**) malloc(numw * sizeof(char*));
	count = create_words(str, words, &max_min, check);
	clear_words(words, numw, count);
	put_words(words, word, max_min, count);
		
	free(words);

	return 0;
}
