#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SWAP(x,y) do {int temp=x; x=y; y=temp;} while(0)
#define FAIL -1
#define NSIZE 1000
typedef enum { false, true } bool;

//Bubble Sort
void bubblesort(int arr[], int n) {
	int i, j;
	for (i = n; 0 < i; i--) {
		for (j = 0; j + 1 < i; j++) {
			if (arr[j] > arr[j + 1]) SWAP(arr[j], arr[j + 1]);
		}
	}
}

//Insertion Sort
void insertionsort(int arr[], int n) {
	int i, j, key;
	for (i = 0; i < n - 1; i++) {
		key = arr[i + 1];
		for (j = i; 0 <= j && key < arr[j]; j--) {
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = key;
	}
}

//Merge Sort
int temp_arr_for_merge[1000];
void mergesort_recur(int arr[], int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		mergesort_recur(arr, left, mid);
		mergesort_recur(arr, mid + 1, right);

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

void mergesort(int arr[], int n) { mergesort_recur(arr, 0, n - 1); }	//recursively call mergesort_recur

//Radix Sort
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
		queue->data[queue->head] = ele;
		queue->head = (queue->head + 1) % queue->max;
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

void radixsort(int arr[], int n) {
	Queue* queue[10];	//Queue Array. Bucket size will be n/10.
	int i, t;
	int divisor = 1;
	int que_index;
	for (i = 0; i < 10; i++) queue[i] = createQue(n);	//create array of queue

	while (divisor < n) {	//depends on NSIZE

		//euque all of values from array
		for (i = 0; i < n; i++) {
			que_index = (arr[i] % (divisor * 10)) / divisor;
			enque(queue[que_index], arr[i]) ? true : exit(1);
		}
		//deque from the queues
		t = 0;
		for (i = 0; i < 10; i++) {
			while (isNotEmpty(queue[i])) {
				arr[t] = deque(queue[i]);
				if (arr[t] == FAIL) {
					printf("Deque fail...\n");
					exit(1);
				}
				t++;
			}
		}

		divisor *= 10;
	}
	for (i = 0; i < 10; i++) terminateQueue(queue[i]);
}

//Quicksort
void quicksort_recur(int arr[], int left, int right) {

	if (left < right) {
		int pivot = arr[left];
		int low = left + 1;
		int high = right;

		while (low <= high) {
			while (low <= right && arr[low] <= pivot) low++;
			while (left <= high && pivot < arr[high]) high--;

			if (low < high) SWAP(arr[low], arr[high]);
		}
		SWAP(arr[left], arr[high]);

		quicksort_recur(arr, left, high - 1);
		quicksort_recur(arr, high + 1, right);
	}
}

void quicksort(int arr[], int n) { quicksort_recur(arr, 0, n - 1); }	//recursively call quick_recur

//Bucket Sort
typedef struct __Node {
	int data;
	struct __Node *next;
}Node;

typedef struct __List {
	Node* head;
}List;

List* createList() {
	List* list = (List*)calloc(1, sizeof(List));	//initialize all field zero
	list->head = (Node*)calloc(1, sizeof(Node));	//Dummy Node
	list->head->data = FAIL;
	return list;
}

void terminateList(List* list) {
	if (list->head == NULL) free(list);
	else {
		Node* cur, *nextnode;
		cur = list->head;
		nextnode = cur->next;
		int i = 1;
		while (nextnode) {
			free(cur);
			cur = nextnode;
			nextnode = nextnode->next;
		}
		free(cur);
		free(list);
	}
}

void append(List* list, int data) {	//append node to bucket in ascending order
	Node* p = list->head;
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	while (p->next != NULL && p->next->data < data) {
		p = p->next;
	}
	newNode->next = p->next;
	p->next = newNode;
}

void bucketsort(int arr[], int n) {
	List* list[10];
	int i;
	int divisor = n / 10;
	for (i = 0; i < 10; i++) list[i] = createList();

	for (i = 0; i < n; i++) append(list[arr[i] / divisor], arr[i]);

	int t = 0;
	Node* cur;
	for (i = 0; i < 10; i++) {
		cur = list[i]->head->next;
		while (cur) {
			arr[t++] = cur->data;
			cur = cur->next;
		}
	}
	printf("\n");

	for (i = 0; i < 10; i++) terminateList(list[i]);
}

int arr_10[10];
int arr_100[100];
int arr_1000[1000];
const void (*func[])(int[], int) = { bubblesort, insertionsort, mergesort, radixsort, quicksort, bucketsort };
const char* sortname[] = { "Bubble Sort", "Insertion Sort", "Merge Sort", "Radix Sort", "Quicksort", "Bucket Sort" };

int main() {
	srand(time(NULL));
	clock_t start, end;
	float total_time;
	int *arr = NULL;

	for (int i = 0; i < 6; i++) {
		printf("---------------------------------------------%s-----------------------------------------------------\n", sortname[i]);
		
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

			//making random numbers
			printf("[Array Size : %d]\n\n", n);
			printf("Before sorting\n{");
			for (int j = 0; j < n; j++) {
				arr[j] = rand() % n;	//values are always smaller than n
				printf("%d, ", arr[j]);
			}
			printf("\b\b}\n\n");

			//sorting start
			start = clock();
			func[i](arr, n);
			end = clock();
			total_time = (float)(end - start);

			printf("After sorting\n{");
			for (int j = 0; j < n; j++) printf("%d, ", arr[j]);
			printf("\b\b}\n\n");
			printf("Total time : %fms\n\n\n", total_time);
		}
	}

	return 0;
}