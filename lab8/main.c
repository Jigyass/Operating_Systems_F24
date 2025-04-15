#include <stdio.h>

int func(int input)
{
	input = input - 1;
	return input;
}

int main()
{
	int a=10;
	int b=5;
	int c=0;
	c=a+b;
	int call = func(c);
	printf("hello");
	return 0;
}
