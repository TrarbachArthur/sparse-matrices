#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    Matrix* matrix = matrix_create(10, 10);
    
    printf("%p", matrix->rows[7]);
}