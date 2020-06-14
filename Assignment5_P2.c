#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define INVALID 2147483647

//to remember all the pointer that should be freed
typedef struct __List__ {
	void* pointer;
	struct __List__* next;
}List;

List* head;
void add_list(void* ptr) {	//ptr to be freed
	List* node = (List*)malloc(sizeof(List));
	node->pointer = ptr;
	node->next = head;
	head = node;
}

void* my_malloc(unsigned int size) {
	void* ptr = malloc(size);
	add_list(ptr);
	return ptr;
}

int main(void) {

	int d[4];	//dimensions
	d[0] = 5;
	d[3] = 10;
	int cost[4][4];	//required computation number
	for (int i = 0; i < 4; i++) cost[i][i] = 0;

	printf("A sequence of dimensions of matrices < 5, d1, d2, 10>\n");
	printf("input d1 : ");
	scanf("%d", &d[1]);
	printf("input d2 : ");
	scanf("%d", &d[2]);
	printf("\nA sequence of dimensions of matrices < 5, %d, %d, 10>\n", d[1], d[2]);

	int optimal_chain = 0;

	//find smallest computation from Ai to Aj
	for (int dia = 1; dia < 3; dia++) {
		int i = 0;	//i = 0 ~ 2
		int j = i + dia;	//j = 1 ~ 2
		while (j < 3) {
			int min = INVALID;
			int temp;
			for (int k = i; k < j; k++) {	//0<=k<=1, 1<=k+1<=2
				temp = cost[i][k] + cost[k + 1][j] + d[i] * d[k + 1] * d[j + 1];
				if (temp < min) {
					optimal_chain = k;
					min = temp;
				}
			}
			cost[i][j] = min;
			i++;
			j++;
		}
	}

	printf("The optimal chain is %s\n", optimal_chain ? "(A1A2)A3" : "A1(A2A3)");
	printf("The smallest computation number is %d\n", cost[0][2]);
	puts("\n[Output]");

	srand(time(NULL));
	int** mat[3];	//mat[i] == Ai (i-th matrix)

	for (int n = 0; n < 3; n++) {
		printf("\n[A%d]\n", n + 1);
		mat[n] = (int**)my_malloc(sizeof(int*) * d[n]);	//generate rows
		for (int i = 0; i < d[n]; i++) {
			mat[n][i] = (int*)my_malloc(sizeof(int) * d[n + 1]);	//generate columns
			for (int j = 0; j < d[n + 1]; j++) {
				mat[n][i][j] = rand() % 5;	//random number
				printf("%d ", mat[n][i][j]);
			}
			puts("");
		}
	}

	int** temp_mat;
	int** result_mat;
	result_mat = (int**)my_malloc(sizeof(int*) * d[0]);
	for (int i = 0; i < d[0]; i++) {
		result_mat[i] = (int*)my_malloc(sizeof(int) * d[3]);
	}

	if (optimal_chain) {	//(A1A2)A3
		temp_mat = (int**)my_malloc(sizeof(int*) * d[0]);	//A1*A2
		for (int i = 0; i < d[0]; i++) {
			temp_mat[i] = (int*)my_malloc(sizeof(int) * d[2]);
		}

		printf("\n[A1*A2]\n");
		for (int i = 0; i < d[0]; i++) {
			for (int j = 0; j < d[2]; j++) {
				int temp = 0;
				for (int k = 0; k < d[1]; k++) {
					temp += mat[0][i][k] * mat[1][k][j];
				}
				temp_mat[i][j] = temp;
				printf("%d	", temp_mat[i][j]);
			}
			puts("");
		}

		printf("\n[Answer]\n");
		for (int i = 0; i < d[0]; i++) {
			for (int j = 0; j < d[3]; j++) {
				int temp = 0;
				for (int k = 0; k < d[2]; k++) {
					temp += temp_mat[i][k] * mat[2][k][j];
				}
				result_mat[i][j] = temp;
				printf("%d	", result_mat[i][j]);
			}
			puts("");
		}

	}
	else {	//A1(A2A3)
		temp_mat = (int**)my_malloc(sizeof(int*) * d[1]);	//A2*A3
		for (int i = 0; i < d[1]; i++) {
			temp_mat[i] = (int*)my_malloc(sizeof(int) * d[3]);
		}

		printf("\n[A2*A3]\n");
		for (int i = 0; i < d[1]; i++) {
			for (int j = 0; j < d[3]; j++) {
				int temp = 0;
				for (int k = 0; k < d[2]; k++) {
					temp += mat[1][i][k] * mat[2][k][j];
				}
				temp_mat[i][j] = temp;
				printf("%d	", temp_mat[i][j]);
			}
			puts("");
		}

		printf("\n[Answer]\n");
		for (int i = 0; i < d[0]; i++) {
			for (int j = 0; j < d[3]; j++) {
				int temp = 0;
				for (int k = 0; k < d[1]; k++) {
					temp += mat[0][i][k] * temp_mat[k][j];
				}
				result_mat[i][j] = temp;
				printf("%d	", result_mat[i][j]);
			}
			puts("");
		}
	}

	//free all the allocated ptr
	List* node = head;
	List* temp;
	while (node) {
		temp = node->next;
		free(node->pointer);
		free(node);
		node = temp;
	}

	return 0;
}