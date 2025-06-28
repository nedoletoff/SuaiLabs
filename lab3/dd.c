#include <stdio.h>

int meter(char* a)
{
	int count = 0;
	while (a[++count] != '\0');
	return count;
}

int inputcheck(char* a)
{ 
	int len = meter(a);
	int t = 0;
	int check = 1;
	if (a[t] == '-')
		++t;
	if ((a[t] > '0' && a[t] <= '9') || (a[t] == '0' && len == t+1))
	{
		while (++t < len)
			if (a[t] < '0' || a[t] > '9')
			{
				printf("\n%d - %d - ", t, a[t]);
				puts("1");
				check = 0;
			}
	}
	else if (a[t] == '0')
	{
		++t;
		if (a[t] != 'x')
			while (++t < len)
				if (a[t] < '0' || a[t] > '7')
				{
					puts("2");
					check = 0;
				}
		if (a[t] == 'x')
			while (++t < len)
				if (a[t] < '0' || (a[t] > '9' && a[t] < 'A') || a[t] > 'F')
				{
					puts("3");
					check = 0;
				}
	}
	else 
	{
		puts("4");
		check = 0;
	}
	return check;
}

			


int conv(char* a)
{
	int number = 0;
	int len = meter(a);
	if (a[0] != '-')
	{
		if (len > 0 && a[0] != '0')
			for (int i = 0; i < len; ++i)
			{
				number *= 10;
				number += (a[i] & 0x0F);
			}
		else if (len > 1 && a[1] != 'x')
			for (int i = 1; i < len; ++i)
			{
				number *= 8;
				number += (a[i] & 0x0F);
			}
		else if (len > 2 && a[1] == 'x')
			for (int i = 2; i < len; ++i)
			{
				number *= 16;	
				if (a[i] > '9')
					number += (a[i] & 0x0F) + 9;
				else 
					number += (a[i] & 0x0F);
			}
	}
	if (a[0] == '-')
	{
		if (len > 1 && a[1] != '0')
			for (int i = 1; i < len; ++i)
			{
				number *= 10;
				number += (a[i] & 0x0F);
			}
		else if (len > 2 && a[2] != 'x')
			for (int i = 2; i < len; ++i)
			{
				number *= 8;
				number += (a[i] & 0x0F);
			}
		else if (len > 3 && a[2] == 'x')
			for (int i = 3; i < len; ++i)
			{
				number *= 16;	
				if (a[i] > '9')
					number += (a[i] & 0x0F) + 9;
				else 
					number += (a[i] & 0x0F);
			}
		number = -number;
	}


	return number;
}

int check(int a, int b)
{	
	int c = b;
	int count = 0;

	if (a == 0)
		return 0;

	while (c > 1 || c < 0)
	{
		c /= a;
		if (c < 0)
			c *= -1;
		++count;
	}

	c = 1;

	while (count != 0)
	{
		c *= a;
		--count;
	}
	if (c == b)
		return 1;
	else 
		return 0;
}

int func(char* a, char* b)
{
	int c, d;
	c = conv(a);
	d = conv(b);
	return check(c, d);
}

int main()
{
	char a[256];
       	char b[256];
	char* c = "-0x5";
	char* d = "-0x7D";
	char* e = "05";
	char* f = "031";

	do 
	{
		printf("Type a: "); 
		for (int i = 0; i < 256; ++i)
		{
			a[i] = getchar();
			if (a[i] == '\n')
			{
				a[i] = '\0';
				break;
			}
		}	
	}
	while (!inputcheck(a));

	do 
	{
		printf("Type b: "); 
		for (int i = 0; i < 256; ++i)
		{
			b[i] = getchar();
			if (b[i] == '\n')
			{
				b[i] = '\0';
				break;
			}
		}	
	}
	while (!inputcheck(b));

	if (func(a, b))
		printf("Function(%s, %s) = True\n", a, b);
	else 
		printf("Function(%s, %s) = False\n", a, b);

	if (func(c, d))
		printf("Function(%s, %s) = True\n", c, d);
	else 
		printf("Function(%s, %s) = False\n", c, d);

	if (func(e, f))
		printf("Function(%s, %s) = True\n", e, f);
	else 
		printf("Function(%s, %s) = False\n", e, f);

	return 0;
}
