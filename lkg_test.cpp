#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <malloc.h>
#include <locale.h>
#include <windows.h>
#include <search.h>
#define m 18446744073709551614
#define a 13084467440737175637
#define c 1253

unsigned long long generate_seed()
{
	srand(time(NULL));
	unsigned long long seed = rand();
	return seed;
}

unsigned long long generate(unsigned long long buffer)
{
	return ((a * buffer + c) % m);
}

void printStation(FILE* testfile, unsigned long long number)
{
	switch (number)
	{
	case 0:
		fprintf(testfile, "Девяткино\n");
		break;
	case 1:
		fprintf(testfile, "Гр.Проспект\n");
		break;
	case 2:
		fprintf(testfile, "Академическая\n");
		break;
	case 3:
		fprintf(testfile, "Политехническая\n");
		break;
	case 4:
		fprintf(testfile, "Площадь_мужества\n");
		break;
	case 5:
		fprintf(testfile, "Лесная\n");
		break;
	case 6:
		fprintf(testfile, "Выборгская\n");
		break;
	case 7:
		fprintf(testfile, "Площадь_Ленина\n");
		break;
	case 8:
		fprintf(testfile, "Чернышевская\n");
		break;
	case 9:
		fprintf(testfile, "Площадь_Восстания\n");
		break;
	case 10:
		fprintf(testfile, "Владимирская\n");
		break;
	case 11:
		fprintf(testfile, "Пушкинская\n");
		break;
	case 12:
		fprintf(testfile, "Техн.Институт_1\n");
		break;
	case 13:
		fprintf(testfile, "Балтийская\n");
		break;
	case 14:
		fprintf(testfile, "Нарвская\n");
		break;
	case 15:
		fprintf(testfile, "Кировский_завод\n");
		break;
	case 16:
		fprintf(testfile, "Автово\n");
		break;
	case 17:
		fprintf(testfile, "Ленинский_Проспект\n");
		break;
	case 18:
		fprintf(testfile, "Проспект_Ветеранов\n");
		break;
	case 19:
		fprintf(testfile, "Парнас\n");
		break;
	case 20:
		fprintf(testfile, "Проспект_Просвящения\n");
		break;
	case 21:
		fprintf(testfile, "Озерки\n");
		break;
	case 22:
		fprintf(testfile, "Удельная\n");
		break;
	case 23:
		fprintf(testfile, "Пионерская\n");
		break;
	case 24:
		fprintf(testfile, "Черная_речка\n");
		break;
	case 25:
		fprintf(testfile, "Петроградская\n");
		break;
	case 26:
		fprintf(testfile, "Горьковская\n");
		break;
	case 27:
		fprintf(testfile, "Невский_проспект\n");
		break;
	case 28:
		fprintf(testfile, "Сенная_площадь\n");
		break;
	case 29:
		fprintf(testfile, "Техн.Институт_2\n");
		break;
	case 30:
		fprintf(testfile, "Фрунзенская\n");
		break;
	case 31:
		fprintf(testfile, "Московские_ворота\n");
		break;
	case 32:
		fprintf(testfile, "Электросила\n");
		break;
	case 33:
		fprintf(testfile, "Парк_Победы\n");
		break;
	case 34:
		fprintf(testfile, "Московская\n");
		break;
	case 35:
		fprintf(testfile, "Звездная\n");
		break;
	case 36:
		fprintf(testfile, "Купчино\n");
		break;
	case 37:
		fprintf(testfile, "Беговая\n");
		break;
	case 38:
		fprintf(testfile, "Зенит\n");
		break;
	case 39:
		fprintf(testfile, "Приморская\n");
		break;
	case 40:
		fprintf(testfile, "Василеостровская\n");
		break;
	case 41:
		fprintf(testfile, "Гостиный_двор\n");
		break;
	case 42:
		fprintf(testfile, "Маяковская\n");
		break;
	case 43:
		fprintf(testfile, "Пл.Александра_Невского_1\n");
		break;
	case 44:
		fprintf(testfile, "Елизаровская\n");
		break;
	case 45:
		fprintf(testfile, "Ломоносовская\n");
		break;
	case 46:
		fprintf(testfile, "Пролетарская\n");
		break;
	case 47:
		fprintf(testfile, "Обухово\n");
		break;
	case 48:
		fprintf(testfile, "Рыбацкое\n");
		break;
	case 49:
		fprintf(testfile, "Спасская\n");
		break;
	case 50:
		fprintf(testfile, "Достоевская\n");
		break;
	case 51:
		fprintf(testfile, "Лиговский_проспект\n");
		break;
	case 52:
		fprintf(testfile, "Пл.Александра_Невского_2\n");
		break;
	case 53:
		fprintf(testfile, "Новочеркасская\n");
		break;
	case 54:
		fprintf(testfile, "Ладожская\n");
		break;
	case 55:
		fprintf(testfile, "Проспект_Большевиков\n");
		break;
	case 56:
		fprintf(testfile, "Улица_Дыбенко\n");
		break;
	case 57:
		fprintf(testfile, "Комендантский_проспект\n");
		break;
	case 58:
		fprintf(testfile, "Старая_деревня\n");
		break;
	case 59:
		fprintf(testfile, "Крестовский_остров\n");
		break;
	case 60:
		fprintf(testfile, "Чкаловская\n");
		break;
	case 61:
		fprintf(testfile, "Спортивная\n");
		break;
	case 62:
		fprintf(testfile, "Адмиралтейская\n");
		break;
	case 63:
		fprintf(testfile, "Садовая\n");
		break;
	case 64:
		fprintf(testfile, "Звенигородская\n");
		break;
	case 65:
		fprintf(testfile, "Обводный_канал\n");
		break;
	case 66:
		fprintf(testfile, "Волковская\n");
		break;
	case 67:
		fprintf(testfile, "Бухарестская\n");
		break;
	case 68:
		fprintf(testfile, "Международная\n");
		break;
	case 69:
		fprintf(testfile, "Проспект_Славы\n");
		break;
	case 70:
		fprintf(testfile, "Дунайская\n");
		break;
	case 71:
		fprintf(testfile, "Шушары\n");
		break;
	default:
		fprintf(testfile, "БИНГО! ВЫ НАШЛИ БАГ!!!\n");
		break;
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	unsigned long long N;
	printf("Количество чисел для генерации (x4 для метро; надо 1000 - пиши 4000): ");
	scanf("%llu", &N);
	FILE* testfile = fopen("testfile.txt", "w");

	unsigned long long int buffer = generate_seed();

	unsigned long long* X = (unsigned long long*)calloc(N, sizeof(unsigned long long));
	unsigned long long* NAMEID_FROM = (unsigned long long*)calloc(N, sizeof(unsigned long long));
	unsigned long long* NAMEID_TO = (unsigned long long*)calloc(N, sizeof(unsigned long long));
	unsigned long long* TIME_HOUR = (unsigned long long*)calloc(N, sizeof(unsigned long long));
	unsigned long long* TIME_MINUTE = (unsigned long long*)calloc(N, sizeof(unsigned long long));
	for (int i = 0; i < N; i++)
	{
		buffer = generate(buffer);
		X[i] = buffer;
		if (i % 4 == 0)
		{
			TIME_HOUR[i] = (buffer % 17) + 7;
			//printf("ЧАС: %llu\n", TIME_HOUR[i]);
			//if (TIME_HOUR[i] < 10)!
				//fprintf(testfile, "0");!
			//fprintf(testfile, "%llu,", TIME_HOUR[i]);!
		}
		if (i % 4 == 1)
		{
			TIME_MINUTE[i] = buffer % 60;
			//printf("МИНУТЫ: %llu\n", TIME_MINUTE[i]);
			//if (TIME_MINUTE[i] < 10)!
				//fprintf(testfile, "0");!
			//fprintf(testfile, "%llu\n", TIME_MINUTE[i]);!
		}
		if (i % 4 == 2)
		{
			NAMEID_FROM[i] = buffer % 72;
			//printf("ОТ: %llu\n", NAMEID_FROM[i]);
			printStation(testfile, NAMEID_FROM[i]);
		}
		if (i % 4 == 3)
		{
			NAMEID_TO[i] = buffer % 72;
			//printf("ДО: %llu\n", NAMEID_TO[i]);
			printStation(testfile, NAMEID_TO[i]);
			if (i == N - 1)
				fprintf(testfile, "0");
			else
				fprintf(testfile, "1\n");
		}
	}

	free(X);
	free(NAMEID_FROM);
	free(NAMEID_TO);
	free(TIME_HOUR);
	free(TIME_MINUTE);
	fclose(testfile);
	return 0;
}
