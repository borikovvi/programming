#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <windows.h>

const char* stations[] = { "Девяткино", "Гр.Проспект", "Академическая", "Политехническая", "Площадь мужества", "Лесная", "Выборгская", "Площадь Ленина", "Чернышевская", "Площадь Восстания", "Владимирская", "Пушкинская", "Техн.Институт 1", "Балтийская", "Нарвская", "Кировский завод", "Автово", "Ленинский роспект", "Проспект Ветеранов", "Парнас", "Проспект Просвящения", "Озерки", "Удельная", "Пионерская", "Черная речка", "Петроградская", "Горьковская", "Невский проспект", "Сенная площадь", "Техн.Институт 2", "Фрунзенская", "Московские ворота", "Электросила", "Парк Победы", "Московская", "Звездная", "Купчино", "Беговая", "Зенит", "Приморская", "Василеостровская", "Гостиный двор", "Маяковская", "Пл.Александра Невского 1", "Елизаровская", "Ломоносовская", "Пролетарская", "Обухово", "Рыбацкое", "Спасская", "Достоевская", "Лиговский проспект", "Пл.Александра Невского 2", "Новочеркасская", "Ладожская", "Проспект Большевиков", "Улица Дыбенко", "Комендантский проспект", "Старая деревня", "Крестовский остров", "Чкаловская", "Спортивная", "Адмиралтейская", "Садовая", "Звенигородская", "Обводный канал", "Волковская", "Бухарестская", "Международная", "Проспект Славы", "Дунайская", "Шушары" };

char* gets(char* s)
{
	fflush(stdin);

	int i, k = getchar();

	if (k == EOF)
		return NULL;

	for (i = 0; k != EOF && k != '\n'; ++i) {
		s[i] = k;
		k = getchar();

		if (k == EOF && !feof(stdin))
			return NULL;
	}

	s[i] = '\0';

	return s;
}

int getStationIndex(char* station)
{
	for (int i = 0; i < 72; i++)
	{
		if (!strcmp(stations[i], station))
		{
			return i;
		}
	}
	return -1;
}
struct AdjListNode
{
	int dest;
	int weight;
	struct AdjListNode* next;
};

struct AdjList
{
	struct AdjListNode* head;
};

struct Graph
{
	int V;
	struct AdjList* array;
};

struct AdjListNode* newAdjListNode(
	int dest, int weight)
{
	struct AdjListNode* newNode =
		(struct AdjListNode*)
		malloc(sizeof(struct AdjListNode));
	newNode->dest = dest;
	newNode->weight = weight;
	newNode->next = NULL;
	return newNode;
}

struct Graph* createGraph(int V)
{
	struct Graph* graph = (struct Graph*)
		malloc(sizeof(struct Graph));
	graph->V = V;

	graph->array = (struct AdjList*)
		malloc(V * sizeof(struct AdjList));

	for (int i = 0; i < V; ++i)
		graph->array[i].head = NULL;

	return graph;
}

void addEdge(struct Graph* graph, int src,
	int dest, int weight)
{
	struct AdjListNode* newNode =
		newAdjListNode(dest, weight);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;

	newNode = newAdjListNode(src, weight);
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;
}

struct MinHeapNode
{
	int v;
	int dist;
};

struct MinHeap
{
	int size;
	int capacity;
	int* pos;
	struct MinHeapNode** array;
};

struct MinHeapNode* newMinHeapNode(int v,
	int dist)
{
	struct MinHeapNode* minHeapNode =
		(struct MinHeapNode*)
		malloc(sizeof(struct MinHeapNode));
	minHeapNode->v = v;
	minHeapNode->dist = dist;
	return minHeapNode;
}

