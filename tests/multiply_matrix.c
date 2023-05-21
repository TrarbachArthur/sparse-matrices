#include "../matrix.h"

int multMatrix() {
/*
    First matrix: 
        0 2 0
        0 0 3
        4 0 9
        0 5 0
        0 0 0
    
    Seconde matrix:
        0 2
        0 3
        7 9

    Expected output:
        0 2 0
        0 3 0
        7 9 0
*/  
    printf("First original matrix:\n");
    Matrix* matrix1 = matrix_create(5, 3);
    matrix_add(matrix1, 4, 2, 0);
    matrix_add(matrix1, 2, 0, 1);
    matrix_add(matrix1, 9, 2, 2);
    matrix_add(matrix1, 3, 1, 2);
    matrix_add(matrix1, 5, 3, 1);

    matrix_print_dense(matrix1);

    printf("Second original matrix:\n");
    Matrix* matrix2 = matrix_create(3, 2);
    matrix_add(matrix2, 7, 2, 0);
    matrix_add(matrix2, 2, 0, 1);
    matrix_add(matrix2, 9, 2, 1);
    matrix_add(matrix2, 3, 1, 1);

    matrix_print_dense(matrix2);

    printf("Multiplying matrices:\n");
    Matrix* new_matrix = matrix_multiply_matrix(matrix1, matrix2);
    matrix_print_dense(new_matrix);
    matrix_destroy(new_matrix);
    matrix_destroy(matrix1);
    matrix_destroy(matrix2);

    return 0;
}