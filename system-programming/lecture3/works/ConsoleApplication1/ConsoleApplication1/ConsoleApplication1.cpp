#include <iostream>
#include <stdio.h>
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>

pthread_mutex_t mutex; //двоичный семафор
int A[3][3] = {
	1, -2, 0,
	4, 6, 2,
	-3, 4, -2
};
int B[3][3] = {
	0, 2, 0,
	1, 1, 1,
	5, -3, 10
};
int C[3][3]; //результирующая матрица
struct result { //структура очереди
	char str[100]; //для записи результата вычислений
	result* next; //указатель на следующий элемент
};
result* head; //указатель на первый элемент очереди
result* newrez; //указатель элементов очереди
result* rez; //указатель на последний элемент очереди

//стартовая функция для дочерних потоков
void* func(void* param) {
	//номер строки, заполняемой потоком
	int p = *(int*)param;
	//вычисление элементов матрицы, стоящих в строке p
	for (int i = 0; i < 3; i++) {
		C[p][i] = 0;
		for (int j = 0; j < 3; j++) {
			C[p][i] += A[p][j] * B[j][i];
		}
		//протокол входа в КС: закрыть двоичный семафор
		pthread_mutex_lock(&mutex);
			//начало критической секции
			// – запись результата в очередь
			newrez = new result;
		printf(newrez->str,
			"Поток %d: вычислен элемент [%d][%d] = %d\0",
			p, p, i, C[p][i]
		);
		//конец критической секции
		//протокол выхода из КС:
		pthread_mutex_unlock(&mutex);
		//открыть двоичный семафор
	}
	return nullptr;
}
int main() {
	//setlocale(LC_ALL, "Russian");
	head = new result;
	rez = head; //создание первого элемента очереди
	//инициализация двоичного семафора
	pthread_mutex_init(&mutex, NULL);
	//идентификаторы для дочерних потоков
	pthread_t mythread1, mythread2;
	int num[3];
	for (int i = 0; i < 3; i++) {
		num[i] = i; //номера строк для потоков
	}
		//создание дочерних потоков
		pthread_create(&mythread1, NULL, func,
			(void*)(num + 1));
	pthread_create(&mythread2, NULL, func,
		(void*)(num + 2));
	//заполнение первой строки результирующей матрицы
	func((void*)num);
	//ожидание завершения дочерних потоков
	pthread_join(mythread1, NULL);
	pthread_join(mythread2, NULL);
		rez = head->next;
	while (rez != NULL) { //вывод очереди
		printf("\n%s", rez->str);
		rez = rez->next;
	}
	// вывод результата вычислений всех потоков
	printf("\n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%d ", C[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}