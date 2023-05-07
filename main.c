#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    Matrix* matrix1 = matrix_create(3, 3);
    matrix_add(matrix1, 1, 0, 0);
    matrix_add(matrix1, 1, 1, 1);
    matrix_add(matrix1, 1, 2, 2);

    Matrix* matrix2 = matrix_create(3, 3);
    matrix_add(matrix2, 7, 2, 0);
    matrix_add(matrix2, 2, 0, 2);
    matrix_add(matrix2, 9, 2, 2);
    matrix_add(matrix2, 3, 1, 2);

    matrix_print_dense(matrix1);
    matrix_print_dense(matrix2);

    Matrix* new_matrix = matrix_swap_rows(matrix1, 0, 1);
    matrix_print_dense(new_matrix);
    matrix_destroy(new_matrix);

    new_matrix = matrix_swap_columns(matrix2, 1, 2);
    matrix_print_dense(new_matrix);
    matrix_destroy(new_matrix);

    matrix_destroy(matrix1);
    matrix_destroy(matrix2);

    return 0;
}