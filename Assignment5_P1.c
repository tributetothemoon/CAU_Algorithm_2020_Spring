#include <stdio.h>
#include <stdlib.h>

int main(void) {

	int *arr, n;
	printf("input n : ");
	scanf("%d", &n);

	if (n < 0) {
		printf("The input n should be positive number");
		return 0;
	}

	else if (n == 0 || n == 1) {	//when input n is 0 or 1
		printf("Fn = %d\n", n);
		return 0;
	}

	arr = (int*)malloc(sizeof(int) * (n+1));	//array to store fibonacci numbers

	arr[0] = 0;
	arr[1] = 1;

	for (int i = 2; i <= n; i++) {	//when input n is over 5
		arr[i] = arr[i - 2] + arr[i - 1];	//caculates number
	}

	printf("Fn = %d\n", arr[n]);	//display output
	free(arr);

	return 0;
}