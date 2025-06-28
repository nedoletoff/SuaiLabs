#include "pr.hpp"
#include <cstdio>
#include <iostream>
#include <cctype>


void get_filename(char* n)
{
	int check = -2;
	while (check <= 0)
	{
		if (check == -1)
			std::cout << "Try again" << std::endl;
		std::cout<< "Type file name" << std::endl;
		std::cin.getline(n, SIZE);
		for (int i = 0; i < SIZE; ++i)
		{	
			if (n[i] == '\0')
			{
				check = i;
				break;
			}	
			if (n[i] <= ' ')
			{
				check = -1;
				break;
			}
		}
	}
}

int open_file(char* name)
{
	FILE* rFile = fopen(name, "r");
	if (!(rFile))
	{
			std::cout << "File doesnt exist" << std::endl;
			return 1;
	}
	fclose(rFile);
	return 0;
}

int count_words(char* txtfile)
{
	FILE* rFile = fopen(txtfile, "r");
	int count = 0;
	int check = 0;
	char ch;
	while ((ch = fgetc(rFile)) != EOF)
	{
		if (ch > ' ' && !check)
			check = 1;
		if (ch <= ' ' && check)
		{
			count++;
			check = 0;
		}
	}
	fclose(rFile);
	return count;
}

int isvowel(char ch)
{
	char c = ch;
	if (isupper(c))
		c = tolower(c);
	switch(c)
	{
		case 'a':
		case 'e':
		case 'u':
		case 'i':
		case 'o':
		case 'y':
		case 'q':
			return 1;
	}
	return 0;
}

void print_words(char** mas, int size)
{
	int lstword = 0;
	int wordsize = 0;
	for (int i = 0; i < size; ++i)
	{
		for (wordsize = 0; mas[i][wordsize] != '\0'; ++wordsize);
		if (lstword && isvowel(mas[i][0]))
				std::cout << mas[i] << std::endl;
		if (isvowel(mas[i][wordsize - 1]))
		       lstword = 0;
		else 
			lstword = 1;
	}
}

void read_and_pull(char* txtfile, char*** mas, int size)
{
	int countl = 0, countw = 0;
	char ch;
	char temp[N] = {'\0'};
	char** str = new char*[size];

	FILE* rFile = fopen(txtfile, "r");
	while ((ch = char(fgetc(rFile))) != EOF)
	{
		if (ch > ' ')
			temp[countl++] = char(ch);
		if (ch <= ' ' && countl)
		{
			str[countw] = new char[++countl];
			for (int i = 0; i < countl; ++i)
			{
				str[countw][i] = temp[i];
				temp[i] = {'\0'};
			}
			countl = 0;
			countw++;
		}
	}
	fclose(rFile);

	*mas = str;

}




