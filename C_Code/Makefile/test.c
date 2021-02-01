#include <stdio.h>
#include "sub.h"
#include "add.h"
int main(void)
{
	int a = 10, b = 12;
	float x = 1.23456, y = 9.87654321;
	printf("int a+b is:%d\n", addint(a, b));
	printf("int a-b is:%d\n", subint(a, b));
	printf("int x+y is:%f\n", addfloat(x, y));
	printf("int x-y is:%f\n", subfloat(x, y));
	return 0;
}
