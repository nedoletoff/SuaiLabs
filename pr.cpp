#include "pr.hpp"
#include <cstdio>
#include <iostream>


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

int open_file(char* name, int mode)
{
	FILE* rFile = fopen(name, "r");
	if (rFile)
	{
		if (!(mode))
		{
			std::cout << "File already exist" << std::endl;
			fclose(rFile);
			return 1;
		}
	}
	else 
	{

		if (mode)
		{
			std::cout << "File doesnt exist" << std::endl;
			return 2;
		}
	}
	return 0;
}
/* //"jsfjsl\\sd\"\fs\\fd\s\\s\'fskfsk'\\"
 * std::cout << "E" << std::endl;
*/
 

void read_and_write(char* cppfile, char* txtfile)
{
//	std::cout << "Hello world" << std::endl;
	FILE* rFile = fopen(cppfile, "r");
	FILE* wFile = fopen(txtfile, "w");
	char temp[N+1] = {'\0'};
	int check = 0;
	while (fgets(temp, N, rFile) != NULL)
	{
		for (int i = 0; i < N || temp[i] == '\0'; ++i)
		{
			if (temp[i] == '*' && temp[i+1] == '/')
				check = 0;
			if (temp[i] == '/' && temp[i+1] == '*')
				check = 1;
			if (check)
				break;
			if (temp[i] == '/' && temp[i+1] == '/')
				break;
			if (temp[i] == '\'')
			{
				fputc(temp[++i], wFile);
				if (temp[i] == '\\')
					fputc(temp[++i], wFile);
				fputc('\n', wFile);
				i++;
			}
			if (temp[i] == '\"')
			{
				while (temp[++i] != '\"')
				{
					if (temp[i] == '\\')
					{
						fputc(temp[i], wFile);
						fputc(temp[++i], wFile);
					}
					else
						fputc(temp[i], wFile);
				}
				fputc('\n', wFile);
			}
		}
		for (int i = 0; i < N; ++i)
			temp[i] = '\0';
	}
	fclose(wFile);
	fclose(rFile);
}



