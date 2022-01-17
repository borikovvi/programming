#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <locale.h>
#include <Windows.h>
#define mcontrol 777 //you are genius
char** ptr_name_of_statiton;// указатель на матрицу name_of_statiton
int** ptr_map_time;// указатель на матрицу map_time
int station_1 = -1, station_2 = -1;
int N = 1;
int input() {
    FILE* input;
    input = fopen("input.txt", "r");
    char city[500] = { NULL }; // выводим какую-то фразу в начале
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
    }// выделяем память под матрицу Nx30, храним назваиния станций, каждая строка матрицы это название станции

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

    }// заполняем матрицу с названиями станций
    ptr_name_of_statiton = name_of_statiton;


    //for (int i = 0; i <= 71; i++) {
    //    for (int j = 0; j < 30; j++) {
    //        //if (map_time[i][j] == 0) break;
    //        printf("%c", name_of_statiton[i][j]);
    //    }
    //    printf("\n");
    //}// выводим названия станций в консоль


    int** map_time = NULL;// это матрица со станциями
    map_time = (int**)calloc(N, sizeof(int*));
    for (int i = 0; i < N; i++) {
        map_time[i] = (int*)calloc(N, sizeof(int));
    }// выделяем память под матрицу NxN
    ptr_map_time = map_time;


    int g;
    char s[6] = { NULL };
    printf("Укажите время начала Вашей поездки: ");
    fgets(s, 6, stdin);
    getchar();
    double x = atof(s);
    char rush_hour = 0;

    printf("\n");
    if (x >= 0 && x < 6) {
        printf("К сожалению, в указанное Вами время метрополитен закрыт. Попробуйте выбрать другое время для поездки.\n");
        printf("Укажите время начала Вашей поездки: \n");
        fgets(s, 6, stdin);
        getchar();
        double x = atof(s);

    }
    if ((x >= 6 && x < 12) || (x >= 18 && x < 24)) {
        while (1) {
            fscanf(input, "%d", &g);
            if (g == mcontrol) break;
            rush_hour = 1;
        }
        //for (int i = 0; i < N*N; i++) fscanf(input, "%d", &g);
    }




    int i_map = 0, j_map = 0; // переменные для матрицы
    while (!feof(input)) {
        int z;
        fscanf(input, "%d", &z);
        if (z == mcontrol) break;
        map_time[i_map][j_map] = z;
        j_map++;
        if (fgetc(input) == 10) {
            i_map++;
            j_map = 0;
        }
    }// считываем матрицу из файла
    //for (int i = 0; i < N*N; i++) {
    //    int z;
    //    fscanf(input, "%d", &z);
    //    map_time[i_map][j_map] = z;
    //        j_map++;
    //        if (fgetc(input) == 10) {
    //            i_map++;
    //            j_map = 0;
    //        }

    //}// считываем матрицу из файла

    fclose(input);

    //for (int i = 0; i <= 71; i++) {
    //    for (int j = 0; j <= 71; j++) {
    //        //if (map_time[i][j] == 0) break;
    //        printf("%d ", map_time[i][j]);
    //    }
    //    printf("\n");
    //}// выводим матрицу на экран
    return rush_hour;
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


    /*printf("%d\n", station_1);
    printf("%d\n", station_2);*/
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");


    int choice = 1;

    while (choice != 0) {
        int rush_hour_mode = input();
        where_go(ptr_name_of_statiton);

        int* d = (int*)calloc(N, sizeof(int)); // минимальное расстояние
        int* v = (int*)calloc(N, sizeof(int)); // посещенные вершины
        int temp, minindex, min;
        int begin_index = station_1;
        //system("chcp 1251");
        //system("cls");

        //Инициализация вершин и расстояний
        for (int i = 0; i < N; i++)
        {
            d[i] = 10000;
            v[i] = 1;// значит что еще не обошли
        }
        d[begin_index] = 0;
        // Шаг алгоритма
        do {
            minindex = 10000;
            min = 10000;
            for (int i = 0; i < N; i++)
            { // Если вершину ещё не обошли и вес меньше min
                if ((v[i] == 1) && (d[i] < min))
                { // Переприсваиваем значения
                    min = d[i];
                    minindex = i;// номер вершины, у которой наименьшая длина пути (индекс)
                }
            }
            // Добавляем найденный минимальный вес
            // к текущему весу вершины
            // и сравниваем с текущим минимальным весом вершины
            if (minindex != 10000)// т.е. если мы нашли вершину, с минимальным индексом
            {
                for (int i = 0; i < N; i++)
                {
                    if (ptr_map_time[minindex][i] > 0)//если есть прямой путь от данной вершины к другой вершине
                    {
                        temp = min + ptr_map_time[minindex][i];// в первом случае это 0 + длина пути из таблицы до новой вершины
                        if (temp < d[i])
                        {
                            d[i] = temp;
                        }
                    }
                }
                v[minindex] = 0;// мы прошли эту вершину
            }
        } while (minindex < 10000);
        // Вывод кратчайших расстояний до вершин
        /*printf("\nКратчайшие расстояния до вершин: \n");
        for (int i = 0; i < N; i++)
            printf("%5d ", d[i]);*/

            // Восстановление пути
        int* ver = (int*)calloc(N, sizeof(int)); // массив посещенных вершин
        int end = station_2; // индекс конечной вершины = 5 - 1
        ver[0] = end /*+ 1*/; // начальный элемент - конечная вершина
        int k = 1; // индекс предыдущей вершины
        int weight = d[end]; // вес конечной вершины

        while (end != begin_index) // пока не дошли до начальной вершины
        {
            for (int i = 0; i < N; i++) // просматриваем все вершины
                if (ptr_map_time[i][end] != 0)   // если связь есть
                {
                    int temp = weight - ptr_map_time[i][end]; // определяем вес пути из предыдущей вершины
                    if (temp == d[i]) // если вес совпал с рассчитанным, значит из этой вершины и был переход
                    {                 // 
                        weight = temp; // сохраняем новый вес
                        end = i;       // сохраняем предыдущую вершину
                        ver[k] = i /*+ 1*/; // и записываем ее в массив
                        k++;
                    }
                }
        }
        // Вывод пути (начальная вершина оказалась в конце массива из k элементов)
        printf("\nВывод кратчайшего пути:\n");
        for (int n = k - 1; n >= 0; n--) {
            if (rush_hour_mode)
                printf("%3d мин", (3 + d[ver[n]])); // час-пик
            else
                printf("%3d мин", (4 + d[ver[n]])); // стандарт
            printf(" -> %s\n", ptr_name_of_statiton[ver[n]]);
        }
        /*printf("\n");
        printf("Ваше время в пути составит: %d минут.\n", d[station_2]);*/
        int tmp_res = 0;
        if (d[station_2] < 60)
            printf("Время Вашего пути составит: %d мин\n", d[station_2]);
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

        //getchar();
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
