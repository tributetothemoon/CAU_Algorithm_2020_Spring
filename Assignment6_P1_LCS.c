#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { null, up, diagonal, left } direction;

int lcs_length[8][7];		//c
int lcs_direction[8][7];	//b

int lcs_Length(char X[], char Y[]) {

	int m = strlen(X) - 1;	//minus 1 because of dummy char
	int n = strlen(Y) - 1;

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (X[i] == Y[j]) {
				lcs_length[i][j] = lcs_length[i - 1][j - 1] + 1;
				lcs_direction[i][j] = diagonal;

			}
			else if (lcs_length[i - 1][j] >= lcs_length[i][j - 1]) {
				lcs_length[i][j] = lcs_length[i-1][j];
				lcs_direction[i][j] = up;
			}
			else {
				lcs_length[i][j] = lcs_length[i][j - 1];
				lcs_direction[i][j] = left;
			}
		}
	}

	return lcs_length[m][n];
	return 0;
}

void print_lcs(int table[][7], char X[], int i, int j) {
	if (i == 0 || j == 0) return;

	if (table[i][j] == diagonal) {
		print_lcs(table, X, i - 1, j - 1);
		printf("%c", X[i]);
	}
	else if (table[i][j] == up)
		print_lcs(table, X, i - 1, j);
	
	else
		print_lcs(table, X, i, j - 1);
}

int main(void) {

	char X[] = { 'x', 'A', 'B', 'C', 'B', 'D', 'A', 'B', 0 };	//x as dummy char

	char Y[] = { 'y', 'B', 'D', 'C', 'A', 'B', 'A', 0 };	//y as dummy char

	printf("LCS Length : %d\n", lcs_Length(X, Y));

	printf("LCS : ");
	print_lcs(lcs_direction, X, strlen(X)-1, strlen(Y)-1);	//minus 1 because of dummy char

	return 0;
}