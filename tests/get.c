#include "../matrix.h"

int get() {
/*
    Original matrix: 
        0 0 2
        0 0 3
        7 0 9
    
    Expected output depends on the coordinates typed
*/
    printf("Original matrix:\n");
    Matrix* matrix2 = matrix_create(3, 3);
    matrix_add(matrix2, 7, 2, 0);
    matrix_add(matrix2, 2, 0, 2);
    matrix_add(matrix2, 9, 2, 2);
    matrix_add(matrix2, 3, 1, 2);

    // Testing the remove function
    matrix_add(matrix2, 5, 2, 1);
    matrix_add(matrix2, 0, 2 ,1);

    matrix_print_sparse(matrix2);

    int row, col;

    printf("Enter the coordinates of the value(row col): ");
    scanf("%d %d", &row, &col);
    printf("The value of (%d, %d) is: %.2f\n", row, col, matrix_get_value(matrix2, row, col));

    matrix_destroy(matrix2);

    return 0;
}