struct MinHeap* createMinHeap(int capacity)
{
	struct MinHeap* minHeap =
		(struct MinHeap*)
		malloc(sizeof(struct MinHeap));
	minHeap->pos = (int*)malloc(
		capacity * sizeof(int));
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->array =
		(struct MinHeapNode**)
		malloc(capacity *
			sizeof(struct MinHeapNode*));
	return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a,
	struct MinHeapNode** b)
{
	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

void minHeapify(struct MinHeap* minHeap,
	int idx)
{
	int smallest, left, right;
	smallest = idx;
	left = 2 * idx + 1;
	right = 2 * idx + 2;

	if (left < minHeap->size &&
		minHeap->array[left]->dist <
		minHeap->array[smallest]->dist)
		smallest = left;

	if (right < minHeap->size &&
		minHeap->array[right]->dist <
		minHeap->array[smallest]->dist)
		smallest = right;

	if (smallest != idx)
	{
		MinHeapNode* smallestNode =
			minHeap->array[smallest];
		MinHeapNode* idxNode =
			minHeap->array[idx];

		minHeap->pos[smallestNode->v] = idx;
		minHeap->pos[idxNode->v] = smallest;

		swapMinHeapNode(&minHeap->array[smallest],
			&minHeap->array[idx]);

		minHeapify(minHeap, smallest);
	}
}

int isEmpty(struct MinHeap* minHeap)
{
	return minHeap->size == 0;
}

struct MinHeapNode* extractMin(struct MinHeap*
	minHeap)
{
	if (isEmpty(minHeap))
		return NULL;

	struct MinHeapNode* root =
		minHeap->array[0];

	struct MinHeapNode* lastNode =
		minHeap->array[minHeap->size - 1];
	minHeap->array[0] = lastNode;

	minHeap->pos[root->v] = minHeap->size - 1;
	minHeap->pos[lastNode->v] = 0;

	--minHeap->size;
	minHeapify(minHeap, 0);

	return root;
}

void decreaseKey(struct MinHeap* minHeap,
	int v, int dist)
{
	int i = minHeap->pos[v];

	minHeap->array[i]->dist = dist;

	while (i && minHeap->array[i]->dist <
		minHeap->array[(i - 1) / 2]->dist)
	{
		minHeap->pos[minHeap->array[i]->v] =
			(i - 1) / 2;
		minHeap->pos[minHeap->array[
			(i - 1) / 2]->v] = i;
		swapMinHeapNode(&minHeap->array[i],
			&minHeap->array[(i - 1) / 2]);

		i = (i - 1) / 2;
	}
}

bool isInMinHeap(struct MinHeap* minHeap, int v)
{
	if (minHeap->pos[v] < minHeap->size)
		return true;
	return false;
}

void dijkstra(struct Graph* graph, int src, int dest)
{
	int V = graph->V;

	int* dist = (int*)malloc(V * sizeof(int));

	struct MinHeap* minHeap = createMinHeap(V);

	for (int v = 0; v < V; ++v)
	{
		dist[v] = INT_MAX;
		minHeap->array[v] = newMinHeapNode(v,
			dist[v]);
		minHeap->pos[v] = v;
	}

	minHeap->array[src] =
		newMinHeapNode(src, dist[src]);
	minHeap->pos[src] = src;
	dist[src] = 0;
	decreaseKey(minHeap, src, dist[src]);

	minHeap->size = V;

	int way[100][3];
	int size = 0;

	while (!isEmpty(minHeap))
	{
		struct MinHeapNode* minHeapNode =
			extractMin(minHeap);

		int u = minHeapNode->v;

		struct AdjListNode* pCrawl =
			graph->array[u].head;
		while (pCrawl != NULL)
		{
			int v = pCrawl->dest;

			if (isInMinHeap(minHeap, v) &&
				dist[u] != INT_MAX &&
				pCrawl->weight + dist[u] < dist[v])
			{
				dist[v] = dist[u] + pCrawl->weight;
				way[size][0] = u;
				way[size][1] = v;
				way[size][2] = dist[v];
				size++;
				decreaseKey(minHeap, v, dist[v]);
			}
			pCrawl = pCrawl->next;
		}
	}

	printf("\nВывод кратчайшего пути:\n");
	int i = size - 1;
	bool last = false;
	int minutes = 0;
	while (i >= 0)
	{
		if (way[i][1] == dest)
		{
			printf("%4d мин -> %s\n", way[i][2], stations[way[i][1]]);
			if (!last)
			{
				last = true;
				minutes = way[i][2];
			}
			dest = way[i][0];
		}
		i--;
	}
	printf("Время вашего пути составит: %d мин\n", minutes);
}


int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	int V = 72;
	struct Graph* graph = createGraph(V);
	addEdge(graph, 0, 1, 4);
	addEdge(graph, 1, 2, 4);
	addEdge(graph, 2, 3, 2);
	addEdge(graph, 3, 4, 2);
	addEdge(graph, 4, 5, 3);
	addEdge(graph, 5, 6, 3);
	addEdge(graph, 6, 7, 3);
	addEdge(graph, 7, 8, 3);
	addEdge(graph, 8, 9, 3);
	addEdge(graph, 9, 10, 2);
	addEdge(graph, 9, 42, 5);
	addEdge(graph, 10, 11, 2);
	addEdge(graph, 10, 50, 5);
	addEdge(graph, 11, 12, 4);
	addEdge(graph, 11, 64, 5);
	addEdge(graph, 12, 13, 2);
	addEdge(graph, 12, 29, 4);
	addEdge(graph, 13, 14, 3);
	addEdge(graph, 14, 15, 4);
	addEdge(graph, 15, 16, 2);
	addEdge(graph, 16, 17, 3);
	addEdge(graph, 17, 18, 2);
	addEdge(graph, 19, 20, 3);
	addEdge(graph, 20, 21, 2);
	addEdge(graph, 21, 22, 3);
	addEdge(graph, 22, 23, 3);
	addEdge(graph, 23, 24, 3);
	addEdge(graph, 24, 25, 4);
	addEdge(graph, 25, 26, 2);
	addEdge(graph, 26, 27, 4);
	addEdge(graph, 27, 28, 2);
	addEdge(graph, 27, 41, 6);
	addEdge(graph, 28, 29, 2);
	addEdge(graph, 28, 49, 6);
	addEdge(graph, 28, 63, 6);
	addEdge(graph, 29, 30, 2);
	addEdge(graph, 30, 31, 3);
	addEdge(graph, 31, 32, 2);
	addEdge(graph, 32, 33, 2);
	addEdge(graph, 33, 34, 3);
	addEdge(graph, 34, 35, 5);
	addEdge(graph, 35, 36, 3);
	addEdge(graph, 37, 38, 4);
	addEdge(graph, 38, 39, 4);
	addEdge(graph, 39, 40, 4);
	addEdge(graph, 40, 41, 4);
	addEdge(graph, 41, 42, 3);
	addEdge(graph, 42, 43, 3);
	addEdge(graph, 43, 44, 4);
	addEdge(graph, 43, 52, 5);
	addEdge(graph, 44, 45, 3);
	addEdge(graph, 45, 46, 4);
	addEdge(graph, 46, 47, 3);
	addEdge(graph, 47, 48, 4);
	addEdge(graph, 49, 50, 4);
	addEdge(graph, 49, 63, 5);
	addEdge(graph, 50, 51, 2);
	addEdge(graph, 51, 52, 2);
	addEdge(graph, 52, 53, 3);
	addEdge(graph, 53, 54, 3);
	addEdge(graph, 54, 55, 3);
	addEdge(graph, 55, 56, 3);
	addEdge(graph, 57, 58, 4);
	addEdge(graph, 58, 59, 3);
	addEdge(graph, 59, 60, 3);
	addEdge(graph, 60, 61, 2);
	addEdge(graph, 61, 62, 3);
	addEdge(graph, 62, 63, 2);
	addEdge(graph, 63, 64, 3);
	addEdge(graph, 64, 65, 3);
	addEdge(graph, 65, 66, 3);
	addEdge(graph, 66, 67, 3);
	addEdge(graph, 67, 68, 3);
	addEdge(graph, 68, 69, 2);
	addEdge(graph, 69, 70, 3);
	addEdge(graph, 70, 71, 3);

	int menu = 1;
	char from[30], to[30];
	while (menu != 0)
	{
		system("cls");
		printf("Ниже укажите пожалуйста две станции\n");
		printf("ОТКУДА: ");
		gets(from);
		printf("КУДА: ");
		gets(to);
		dijkstra(graph, getStationIndex(from), getStationIndex(to));
		printf("\nМЕНЮ. Введите, пожалуйста:\n");
		printf("ЛЮБОЕ ЧИСЛО - продолжить работу\n");
		printf("     0      - завершить работу\n");
		printf("Действие: ");
		scanf("%d", &menu);
		fseek(stdin, 0, SEEK_END);
	}

	system("pause");
	return 0;
}
