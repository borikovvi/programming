#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <windows.h>

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

char** ptr_name_of_statiton;
int** ptr_map_time;
int station_1 = -1, station_2 = -1;
int N = 1;
int rush_hour_mode = 0;
void input() {
    FILE* input;
    input = fopen("input.txt", "r");
    char city[500] = { NULL };
    fgets(city, 500, input);
    while (1) {
        char ch;
        fscanf(input, "%c", &ch);
        if (ch == 10) break;
        if (ch == 32) N++;
    }
    fclose(input);
    input = fopen("input.txt", "r");


    fgets(city, 500, input);
    printf("%s", city);


    char** name_of_statiton = NULL;
    name_of_statiton = (char**)calloc(N, sizeof(char*));
    for (int i = 0; i < N; i++) {
        name_of_statiton[i] = (char*)calloc(30, sizeof(char));
    }

    int i_name = 0, j_name = 0;
    while (1) {
        int x = fgetc(input);
        if (x == 10) break;
        if (x == 32) {
            i_name++;
            j_name = 0;
            continue;
        }
        name_of_statiton[i_name][j_name] = x;
        j_name++;

    }
    ptr_name_of_statiton = name_of_statiton;

    int** map_time = NULL;
    map_time = (int**)calloc(N, sizeof(int*));
    for (int i = 0; i < N; i++) {
        map_time[i] = (int*)calloc(N, sizeof(int));
    }
    ptr_map_time = map_time;


    int g;
    char s[6] = { NULL };
    printf("Укажите время начала Вашей поездки: ");
    fgets(s, 6, stdin);
    getchar();
    double x = atof(s);

    printf("\n");
    if (x >= 0 && x < 6) {
        printf("К сожалению, в указанное Вами время метрополитен закрыт. Попробуйте выбрать другое время для поездки.\n");
        printf("Укажите время начала Вашей поездки: \n");
        fgets(s, 6, stdin);
        getchar();
        double x = atof(s);

    }
    
    if ((x >= 6 && x < 12) || (x >= 18 && x < 24)) {
        rush_hour_mode = 1;
        while (1) {
            fscanf(input, "%d", &g);
            if (g == 777) break;
        }
    }




    int i_map = 0, j_map = 0;
    while (!feof(input)) {
        int z;
        fscanf(input, "%d", &z);
        if (z == 777) break;
        map_time[i_map][j_map] = z;
        j_map++;
        if (fgetc(input) == 10) {
            i_map++;
            j_map = 0;
        }
    }

    fclose(input);
}

void where_go(char** names) {
    char st_1[30] = { NULL };
    char st_2[30] = { NULL };
    printf("Ниже укажите, пожалуйста, две станции.\n");


    while (1) {
        printf("ОТКУДА: ");
        fgets(st_1, 30, stdin);
        for (int i = 29; i >= 0; i--) {
            if (st_1[i] != 0) {
                st_1[i] = 0;
                break;
            }
        }
        int count_st_1 = strlen(st_1);
        for (int i = 0; i < N; i++) {
            if (strcmp(st_1, ptr_name_of_statiton[i]) == 0) station_1 = i;
        }
        if (station_1 == -1) {
            printf("Ошибка! Некорректный ввод! Пожалуйста, введите название станции еще раз.\n");
        }
        else break;
    }
    while (1) {
        printf("КУДА: ");
        fgets(st_2, 30, stdin);
        for (int i = 29; i >= 0; i--) {
            if (st_2[i] != 0) {
                st_2[i] = 0;
                break;
            }
        }
        int count_st_2 = strlen(st_2);
        for (int i = 0; i < N; i++) {
            if (strcmp(st_2, ptr_name_of_statiton[i]) == 0) station_2 = i;
        }
        if (station_2 == -1) {
            printf("Ошибка! Некорректный ввод! Пожалуйста, введите название станции еще раз.\n");
        }
        else break;
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");


    int choice = 1;

    while (choice != 0) {
        input();
        where_go(ptr_name_of_statiton);

        int* d = (int*)calloc(N, sizeof(int));
        int* v = (int*)calloc(N, sizeof(int));
        int temp, minindex, min;
        int begin_index = station_1;

        for (int i = 0; i < N; i++)
        {
            d[i] = 10000;
            v[i] = 1;
        }
        d[begin_index] = 0;
        
        do {
            minindex = 10000;
            min = 10000;
            for (int i = 0; i < N; i++)
            {
                if ((v[i] == 1) && (d[i] < min))
                {
                    min = d[i];
                    minindex = i;
                }
            }

            if (minindex != 10000)
            {
                for (int i = 0; i < N; i++)
                {
                    if (ptr_map_time[minindex][i] > 0)
                    {
                        temp = min + ptr_map_time[minindex][i];
                        if (temp < d[i])
                        {
                            d[i] = temp;
                        }
                    }
                }
                v[minindex] = 0;
            }
        } while (minindex < 10000);

        int* ver = (int*)calloc(N, sizeof(int));
        int end = station_2;
        ver[0] = end;
        int k = 1;
        int weight = d[end];

        while (end != begin_index)
        {
            for (int i = 0; i < N; i++)
                if (ptr_map_time[i][end] != 0)
                {
                    int temp = weight - ptr_map_time[i][end];
                    if (temp == d[i])
                    { 
                        weight = temp;
                        end = i;
                        ver[k] = i;
                        k++;
                    }
                }
        }
        
        printf("\nВывод кратчайшего пути:\n");
        for (int n = k - 1; n >= 0; n--) {
            if (rush_hour_mode)
                printf("%3d мин", (3 + d[ver[n]]));
            else
                printf("%3d мин", (4 + d[ver[n]]));
            printf(" -> %s\n", ptr_name_of_statiton[ver[n]]);
        }
        
        int tmp_res = 0;
        if (d[station_2] < 60)
            if (rush_hour_mode) printf("Время Вашего пути составит: %d мин\n", d[station_2] + 3 + 2);
            else printf("Время Вашего пути составит: %d мин\n", d[station_2] + 4 + 2);
        else
        {
            if (rush_hour_mode) tmp_res = d[station_2] + 3 + 2;
            else tmp_res = d[station_2] + 4 + 2;
            int hour = tmp_res / 60;
            tmp_res = tmp_res % 60;
            if (tmp_res == 0)
                printf("Время Вашего пути составит: %d ч\n", hour);
            else
                printf("Время Вашего пути составит: %d ч %d мин\n", hour, tmp_res);
        }

        free(d);
        free(v);
        free(ver);

        printf("\nМЕНЮ. Введите, пожалуйста:\n"
            "ЛЮБОЕ ЧИСЛО - продолжить работу\n"
            "      0     - завершить работу\n");
        printf("Действие: ");
        scanf("%d", &choice);
        getchar();

        free(ptr_map_time);
        free(ptr_name_of_statiton);
    }
    return 0;
}
