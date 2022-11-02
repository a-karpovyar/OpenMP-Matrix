#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <fstream>

using namespace std;

void make_random_matrix(int** matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = rand() % 11;
        }
    }

    return;
}
  


int main(int argc, char** argv) {
    srand(time(NULL));
    int n1, m1, n2, m2;
    cout << "Size of matrix1";
    cin >> n1;
    m1 = n1;
    cout << "Size of matrix2";
    cin >> n2;
    m2 = n2;
    int** matrix1;

    int** matrix2;

    matrix1 = (int**)malloc(sizeof(int*) * n1);
    for (int i = 0; i < n1; i++) {
        matrix1[i] = (int*)malloc(sizeof(int) * m1);
    }
    matrix2 = (int**)malloc(sizeof(int*) * n2);
    for (int i = 0; i < n2; i++) {
        matrix2[i] = (int*)malloc(sizeof(int) * m2);
    }

    make_random_matrix(matrix1, n1, m1);
    make_random_matrix(matrix2, n2, m2);

    int** result = (int**)malloc(sizeof(int*) * n1);;
    for (int i = 0; i < n1; i++) {
        result[i] = (int*)malloc(sizeof(int) * m2);
    }

    int threadsNum = 1;//Число потоков
    omp_set_num_threads(threadsNum);

    int i, j, k;
    auto start = omp_get_wtime();

#pragma omp parallel for shared(matrix1, matrix2, result) private(i, j, k)
    for (i = 0; i < n1; i++) {
        for (j = 0; j < m2; j++) {
            result[i][j] = 0;
            for (k = 0; k < m1; k++) {
                result[i][j] += (matrix1[i][k] * matrix2[k][j]);
            }
        }
    }


    auto end = omp_get_wtime();
    cout << "Expect,programm working... "<< endl;
    cout << "Time of working: " << (end - start) <<" second" << endl;

    return 0;
}