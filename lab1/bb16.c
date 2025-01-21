#include <stdio.h>

int main()
{
	float x = 0, num = 0;
	float r = 1, min = 1;
	int tmp = 0, check = 0;

	for (int i = 0; i < 10; ++i)
	{
		printf("Type number: ");
		check = 0;
		if (scanf("%f", &x) == 1)
		{
			if (getchar() != '\n')
			{
				printf("Input Error\n");
				return 1;
			}
		}
		else 
		{
			printf("Input Error\n");
			return 1;
		}

		if (x < 0)
        	{
			x = -x;
			check = 1;
       		}
	
		tmp = (int) x;
		r = x - tmp;
		if (r < min)
		{
			min = r;
			if (check)
				num = -x;
			else 
				num = x;
		}
	}
	printf("Ans: %f\n", num);
	return 0;
}
		
