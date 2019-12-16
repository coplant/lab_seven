#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <conio.h>
#include <stdio.h>
#include <clocale>
#include <crtdbg.h>
#include <memory.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <windows.h>;
#include < string.h >
using namespace std;

char** toArr(char** string, int& count, char* token)
{
	char** tmpArr = new char* [count + 1];
	for (int i = 0; i < count; i++)
	{
		tmpArr[i] = string[i];
	}
	tmpArr[count] = token;
	count++;
	delete[] string;
	string = tmpArr;
	return string;
};

char* readStr(FILE* from)
{
	char* str = nullptr;
	char tmpCh = ' ';
	int strlen = 0;
	do
	{
		fscanf(from, "%c", &tmpCh);
		char* tmpStr = new char[strlen + 1];
		for (int i = 0; i < strlen; i++)
		{
			tmpStr[i] = str[i];
		}
		tmpStr[strlen] = tmpCh;
		strlen++;
		delete[] str;
		str = tmpStr;
	} while (tmpCh != '\n' && !feof(from));

	str[strlen - 1] = '\0';
	return str;
}

char** readFromFile(int& size, char* filename, bool& found)
{
	char** readIns = nullptr;
	char** read = nullptr;
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Файл не найден!\n");
		found = 0;
		return 0;
	}
	else if
		(fgetc(file) == EOF)
	{
		printf("Файл пуст!");
		found = 0;
		return 0;
		fclose(file);
	}
	else
	{
		printf("Файл найден!\n");
		file = fopen(filename, "a+");
		while (!feof(file))
		{
			read = toArr(readIns, size, readStr(file));
			readIns = read;
		}
		fclose(file);
		return read;
	}
}

char* strFill()
{
	int len = 1;
	char* tmpStr = NULL;
	char* resultStr = new char[len];
	while (true)
	{

		resultStr[len - 1] = _getch();
		if (resultStr[0] == '\b')
			continue;
		if (resultStr[len - 1] == '\0')
		{
			continue;
		}
		if (resultStr[len - 1] == 13)
		{
			resultStr[len - 1] = '\0';
			break;
		}
		if (resultStr[len - 1] == '\b')
		{
			printf("%c", resultStr[len - 1]);
			printf("%c", ' ');
			printf("%c", resultStr[len - 1]);
			tmpStr = new char[len - 1];
			for (int i = 0; i < len - 2; i++)
			{
				tmpStr[i] = resultStr[i];
			}
			delete[] resultStr;
			resultStr = tmpStr;
			len--;
		}
		else
		{
			printf("%c", resultStr[len - 1]);
			tmpStr = new char[len + 1];
			for (int i = 0; i < len; i++)
			{
				tmpStr[i] = resultStr[i];
			}
			delete[] resultStr;
			resultStr = tmpStr;
			len++;
		}
	}
	return resultStr;
};

void printArr(char** arr, int count, int* vowelsCount)
{
	for (int i = 0; i < count; i++)
		printf(" %s = %d\n", arr[i], vowelsCount[i]);
};

void printArr(char** name, int count)
{
	for (int i = 0; i < count; i++)
		printf("%s\n", name[i]);
};

void freeArr(char** arr, int count)
{
	for (int i = 0; i < count; i++)
	{
		delete[] arr[i];
	}
	delete arr;
};

void swap(char*& left, char*& right)
{
	char* _temp;
	_temp = left;
	left = right;
	right = _temp;
}

int* vowelsArr(char** arr, int count)
{
	char arrVowels[] = { 'A', 'a', 'E', 'e', 'I', 'i', 'U', 'u', 'O', 'o', 'Y', 'y' };
	int* vowelsCount = new int[count];
	for (int i = 0; i < count; i++)
	{
		vowelsCount[i] = 0;
	}
	for (int i = 0; i < count; i++)
		for (int j = 0; j < strlen(arr[i]); j++)
		{
			for (int z = 0; z < sizeof(arrVowels); z++)
				if (arr[i][j] == arrVowels[z])
					vowelsCount[i]++;
		};

	return vowelsCount;
};

void sortArr(char** arr, int count)
{
	int* vowelsCount = new int[count];
	vowelsCount = vowelsArr(arr, count);
	printf("Выберите вариант сортировки:  \n1 - По алфавиту\n2 - По количеству гласных букв в слове\n3 - Верунться назад\n\n");
	int choice = 0;
	scanf("%d", &choice);
	if (choice == 3)
	{
		return;
	}
	else if (choice == 1)
	{
		for (int i = 0; i < count; i++)
		{
			for (int j = count - 1; j > i; j--)
			{
				if (strcmp(arr[j], arr[j - 1]) < 0)
				{
					swap(arr[j], arr[j - 1]);
				}
			}
		}
		printf("\nСписок успешно отсортирован!\n");
		printArr(arr, count);
	}
	else if (choice == 2)
	{
		for (int i = 0; i < count; i++)
		{
			for (int j = count - 1; j > i; j--)
			{
				if (vowelsCount[j] < vowelsCount[j - 1])
				{
					swap(arr[j], arr[j - 1]);
					swap(vowelsCount[j], vowelsCount[j - 1]);
				}
			}
		}
		printf("\nСписок успешно отсортирован!\n");
		printArr(arr, count, vowelsCount);
	};
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int menu = 0;
	bool isClear = 1;
	int namesCount = 0;
	char** names = nullptr;
	char* filename = nullptr;
	bool found = 1;
	while (true)
	{

		printf("\n---Выберите желаемое действие--- \n 1. Чтение данных из файла\n 2. Обработка информации\n 3. Вывод на экран без сортировки\n 4. Выход из программы \n\n");
		scanf("%d", &menu);
		switch (menu)
		{
		case 1: // Чтение из файла
			printf("\nЧтение данных:\n--------------------------------\n");
			printf("Введите путь к  файлу:\n");
			filename = strFill();
			printf("\n");
			if (isClear)
			{
				names = readFromFile(namesCount, filename, found);
				if (found)
				{
					printf("Информация успешно загружена!\n");
					isClear = 0;
				};
			}
			else
			{
				freeArr(names, namesCount);
				names = nullptr;
				namesCount = 0;
				names = readFromFile(namesCount, filename, found);
				if (found)
				{
					printf("Информация успешно загружена!\n");
					isClear = 0;
				};
			};
			break;
		case 2: // Сортировка
			if (isClear)
			{
				printf("\nДля начала выберите файл!");
			}
			else
			{
				printf("\nСортировка:\n--------------------------------\n");
				sortArr(names, namesCount);
			};
			break;
		case 3: // Вывод на экран
			if (isClear)
			{
				printf("\nДля начала выберите файл!");
			}
			else
			{
				printf("\nВывод на экран без сортировки:\n--------------------------------\n");
				printArr(names, namesCount);
			};
			break;

		case 4: // Выход
			freeArr(names, namesCount);
			printf("\nВы успешно завершили работу программы.");
			return(0);
			break;
		default:
			printf("\nТакой функции не существует.");
			break;
		};
	}
	return 0;
}
