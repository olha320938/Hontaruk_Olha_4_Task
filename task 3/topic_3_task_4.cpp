#include <iostream>
#include <iomanip>
#include <ctime>
#include <Windows.h>
using namespace std;
// створення динамічної матриці n на n
int** createMatrix(int n) {
	int** matrix = new int* [n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new int[n];
	}
	return matrix;
}
// заповнення матриці випадковими числами від -14 до 14
void fillMatrix(int** matrix, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = rand() % 29 - 14;
		}

	}
}
// виведення матриці на екран
void printMatrix(int** matrix, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << setw(5) << matrix[i][j];
		}
		cout << endl;
	}
}
// обчислення середнього арифметичного від'ємних елементів матриці
double getAverageNegative(int** matrix, int n) {
	double sum = 0;
	int count = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] < 0) {
				sum += matrix[i][j];
				count++;
			}
		}
	}
	return (count > 0) ? sum / count : 0;
}
// сума непарних елементів сектора 1
int sumOddSector1(int** matrix, int n) {
	int sum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			// вище головної і вищее побічної діагоналі
			if (i < j && (i + j) < (n - 1)) {
				if (matrix[i][j] % 2 != 0) {
					sum += matrix[i][j];
				}
			}
		}
	}
	return sum;
}
// підрахунок елементів сектора 10 та їх заміна на avgNeg
int processSector10(int** matrix, int n, double avgNeg) {
	int count = 0;
	int startCol = n / 2;
	for (int i = 0; i < n; i++) {
		for (int j = startCol; j < n; j++) {
			count++;
			matrix[i][j] = (int)avgNeg;
		}
	}
	return count;
}
// звільнення пам'яті
void deleteMatrix(int** matrix, int n) {
	for (int i = 0; i < n; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

int main()
{
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	srand(static_cast<unsigned int>(time(0)));

	int n;
	cout << "Введіть розмір матриці n:";
	cin >> n;

	if (n <= 0) {
		cout << "Розмір має бути більше 0!" << endl;
		return 1;
	}

	int** matrix = createMatrix(n);
	fillMatrix(matrix, n);
	cout << "\nПочаткова матриця:\n";
	printMatrix(matrix, n);
	// обчислюємо потрібні значення до модифікації матриці
	double avgNeg = getAverageNegative(matrix, n);
	int sumOdd1 = sumOddSector1(matrix, n);

	cout << "\n--- Результати ---\n";
	cout << "1. Середнє від'ємних (по всій матриці): " << fixed << setprecision(2) << avgNeg << endl;
	cout << "2. Сума непарних у секторі 1: " << sumOdd1 << endl;

	int count10 = processSector10(matrix, n, avgNeg);
	cout << "3. Кількість елементів у секторі 10: " << count10
		<< " (всі замінені на " << (int)avgNeg << ")" << endl;

	cout << "\nМатриця після модифікації сектора 10:\n";
	printMatrix(matrix, n);

	deleteMatrix(matrix, n);
	return 0;

}