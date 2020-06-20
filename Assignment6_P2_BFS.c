#include <stdio.h>
#include <stdlib.h>
#define DEQUEFAIL -1
typedef enum { false, true } bool;
typedef enum { s, t, u, v, w, x, y, r } vertex;
char vertex_name[8] = { 's', 't', 'u', 'v', 'w', 'x', 'y', 'r' };

typedef struct __Queue {
	int max;
	int num;
	int	head;
	int tail;
	int* data;
}Queue;

Queue* createQue(int size) {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->num = 0;
	queue->max = size;
	queue->head = 0;
	queue->tail = 0;
	queue->data = (int*)malloc(sizeof(int) * size);
	return queue;
}

bool enque(Queue* queue, vertex ele) {
	if (queue->num < queue->max) {
		queue->data[queue->head] = ele;
		queue->head = (queue->head + 1) % queue->max;
		queue->num++;
		return true;
	}
	else return false;
}

vertex deque(Queue* queue) {
	if (0 < queue->num) {
		int result = queue->data[queue->tail];
		queue->tail = (queue->tail + 1) % queue->max;
		queue->num--;
		return result;
	}
	else return DEQUEFAIL;
}

bool isNotEmpty(Queue* queue) {
	return queue->num ? true : false;
}

void terminateQueue(Queue* queue) {
	free(queue->data);
	free(queue);
}


bool connected[8][8];
bool visit[8];//visit[i] means vertex[i] has been visit
int dist[8];	//dist[i] means distance 0 to i
vertex pie[8];	//pie[i] returns i's predecessor number

int main(void) {

	connected[s][r] = true;
	connected[r][s] = true;
	connected[s][w] = true;
	connected[w][s] = true;
	connected[r][v] = true;
	connected[v][r] = true;
	connected[t][w] = true;
	connected[w][t] = true;
	connected[w][x] = true;
	connected[x][w] = true;
	connected[t][u] = true;
	connected[u][t] = true;
	connected[x][y] = true;
	connected[y][x] = true;
	connected[u][x] = true;
	connected[x][u] = true;
	connected[u][y] = true;
	connected[y][u] = true;

	Queue* queue = createQue(8);
	visit[s] = true;
	dist[s] = 0;
	enque(queue, s);

	while (isNotEmpty(queue)) {
		vertex cur = deque(queue);
		printf("[Vertex %c]\n", vertex_name[cur]);
		printf("d = %d\n", dist[cur]);
		if(cur != s) printf("Predecessor Vertex = %c\n", vertex_name[pie[cur]]);	//No Predecessor for starting vertex s
		puts("");
		for (vertex i = s; i <= r; i++) {
			if (connected[cur][i] && !visit[i]) {
				visit[i] = true;	//visit vertex i
				dist[i] = dist[cur] + 1;	//distance i = (distance from vertex s to cur) + 1
				pie[i] = cur;	//vertex i's predecessor is vertex cur
				enque(queue, i);
			}
		}
	}

	return 0;
}