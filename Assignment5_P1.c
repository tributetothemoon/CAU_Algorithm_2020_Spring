#include <stdio.h>
#include <stdlib.h>

int main(void) {

	int *arr, n;
	printf("input n : ");
	scanf("%d", &n);

	if (n < 0) exit(1);
	else if (n == 0 || n == 1) {
		printf("Fn = 1\n");
		return 0;
	}

	arr = (int*)malloc(sizeof(int) * n);
	arr[0] = 1;
	arr[1] = 1;

	for (int i = 2; i < n; i++) {
		arr[i] = arr[i - 2] + arr[i - 1];
	}

	printf("Fn = %d\n", arr[n-1]);
	free(arr);

	return 0;
}