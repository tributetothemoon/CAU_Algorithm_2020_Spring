#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SWAP(x,y) do {int temp=x; x=y; y=temp;} while(0)
#define FAIL -1
#define NSIZE 1000
typedef enum { false, true } bool;

typedef struct __Queue {
	int max;
	int cur;
	int	head;
	int tail;
	int* data;
}Queue;

Queue* createQue(int size) {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->cur = 0;
	queue->max = size;
	queue->head = 0;
	queue->tail = 0;
	queue->data = (int*)malloc(sizeof(int) * size);
	return queue;
}

bool enque(Queue* queue, int ele) {
	if (queue->cur < queue->max) {
		queue->data[queue->head++] = ele;
		queue->cur++;
		return true;
	}
	else return false;
}

int deque(Queue* queue) {
	if (0 < queue->cur) {
		int result = queue->data[queue->tail];
		queue->tail = (queue->tail + 1) % queue->max;
		queue->cur--;
		return result;
	}
	else return FAIL;
}

bool isNotEmpty(Queue* queue) {
	return queue->cur ? true : false;
}

void terminateQueue(Queue* queue) {
	free(queue->data);
	free(queue);
}

int temp_arr_for_merge[1000];

void bubblesort(int arr[], int n) {
	int i, j;
	for (i = n; 0 < i; i--) {
		for (j = 0; j + 1 < i; j++) {
			if (arr[j] > arr[j + 1]) SWAP(arr[j], arr[j + 1]);
		}
	}
}

void insertionsort(int arr[], int n) {
	int i, j, key;
	for (i = 0; i < n - 1; i++) {
		key = arr[i + 1];
		for (j = i; 0 <= j && key < arr[j]; j--) {
			arr[j+1] = arr[j];
		}
		arr[j+1] = key;
		}
}

void mergesort_r(int arr[], int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		mergesort_r(arr, left, mid);
		mergesort_r(arr, mid + 1, right);

		//merge
		int temp_i = left;
		int left_i = left;
		int right_i = mid + 1;

		while (left_i <= mid && right_i <= right) {
			if (arr[left_i] < arr[right_i]) {
				temp_arr_for_merge[temp_i] = arr[left_i];
				left_i++;
			}
			else {
				temp_arr_for_merge[temp_i] = arr[right_i];
				right_i++;
			}
			temp_i++;
		}
		if (left_i <= mid) {
			while (left_i <= mid) {
				temp_arr_for_merge[temp_i] = arr[left_i];
				temp_i++;
				left_i++;
			}
		}
		else {
			while (right_i <= right) {
				temp_arr_for_merge[temp_i] = arr[right_i];
				temp_i++;
				right_i++;
			}
		}
		for (int i = left; i < right + 1; i++) {
			arr[i] = temp_arr_for_merge[i];
		}

	}
}

void mergesort(int arr[], int n) {mergesort_r(arr, 0, n-1);}

void radixsort(int arr[], int n) {
	Queue* queue[10];
	int i, t;
	int divisor = 1;
	int que_index;
	for (i = 0; i < 10; i++) queue[i] = createQue(n);

	for (i = n; 1 < i; i /= 10) {
		for (int j = 0; j < n; j++) {
			que_index = (arr[j] % (divisor * 10)) / divisor;
			enque(queue[que_index], arr[j]);
		}
		t = 0;
		for (int j = 0; j < 10; j++) {
			while (isNotEmpty(queue[j])) {
				arr[t++] = deque(queue[j]);
			}
		}
		divisor *= 10;
	}

	for (i = 0; i < 10; i++) terminateQueue(queue[i]);
}

void quicksork(int arr[], int n) {
}

void bucketsort(int arr[], int n) {
}

int arr_10[10];
int arr_100[100];
int arr_1000[1000];
static char* sort[] = { "Bubble Sort", "Insertion Sort", "Merge Sort", "Radix Sort", "Quicksort", "Bucket Sort" };

int main() {
	srand(time(NULL));
	clock_t start, end;
	float total_time;

	int *arr = NULL;
	void (*func[])(int[], int) = { bubblesort, insertionsort, mergesort, radixsort, quicksork, bucketsort };

	for (int sort_i = 0; sort_i < 4; sort_i++) {

		printf("-----------------------------------%s-----------------------------------\n", sort[sort_i]);
		
		for (int n = 10; n <= NSIZE; n *= 10) {

			switch (n) {
			case 10:
				arr = arr_10;
				break;
			case 100:
				arr = arr_100;
				break;
			case 1000:
				arr = arr_1000;
				break;
			}

			printf("Array Size : %d\n", n);
			printf("Before sorting\n{");
			for (int j = 0; j < n; j++) {
				arr[j] = rand() % n;
				printf("%d, ", arr[j]);
			}
			printf("\b\b}\n");

			printf("\nSorting start\n\n");
			start = clock();
			func[sort_i](arr, n);
			end = clock();
			total_time = (float)(end - start);

			printf("After sorting\n{");
			for (int j = 0; j < n; j++) printf("%d, ", arr[j]);
			printf("\b\b}\n");
			printf("Total time : %fms\n\n", total_time);
		}
		
	}

	return 0;
}