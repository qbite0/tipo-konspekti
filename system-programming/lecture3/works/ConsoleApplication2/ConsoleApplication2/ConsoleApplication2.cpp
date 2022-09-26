#include <iostream>
#include <process.h>

const int n = 0;
const int P = 0;
const int l = 0;

const unsigned int x = 3;
const unsigned int y = 3;

int a[x][y];
int b[x][y];
int c[x][y];

int main() {
	for (int i = 0; i < n - 1; i++) {
		// строки параллельно, затем со
		for (int j = 0; j < n - 1; j++) {
			// столбцы параллельно
			c[i][j] = 0;
			for(int k = 0; k < n - 1; k++)
				c[i][j] = c[i][j] + a[i][k] * b[k][j];
		}
	}
	for(int w = 1; w < P; w++) { //#полосы параллельно
		int first = (w - 1) * n / P; // первая строка полосы
		int last = first + n / P - 1; // последняя строка полосы

		for (int i = first; i < last; i++) {
			for (int j = 0; j < n - l; j++) {
				c[i][j] = 0;
				for (int k = 0; k < n - 1; k++)
					c[i][j] = c[i][j] + a[i][k] * b[k][j];
			}
		}
	}
}