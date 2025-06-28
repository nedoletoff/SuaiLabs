#include <stdio.h>
#include <stdlib.h>
#define N 256

int inputs(char* str, int check)
{
        int numw = 0;
	for (int i = 0; i < N - 1; ++i)	
	{
		str[i] = getchar();
		if (str[i] == ' ')
		       ++numw;
		if (str[i] == '\n' || str[i] == ' ' && check)
		{
			str[i] = '\0';
			++numw;
			break;
		}
	}
        return numw;
} 

int create_words(char* str, char** words, int* maxlen)
{
	int first = 0;
	int len = 0;
	int count = 0;

	for (int j = 0; j < N; ++j)
		if (str[j] != ' ' && str[j] != '\0')
		{
			len = 0;
			first = j;
			while (str[j] != ' ' && str[j] != '\0')
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
	return count;
}

void clear_words(char** words, int start, int stop)
{
	for (int i = start; i < stop; ++i)
		free(words[i]);
}

int count_lenw(char* word)
{	
	int len = 0;
	while (word[++len] != '\0');
	return len;
		
	
}

void put_words(char** words, char* word, int maxlen, int stop)
{

	for (int i = 0; i < stop; ++i)	
	{
		if (count_lenw(words[i]) != maxlen)
			printf("%s ", words[i]);
		else 
			printf("%s ", word);
		free(words[i]);
	}
	putchar('\n');
}

int main()
{
	char str[N] = {'\0'};
	char word[N] = {'\0'};
	int count = 0;
	int numw = 0;
	int maxlen = 0;
	char** words = NULL;

	printf("Type string: ");	
	numw = inputs(str, 0);
	printf("Type word: ");
	inputs(word, 1);

	words = (char**) malloc(numw * sizeof(char*));
	count = create_words(str, words, &maxlen);
	clear_words(words, numw, count);
	put_words(words, word, maxlen, count);
		
	free(words);

	return 0;
}
