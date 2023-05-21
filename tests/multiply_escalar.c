#include "../matrix.h"

int multEscalar() {
/*
    Original matrix: 
        0 0 2
        0 0 3
        7 0 9

    Output depends on the chosen escalar
*/
    printf("Original matrix:\n");
    Matrix* matrix2 = matrix_create(3, 3);
    matrix_add(matrix2, 7, 2, 0);
    matrix_add(matrix2, 2, 0, 2);
    matrix_add(matrix2, 9, 2, 2);
    matrix_add(matrix2, 3, 1, 2);

    matrix_print_dense(matrix2);
    
    float num;
    printf("Enter the escalar you want to multiply by: ");
    scanf("%f", &num);
    printf("\nMultiplying by %.2f:\n", num);
    Matrix* new_matrix = matrix_multiply_escalar(matrix2, num);
    matrix_print_dense(new_matrix);
    matrix_destroy(new_matrix);

    matrix_destroy(matrix2);

    return 0;
}