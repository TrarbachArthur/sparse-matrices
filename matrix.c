#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

Node* node_create(float value, int row, int column) {
    Node* node = calloc(1, sizeof(Node));
    node->row = row;
    node->column = column;
    node->value = value;
    node->next_column = NULL;
    node->next_row = NULL;

    return node;
}
Matrix* matrix_create(int row_amt, int column_amt) {
    Matrix* matrix = calloc(1, sizeof(Matrix));
    matrix->row_amt = row_amt;
    matrix->column_amt = column_amt;
    matrix->rows = calloc(row_amt, sizeof(Node*));
    matrix->columns = calloc(column_amt, sizeof(Node*));

    return matrix;
}

// No need to be inplace
void matrix_add(Matrix* matrix, float value, int row, int column) {
    if (matrix->column_amt <= column || matrix->row_amt <= row) {
        printf("A coluna ou linha não existe na matriz!\n");
        return;
    }

    Node *new_node = node_create(value, row, column);
    Node *prev, *curr;

    // Adding to column
    if (matrix->columns[column] == NULL) {
        matrix->columns[column] = new_node;
    }
    else {
        prev = NULL;
        curr = matrix->columns[column];

        while (curr) {
            if (curr->row > row) {
                new_node->next_column = curr;
                if (prev == NULL) {
                    matrix->columns[column] = new_node;
                    break;
                }
                else {
                    prev->next_column = new_node;
                }
            }
            else {
                if (curr->next_column == NULL) {
                    curr->next_column = new_node;
                    break;
                }
                prev = curr;
                curr = curr->next_column;
            }
        }
    }

    // Adding to row
    if (matrix->rows[row] == NULL) {
        matrix->rows[row] = new_node;
    }
    else {
        prev = NULL;
        curr = matrix->rows[row];

        while (curr != NULL) {
            if (curr->column > column) {
                new_node->next_row = curr;
                if (prev == NULL) {
                    matrix->rows[row] = new_node;
                }
                else {
                    prev->next_row = new_node;
                    printf("Adicionando\n");
                }
            }
            else {
                if (curr->next_row == NULL) {
                    curr->next_row = new_node;
                    break;
                }
                prev = curr;
                curr = curr->next_row;
            }
        }
    }
}
Node* matrix_get_index(Matrix* matrix, int row, int column) {
    Node* aux = matrix->columns[column];

    while (aux) {
        if (aux->row == row) {
            return aux;
        }
        aux = aux->next_column;
    }

    return NULL;
}
float matrix_get_value(Matrix* matrix, int row, int column) {
    if (row >= matrix->row_amt || column >= matrix->column_amt) {
        printf("Linha ou coluna não pertence a matriz\n");
        exit(1);
    }

    Node* node = matrix_get_index(matrix, row, column);

    if (node == NULL) {
        return 0;
    }

    return node->value;
}

Matrix* matrix_sum(Matrix* m1, Matrix* m2);
Matrix* matrix_multiply_escalar(Matrix* m, float n);
Matrix* matrix_multiply_matrix(Matrix* m1, Matrix* m2);
Matrix* matrix_multiply_point(Matrix* m1, Matrix* m2);
Matrix* matrix_swap_rows(Matrix* matrix, int row1, int row2);
Matrix* matrix_swap_columns(Matrix* matrix, int col1, int col2);
Matrix* matrix_slice(Matrix* matrix, int row1, int col1, int row2, int col2);
Matrix* matrix_transpose(Matrix* matrix);
Matrix* matrix_convolution(Matrix* matrix, Matrix* kernel);

void matrix_print_sparse(Matrix* matrix) {
    for (int i=0; i<matrix->row_amt; i++) {
        if (matrix->rows[i]) {
            Node* curr = matrix->rows[i];

            while (curr) {
                printf("(%d, %d) -> %.2f ", curr->row, curr->column, curr->value);
                curr = curr->next_row;
            }
        }
        printf("\n");
    }
}
void matrix_print_dense(Matrix* matrix) {
    for (int i=0; i<matrix->row_amt; i++) {
        for (int j=0; j<matrix->column_amt; j++) {
            printf("%.2f ", matrix_get_value(matrix, i, j));
        }
        printf("\n");
    }
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