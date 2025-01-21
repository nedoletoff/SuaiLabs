#include <stdio.h>
#include <stdlib.h>
#define N 128

int main()
{
	int temp_count = 0;
	char str[N] = {'\0'};
	int count = 0;
	int first = 0;
	int numw = 0;
	char** words = NULL;
	char* temp = NULL;
	int len = 0;

	printf("Type string: ");
	for (int i = 0; i < N - 1; ++i)		//считать строку и посчитать пробелы
	{
		str[i] = getchar();
		if (str[i] == ' ')
		       ++numw;
		if (str[i] == '\n')
		{
			str[i] = ' ';
			++numw;
			break;
		}
	}
	
	words = (char**) malloc(numw * sizeof(char*));		//создать массив адресов

	for (int j = 0; j < N; ++j)		//посчитать количество слов и создать слова
	{
		if (str[j] != ' ' && str[j] != '\0')
		{
			len = 0;
			first = j;
			while (str[j] != ' ' && str[j] != '\0')
			{
				++len;
				++j;
			}
			words[count] = (char*) calloc((len), sizeof(char));
			for (int i = 0; i < len; ++i)
				words[count][i] = str[first++];
			words[count++][len] = '\0';
		}
	}

	for (int i = 0; i < count; ++i)		//упорядочить слова
	for (int j = i+1; j < count; ++j)
		{
			temp_count = 0;
			while  (words[i][temp_count] == (words[j][temp_count]))
				++temp_count;
			if (words[i][temp_count] > words[j][temp_count])
			{
				temp = words[i];
				words[i] = words[j];
				words[j] = temp;
			}
		}
		
	for (int i = 0; i < count; ++i)		//вывести слова в нужном порядке
	{
		int j = 0;
		while (words[i][j] != '\0')
		{
			putchar(words[i][j]);
			++j;
		}
		free(words[i]);
		printf("\n");
	}
	free(words)


	return 0;
}
