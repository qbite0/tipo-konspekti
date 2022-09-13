// ConsoleApplication2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <process.h>

int main() {
	const int n = 0;
	int a[10][10];
	int b[10][10];
	int ary c = 10;

	for (int i = 0; i < n - 1; i++){
		// параллельное вычисление строк
		for (int j = 0; i < n - 1; i++) {
			c[i,j] = 0.0;
			for (int k = 0; k < n - 1; k++)
				c[i,j] = c[i,j] + a[i,k] * b[k,j];
		}
	}

	for (i = 0 to n - 1, j = 0 to n - 1)
	{
		// все  строки и
		с[i,j] = 0.О; // все  столбцы

		for[k = 0  to n - 1] {
			c[i,j] = c[i,j] + a[i,k] * b[k,j];
		}
	}

	for[i = 0 to n - 1]{
		// строки параллельно, затем со
		for[j = 0 to n - 1] {
			// столбцы параллельно
			c[i,j] = 0.0;
			for[k = 0  to n - 1]
				c[i,j] = c[i,j] + a[i,k] * b[k,j];
		}
	}

	process row[i = 0 to n - 1]{
		//строки параллельно
		for[j = 0 to n - 1] {
			c[i,j] = 0.0;
			for[k = 0  to n - 1]
				c[i,j] = c[i,j] + a[i,k] * b[k,j];
		}
	}

	process worker[w = 1 to P]{ //#полосы параллельно
		int first = (w - 1) * n / P; // первая строка полосы
		int last = first + n / P - 1; // последняя строка полосы

		for [i = first to last] {
			for (j = 0 to n - l) {
				c[i, j] = 0.0;
				for[k = 0 to n - 1]
					c[i, j) = c[i, j) + a[i, k] * b[k, j);
			}
		}
	}
}