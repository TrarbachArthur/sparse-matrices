#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

Node* node_create(float value, int row, int column) {
    Node* node = calloc(1, sizeof(Node));
    node->row = row;
    node->column = column;
    node->next_column = NULL;
    node->next_row = NULL;

    return node;
}
Matrix* matrix_create(int row_amt, int column_amt) {
    Matrix* matrix = calloc(1, sizeof(Matrix));
    matrix->row_amt = row_size;
    matrix->column_amt = column_size;
    matrix->rows = calloc(row_size, sizeof(Node*));
    matrix->columns = calloc(column_size, sizeof(Node*));

    return matrix;
}

// No need to be inplace
void matrix_add(Matrix* matrix, float value, int row, int column);
float matrix_get_value(Matrix* matrix, int row, int column);

Matrix* matrix_sum(Matrix* m1, Matrix* m2);
Matrix* matrix_multiply_escalar(Matrix* m, float n);
Matrix* matrix_multiply_matrix(Matrix* m1, Matrix* m2);
Matrix* matrix_multiply_point(Matrix* m1, Matrix* m2);
Matrix* matrix_swap_rows(Matrix* matrix, int row1, int row2);
Matrix* matrix_swap_columns(Matrix* matrix, int col1, int col2);
Matrix* matrix_slice(Matrix* matrix, int row1, int col1, int row2, int col2);
Matrix* matrix_transpose(Matrix* matrix);
Matrix* matrix_convolution(Matrix* matrix, Matrix* kernel);

void matrix_print_sparse(Matrix* matrix);
void matrix_print_dense(Matrix* matrix) {
    for(int j = 0; j < matrix->column_size)
}

void matrix_save_binary(Matrix* matrix, char* file_path);
Matrix* matrix_read_binary(char* file_path);

void node_destroy(Node* node) {
    free(node);
}
void matrix_destroy(Matrix* matrix) {
    // TO DO: FREE ALL NODES INSIDE THE MATRIX

    free(matrix->rows);
    free(matrix->columns);
    free(matrix);
}