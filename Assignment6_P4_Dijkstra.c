#include <stdio.h>
#include <stdlib.h>
#define INF 0x7FFFFFFC
typedef enum {false, true} bool;
typedef enum {s, t, x, y, z} vertex;
char name[] = { 's', 't', 'x', 'y', 'z' };

int length[5][5];
int distance[5];
bool found[5];
vertex prede[5];

void initial() {
	for (int i = 0; i < 5; i++) {
		distance[i] = INF;
		found[i] = false;
		for (int j = 0; j < 5; j++) if (i != j) length[i][j] = INF;
	}
	length[s][t] = 3;
	length[s][y] = 5;
	length[t][y] = 2;
	length[t][x] = 6;
	length[y][t] = 1;
	length[y][z] = 6;
	length[y][x] = 4;
	length[x][z] = 2;
	length[z][s] = 3;
	length[z][x] = 7;
}

void short_way(vertex dest) {
	if (prede[dest] != s) short_way(prede[dest]);
	printf("%c->", name[prede[dest]]);
}

int main() {

	initial();

	found[s] = true;
	distance[s] = length[s][s];
	int min, new;

	for (int i = 0; i < 4; i++) {
		
		//choose closest vertex
		new = 0;
		min = INF;
		for (int j = 0; j < 5; j++) {
			if (!found[j] && distance[j] < min) {
				new = j;
				min = distance[i];
			}
		}
		found[new] = true;
		
		//update new distance
		for (int to = 0; to < 5; to++) {
			if (!found[to]) {	
				if (distance[new] + length[new][to] < distance[to]) {
					distance[to] = distance[new] + length[new][to];
					prede[to] = new;
				}
			}
		}
	}

	printf("Shortest path to vertex y : ");
	short_way(y);	printf("y\n");
	printf("Total cost : %d\n\n", distance[y]);

	printf("Shortest path to vertex z : ");
	short_way(z);	printf("z\n");
	printf("Total cost : %d\n\n", distance[z]);

	return 0;
}