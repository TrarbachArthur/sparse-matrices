#include "../matrix.h"

int convolution() {
/*
    Original matrix: 
        0 1 1 1 0 0 0
        0 0 1 1 1 0 0 
        0 0 0 1 1 1 0
        0 0 0 1 1 0 0 
        0 0 1 1 0 0 0
        0 1 1 0 0 0 0
        1 1 0 0 0 0 0
    
    Kernel:
        1 0 1
        0 1 0
        1 0 1
    
    Expected output:
        0 2 2 3 1 1 0
        1 1 4 3 4 1 1
        0 1 2 4 3 3 0
        0 1 2 3 4 1 1
        1 1 3 3 1 1 0
        1 3 3 1 1 0 0
        2 2 1 1 0 0 0

    (sparse matrix will also be displayed and can be checked by comparison with the dense one)
*/

// Setting up original matrix

    Matrix* matrix = matrix_create(7, 7);
    Matrix* kernel = matrix_create(3, 3);

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

// Setting up convolution kernel
    matrix_add(kernel, 1, 0, 0);
    matrix_add(kernel, 1, 0, 2);

    matrix_add(kernel, 1, 1, 1);

    matrix_add(kernel, 1, 2, 0);
    matrix_add(kernel, 1, 2, 2);

    printf("Kernel:\n");
    matrix_print_dense(kernel);
// Starting actual convolution testing

    Matrix* new_matrix = matrix_convolution(matrix, kernel);

    printf("Sparse output:\n");
    matrix_print_sparse(new_matrix);

    printf("Saving matrix to binary file (./matrix.bin)...\n");
    matrix_save_binary(new_matrix, "./matrix.bin");
    printf("Destroying previous generated matrix...\n");
    matrix_destroy(new_matrix);
    printf("Reading convoluted matrix from the binary file (./matrix.bin)...\n");
    Matrix* file_matrix = matrix_read_binary("./matrix.bin");

    printf("\nDense output:\n");
    matrix_print_dense(file_matrix);

    matrix_destroy(matrix);
    matrix_destroy(kernel);
    matrix_destroy(file_matrix);

    return 0;
}