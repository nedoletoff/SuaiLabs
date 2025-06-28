#include <stdio.h>
#include <stdlib.h>
#define N 128

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

int create_words(char* str, char** words, int* maxlen, int numw)
{
	int first = 0;
	int len = 0;
	int count = 0;

	for (int j = 0; j < N; ++j)
	{
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
			if (*maxlen < len)
				*maxlen = len;
		}
	}
	for (int i = count; i < numw; ++i)
		free(words[i]);
	return count;
}

void count_lenw(int* arr, char** words, int count)
{

	for (int i = 0; i < count; ++i)	
	{
		int len = 0;
		while (words[i][++len] != '\0');
		arr[i] = len;
	}
}

void put_words(char** words, char* word, int* arr, int maxlen, int count)
{

	for (int i = 0; i < count; ++i)	
	{
		if (arr[i] != maxlen)
			puts(words[i]);
		else 
			puts(word);
		free(words[i]);
	}
}

int main()
{
	char str[N] = {'\0'};
	char word[N] = {'\0'};
	int count = 0;
	int numw = 0;
	int maxlen = 0;
	char** words = NULL;
	int* arr = NULL;

	printf("Type string: ");	
	numw = inputs(str);
	printf("Type word: ");
	inputs(word);

	words = (char**) malloc(numw * sizeof(char*));
	count = create_words(str, words, &maxlen, numw);
	arr = (int*) calloc(count, sizeof(int));
	count_lenw(arr, words, count);
	put_words(words, word, arr, maxlen, count);
		
	free(words);
	free(arr);

	return 0;
}
