#include "../matrix.h"

int swap() {
/*
    Original matrix: 
        0 0 2
        0 0 3
        7 0 9
    
    Row swap output:
        0 0 3
        0 0 2
        7 0 9

    Column swap output:
        0 2 0
        0 3 0
        7 9 0
*/
    printf("Original matrix:\n");
    Matrix* matrix2 = matrix_create(3, 3);
    matrix_add(matrix2, 7, 2, 0);
    matrix_add(matrix2, 2, 0, 2);
    matrix_add(matrix2, 9, 2, 2);
    matrix_add(matrix2, 3, 1, 2);

    matrix_print_dense(matrix2);

    printf("Swapping row 0 and 1 from original:\n");
    Matrix* new_matrix = matrix_swap_rows(matrix2, 0, 1);
    matrix_print_dense(new_matrix);
    matrix_destroy(new_matrix);

    printf("Swapping column 1 and 2 from original:\n");
    new_matrix = matrix_swap_columns(matrix2, 1, 2);
    matrix_print_dense(new_matrix);
    matrix_destroy(new_matrix);

    matrix_destroy(matrix2);

    return 0;
}