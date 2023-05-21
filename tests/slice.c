#include "../matrix.h"

int slice() {
/*
    Original matrix: 
        0 1 1 1 0 0 0
        0 0 1 1 1 0 0 
        0 0 0 1 1 1 0
        0 0 0 1 1 0 0 
        0 0 1 1 0 0 0
        0 1 1 0 0 0 0
        1 1 0 0 0 0 0
    
    Output depends on the chosen slicing area
*/

// Setting up original matrix

    Matrix* matrix = matrix_create(7, 7);

    matrix_add(matrix, 1, 0, 1);
    matrix_add(matrix, 1, 0, 2);
    matrix_add(matrix, 1, 0, 3);

    matrix_add(matrix, 1, 1, 2);
    matrix_add(matrix, 1, 1, 3);
    matrix_add(matrix, 1, 1, 4);
    
    matrix_add(matrix, 1, 2, 3);
    matrix_add(matrix, 1, 2, 4);
    matrix_add(matrix, 1, 2, 5);
    
    matrix_add(matrix, 1, 3, 3);
    matrix_add(matrix, 1, 3, 4);

    matrix_add(matrix, 1, 4, 2);
    matrix_add(matrix, 1, 4, 3);

    matrix_add(matrix, 1, 5, 1);
    matrix_add(matrix, 1, 5, 2);

    matrix_add(matrix, 1, 6, 0);
    matrix_add(matrix, 1, 6, 1);

    printf("Original matrix:\n");
    matrix_print_dense(matrix);

    int row1, col1, row2, col2;

    printf("Enter the upper-left bounds (row col): ");
    scanf("%d %d", &row1, &col1);
    printf("Enter the lower-right bounds (row col): ");
    scanf("%d %d", &row2, &col2);

    Matrix* new_matrix = matrix_slice(matrix, row1, col1, row2, col2);

    printf("\nOutput:\n");
    matrix_print_dense(new_matrix);

    matrix_destroy(matrix);
    matrix_destroy(new_matrix);

    return 0;
}