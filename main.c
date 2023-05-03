#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    Matrix* matrix = matrix_create(10, 10);
    matrix_add(matrix, 7, 2, 3);
    matrix_add(matrix, 2, 1, 1);
    matrix_add(matrix, 3, 1, 3);
    matrix_add(matrix, 9, 9, 8);

    //Node* node = matrix_get_index(matrix, 2, 3);
    //printf("%p", node);
    //printf("%f %d %d\n", node->value, node->row, node->column);

    matrix_print_sparse(matrix);

    return 0;
}