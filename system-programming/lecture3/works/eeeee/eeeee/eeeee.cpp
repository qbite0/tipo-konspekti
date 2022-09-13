#include <stdio.h>
#include <stdlib.h>
//#include <stdafx.h>
#include <omp.h>
#include <time.h>
#include "eeeee.h"
#define SIZE 20
// Функция быстрой сортировки
void quickSort(int* numbers, int left, int right)
{
	int pivot; // разрешающий элемент
	int l_hold = left; //левая граница
	int r_hold = right; // правая граница
	pivot = numbers[left];
	while (left < right) // пока границы не сомкнутся
	{
		while ((numbers[right] >= pivot) && (left < right))
			right--; // сдвигаем правую границу пока элемент [right] больше [pivot]
		if (left != right) // если границы не сомкнулись
		{
			numbers[left] = numbers[right]; // перемещаем элемент [right] на место разрешающего
			left++; // сдвигаем левую границу вправо
		}
		while ((numbers[left] <= pivot) && (left < right))
			left++; // сдвигаем левую границу пока элемент [left] меньше [pivot]
		if (left != right) // если границы не сомкнулись
		{
			numbers[right] = numbers[left]; // перемещаем элемент [left] на место [right]
			right--; // сдвигаем правую границу влево
		}
	}
	numbers[left] = pivot; // ставим разрешающий элемент на место
	pivot = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot) // Рекурсивно вызываем сортировку для левой и правой части массива
		quickSort(numbers, left, pivot - 1);
	if (right > pivot)
		quickSort(numbers, pivot + 1, right);
}
int main()
{
	int a[SIZE];
	// Заполнение массива случайными числами
	for (int i = 0; i < SIZE; i++)
		a[i] = rand() % 201 - 100;
	// Вывод элементов массива до сортировки
	for (int i = 0; i < SIZE; i++)
		printf("%4d ", a[i]);
	printf("\n");
	quickSort(a, 0, SIZE - 1); // вызов функции сортировки
	// Вывод элементов массива после сортировки
	for (int i = 0; i < SIZE; i++)
		printf("%4d ", a[i]);
	printf("\n");
	getchar();
	return 0;
}







int _tmain(int argc, __wchar_t * argv[])
{
	system("cls");
	int* arr = new int[SIZE];
	int* brr = new int[SIZE];
	srand(time(0));
	for (int i = 0; i < SIZE; i++)
	{
		arr[i] = rand() % 10;
		brr[i] = arr[i];
		printf("%d ", arr[i]);
	}
	printf("\n---\n");
	int start, time;
	start = clock();
	printf("\n");
	quickSort(arr, 0, SIZE - 1);
	time = clock() - start;
	for (int i = 0; i < SIZE; i++)
		printf("%d ", arr[i]);
	printf("\n");

	printf("\n---\n");
	int start2, time2;
	start2 = clock();
	quickSort(brr, 0, SIZE - 1);
	time2 = clock() - start2;
	for (int i = 0; i < SIZE; i++)
		printf("%d ", brr[i]);
	printf("\n");
	printf("\n---\n");

	printf("\n No parallel time: %d  milsec\n", time);
	printf("\n Parallel time: %d  milsec\n", time2);
	system("pause");
	delete[]arr;
	delete[]brr;
	return 0;
}