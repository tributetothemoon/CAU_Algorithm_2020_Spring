#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int num;
	int weight;
	int value;
}Item;

Item* create_item(int num, int weight, int value) {
	Item* new = (Item*)malloc(sizeof(Item));
	new->num = num;
	new->weight = weight;
	new->value = value;
	return new;
}

//compare function for sorting
int compare(const void* _a, const void* _b) {
	Item* a = *(Item**)_a;
	Item* b = *(Item**)_b;

	int unit_value_a = (a->value) / (a->weight);
	int unit_value_b = (b->value) / (b->weight);

	return unit_value_b - unit_value_a;
}

int total_value;
void c(int index, int bag_size, Item* arr[], int arr_size) {

	if (arr[index]->weight <= bag_size) {
		printf("Item %d\n", arr[index]->num);
		printf("Weight : %d\n", arr[index]->weight);
		printf("Value : %d\n", arr[index]->value);
		printf("Fractional number : %d/%d\n\n", 1, 1);
		total_value += arr[index]->value;
		
		if (index < arr_size) c(index + 1, bag_size - arr[index]->weight, arr, arr_size);	//recursively call
		else return;	//index out of range
	}
	else {	//when item needs to be broken up
		printf("Item %d(fractionized)\n", arr[index]->num);
		printf("Weight : %d\n", bag_size);
		printf("Value : %d\n", (arr[index]->value) / (arr[index]->weight) * bag_size);
		printf("Fractional number : %d/%d\n\n", bag_size, arr[index]->weight);
		total_value += (arr[index]->value) / (arr[index]->weight) * bag_size;
		return;
	}
}

void fractional_knapsack(Item* arr[], int arr_size, int bag_size) {

	printf("[Sorting]\n");
	printf("Sort items in decreasing order...\n\n");
	qsort(arr, arr_size, sizeof(Item*), compare);	//sort in decreasing order

	for (int i = 0; i < arr_size; i++) {
		printf("Item %d, value per unit is %d\n", arr[i]->num, (arr[i]->value) / (arr[i]->weight));
	}

	printf("\n[Fractional Knapsack Problem]\n");
	printf("List of items in the bag...\n\n");

	c(0, bag_size, arr, arr_size);
	
	printf("Total value of items in the bag : %d\n", total_value);
}

int main(void) {

	Item* arr[6];	
	arr[0] = create_item(1, 6, 60);
	arr[1] = create_item(2, 10, 20);
	arr[2] = create_item(3, 3, 12);
	arr[3] = create_item(4, 5, 80);
	arr[4] = create_item(5, 1, 30);
	arr[5] = create_item(6, 3, 60);

	fractional_knapsack(arr, 6, 16);

	for (int i = 0; i < 6; i++) free(arr[i]);

	return 0;
}