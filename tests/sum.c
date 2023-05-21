#include "../matrix.h"

int sum() {
/*
    Original first matrix: 
        1 0 0
        0 1 0
        0 0 1
    
    Original second matrix:
        0 0 3
        0 0 2
        7 0 8

    Expected output:
        1 0 2
        0 1 3
        7 0 9
*/

    printf("First original matrix:\n");
    Matrix* matrix1 = matrix_create(3, 3);
    matrix_add(matrix1, 1, 0, 0);
    matrix_add(matrix1, 1, 1, 1);
    matrix_add(matrix1, 1, 2, 2);

    matrix_print_dense(matrix1); 

    printf("Second original matrix:\n");
    Matrix* matrix2 = matrix_create(3, 3);
    matrix_add(matrix2, 7, 2, 0);
    matrix_add(matrix2, 2, 0, 2);
    matrix_add(matrix2, 8, 2, 2);
    matrix_add(matrix2, 3, 1, 2);

    matrix_print_dense(matrix2);

    printf("Sum output:\n");
    Matrix* new_matrix = matrix_sum(matrix1, matrix2);
    matrix_print_dense(new_matrix);
    matrix_destroy(new_matrix);

    matrix_destroy(matrix1);
    matrix_destroy(matrix2);

    return 0;
}