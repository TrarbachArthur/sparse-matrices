#ifndef MATRIX_H
#define MATRIX_H

typedef struct node {
    int row, column;
    float value;
    struct node *next_row, *next_column;
} Node;

typedef struct matrix {
    int row_amt, column_amt;
    Node **rows, **columns;
} Matrix;

Node* node_create(float value, int row, int column);
Matrix* matrix_create(int row_amt, int column_amt);

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
void matrix_print_dense(Matrix* matrix);

void matrix_save_binary(Matrix* matrix, char* file_path);
Matrix* matrix_read_binary(char* file_path);

void node_destroy(Node* node);
void matrix_destroy(Matrix* matrix);

#endif