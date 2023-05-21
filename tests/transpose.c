#include "../matrix.h"

int transpose() {
/*
    Original matrix: 
        0 0 2
        0 0 3
        7 0 9
    
    Expected output:
        0 0 7
        0 0 0
        2 3 9
*/
    printf("Original matrix:\n");
    Matrix* matrix2 = matrix_create(3, 3);
    matrix_add(matrix2, 7, 2, 0);
    matrix_add(matrix2, 2, 0, 2);
    matrix_add(matrix2, 9, 2, 2);
    matrix_add(matrix2, 3, 1, 2);

    matrix_print_dense(matrix2);

    printf("Output:\n");
    Matrix* new_matrix = matrix_transpose(matrix2);
    matrix_print_dense(new_matrix);
    matrix_destroy(new_matrix);

    matrix_destroy(matrix2);

    return 0;
}