#include <stdio.h>

int ret(void)
{
	return (3);
}

int main(void)
{
	int arr[ret()];

	arr[0] = 1;
	arr[1] = 2;
	printf("%d\n", arr[0]);
	return (0);
}