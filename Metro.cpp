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
