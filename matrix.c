#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

// O(1) tempo contante independente dos parametros
Node* node_create(float value, int row, int column) {
    Node* node = calloc(1, sizeof(Node));
    node->row = row;
    node->column = column;
    node->value = value;
    node->next_column = NULL;
    node->next_row = NULL;

    return node;
}

// O(1) tempo constate considerando que calloc utiliza memset
Matrix* matrix_create(int row_amt, int column_amt) {
    Matrix* matrix = calloc(1, sizeof(Matrix));
    matrix->row_amt = row_amt;
    matrix->column_amt = column_amt;
    matrix->rows = calloc(row_amt, sizeof(Node*));
    matrix->columns = calloc(column_amt, sizeof(Node*));

    return matrix;
}

// O(m+k) = O(n) considerando m o numero de elementos anteriores na linha e n o numero na coluna
void matrix_remove(Matrix* matrix, int row, int column) {
    // removing from column
    Node* prev = NULL, * node = NULL;

    node = matrix->columns[column];
    while (node) {
        if (node->row == row) {
            if (prev == NULL) {
                matrix->columns[column] = node->next_column;
            }
            else {
                prev->next_column = node->next_column;
            }
            break;
        }
        prev = node;
        node = node->next_column;
    }

    prev = NULL;
    node = matrix->rows[row];
    while (node) {
        if (node->column == column) {
            if (prev == NULL) {
                matrix->rows[row] = node->next_row;
            }
            else {
                prev->next_row = node->next_row;
            }
            node_destroy(node);
            break;
        }
        prev = node;
        node = node->next_row;
    }

}

// O(m+k) = O(n) assim como o remove
void matrix_add(Matrix* matrix, float value, int row, int column) {
    if (value == 0) {
        Node* node;
        if (node = matrix_get_index(matrix, row, column)) {
            matrix_remove(matrix, row, column);
        }
        return;
    }
    if (matrix->column_amt <= column || matrix->row_amt <= row) {
        printf("Line or column does not belong to the matrix\n");
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
                    break;
                }
            }
            else if (curr->row == row) {
                curr->value = value;
                node_destroy(new_node);
                break;
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

        while (curr) {
            if (curr->column > column) {
                new_node->next_row = curr;
                if (prev == NULL) {
                    matrix->rows[row] = new_node;
                    break;
                }
                else {
                    prev->next_row = new_node;
                    break;
                }
            }
            else if (curr->column == column) break;
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

// O(n) ja que so eh necessario iterar pela linha OU coluna
Node* matrix_get_index(Matrix* matrix, int row, int column) {
    if (row < 0 || row > matrix->row_amt - 1) return NULL;
    if (column < 0 || column > matrix->column_amt - 1) return NULL;

    Node* aux = matrix->columns[column];

    while (aux) {
        if (aux->row == row) {
            return aux;
        }
        aux = aux->next_column;
    }

    return NULL;
}
// O(n) utiliza o get_index e o resto eh constante
float matrix_get_value(Matrix* matrix, int row, int column) {
    if (row >= matrix->row_amt || column >= matrix->column_amt) {
        printf("Line or column does not belong to the matrix\n");
        exit(1);
    }

    Node* node = matrix_get_index(matrix, row, column);

    if (node == NULL) {
        return 0;
    }

    return node->value;
}

// O(n2) necessario iterar por todos os itens da matriz
float matrix_sum_values(Matrix* matrix) {
    float sum = 0;

    for (int i=0; i < matrix->row_amt; i++) {
        Node* node = matrix->rows[i];

        while (node != NULL) {
            sum += node->value;
            node = node->next_row;
        }
    }

    return sum;
}


// O(2*n2) = O(n2) iterando por todos os itens de ambas as matrizes individualmente
Matrix* matrix_sum(Matrix* m1, Matrix* m2) {
    Matrix* new_matrix = matrix_create(m1->row_amt, m1->column_amt);

    for (int i=0; i<m1->row_amt; i++) {
        Node* node1 = m1->rows[i];
        Node* node2 = m2->rows[i];
        while (node1) {
            if (node2) {
                if (node1->column == node2->column) {
                    matrix_add(new_matrix, node1->value+node2->value, i, node1->column);
                    node1 = node1->next_row;
                    node2 = node2->next_row;
                }
                else if (node1->column > node2->column) {
                    matrix_add(new_matrix, node2->value, i, node2->column);
                    node2 = node2->next_row;
                }
                else if (node1->column < node2->column) {
                    matrix_add(new_matrix, node1->value, i, node1->column);
                    node1 = node1->next_row;
                }
            }
            else {
                matrix_add(new_matrix, node1->value, i, node1->column);
                node1 = node1->next_row;
            }
        }

        while (node2) {
            matrix_add(new_matrix, node2->value, i, node2->column);
            node2 = node2->next_row;
        }
    }

    return new_matrix;
}

// O(n2) iterando por todos os elementos da matriz
Matrix* matrix_multiply_escalar(Matrix* m, float n) {
    Matrix* new_matrix = matrix_create(m->row_amt, m->column_amt);

    for (int i=0; i<m->row_amt; i++) {
        Node* curr = m->rows[i];

        while (curr) {
            matrix_add(new_matrix, curr->value*n, curr->row, curr->column);
            curr = curr->next_row;
        }
    }
    return new_matrix;
}

// O(i*j*m) * O(n) = O(n4) onde i = linhas de m1 | j = colunas de m1 | k = colunas de m2 | realizando add para cada elemento
Matrix* matrix_multiply_matrix(Matrix* m1, Matrix* m2) {
    if (m1->column_amt != m2->row_amt) {
        printf("Error: can't multiply matrices of this dimensions\n");
        return NULL;
    }
    Matrix* new_matrix = matrix_create(m1->row_amt, m2->column_amt);

    for (int i=0; i<m1->row_amt; i++) {
        Node* node1 = m1->rows[i];
        for (int j=0; j<m2->column_amt && node1; j++) {
            Node* node2 = m2->columns[j];
            float sum=0;
            while (node1 && node2) {
                if (node1->column == node2->row) {
                    sum += node1->value * node2->value;
                    node1 = node1->next_row;
                    node2 = node2->next_column;
                }
                else if (node1->column > node2->row) {
                    node2 = node2->next_column;
                }
                else {
                    node1 = node1->next_row;
                }
            }
            matrix_add(new_matrix, sum, i, j);
            node1 = m1->rows[i]; // Resets the reference to the row of the first matrix
        }
    }

    return new_matrix;
}

// O(n2) * O(n) = O(n3) iterando por todos os elementos de m1 e m2 AO MESMO TEMPO e realizando add
Matrix* matrix_multiply_point(Matrix* m1, Matrix* m2) {
    Matrix* new_matrix = matrix_create(m1->row_amt, m1->column_amt);

    for (int i=0; i<m1->row_amt; i++) {
        Node* node1 = m1->rows[i];
        Node* node2 = m2->rows[i];
        while (node1 && node2) {
            if (node2->column == node1->column) {
                matrix_add(new_matrix, node1->value * node2->value, node1->row, node1->column);
                node1 = node1->next_row;
                node2 = node2->next_row;
            }
            else if (node1->column > node2->column) {
                node2 = node2->next_row;
            }
            else {
                node1 = node1->next_row;
            }
        }
    }
    return new_matrix;
}

// O(n2) * O(n) = O(n3) iterando por todos os elemento da matriz e realizando add para cada um
Matrix* matrix_swap_rows(Matrix* matrix, int row1, int row2) {
    Matrix* new_matrix = matrix_create(matrix->row_amt, matrix->column_amt);
    int row=0;
    for (int i=0; i<matrix->row_amt; i++) {
        row = i;
        if (i == row1) row = row2;
        else if (i == row2) row = row1;

        Node* node = matrix->rows[i];

        while (node) {
            matrix_add(new_matrix, node->value, row, node->column);
            node = node->next_row;
        }
    }

    return new_matrix;
}

// O(n3) mesmo do swap_rows
Matrix* matrix_swap_columns(Matrix* matrix, int col1, int col2) {
    Matrix* new_matrix = matrix_create(matrix->row_amt, matrix->column_amt);
    int col=0;
    for (int i=0; i<matrix->column_amt; i++) {
        col = i;
        if (i == col1) col = col2;
        else if (i == col2) col = col1;

        Node* node = matrix->columns[i];

        while (node) {
            matrix_add(new_matrix, node->value, node->row, col);
            node = node->next_column;
        }
    }
    return new_matrix;
}

// O(n) * O(n) = O(n2) iterando por todos os elementos do intervalo e realizando add
Matrix* matrix_slice(Matrix* matrix, int row1, int col1, int row2, int col2) {
    if (row1 > row2 || col1 > col2) {
        printf("Slice borders out of order\n");
        return NULL;
    }
    Matrix* new_matrix = matrix_create(row2-row1+1, col2-col1+1);

    for (int i=row1; i<=row2 && i < matrix->row_amt; i++) {
        if (i < 0) continue;
        Node* node = matrix->rows[i];
        while (node) {
            if (node->column >= col1 && node->column <= col2) {
                matrix_add(new_matrix, node->value, i-row1, node->column - col1);
            }
            if (node->column > col2) break;
            node = node->next_row;
        }
    }

    return new_matrix;
}

// O(n2) * O(n) = O(n3) iterando por todos os elementos e adicionando a nova matriz
Matrix* matrix_transpose(Matrix* matrix) {
    Matrix* new_matrix = matrix_create(matrix->column_amt, matrix->row_amt);

    for (int i=0; i<matrix->row_amt; i++) {
        Node* node = matrix->rows[i];

        while (node) {
            matrix_add(new_matrix, node->value, node->column, node->row);
            node = node->next_row;
        }
    }

    return new_matrix;
}

// O(n2) * (O(n2)+O(n3)+O(n)+O(n2)+O(n2)) = O(n2) * O(n3) = O(n5)
// Iterando por todos os elementos e realizando operacoes onde a mais custosa e a multiplicacao ponto a ponto
Matrix* matrix_convolution(Matrix* matrix, Matrix* kernel) {
    if (kernel->column_amt % 2 == 0 || kernel->row_amt % 2 == 0) {
        printf("Unable to process a convolution with an even sized kernel\n");
        return NULL;
    }

    Matrix* new_matrix = matrix_create(matrix->row_amt, matrix->column_amt);

    int line_offset = (kernel->row_amt - 1) / 2;
    int column_offset = (kernel->column_amt - 1) / 2;

    for (int i = 0; i < matrix->row_amt; i++) {
        for (int j = 0; j < matrix->column_amt; j++) {
            Matrix* slice = matrix_slice(matrix, i-line_offset, j-column_offset, i+line_offset, j+column_offset);
            Matrix* conv_slice = matrix_multiply_point(slice, kernel);

            matrix_add(new_matrix, matrix_sum_values(conv_slice), i, j);
            matrix_destroy(slice);
            matrix_destroy(conv_slice);
        }
    }
    
    return new_matrix;
}


// O(n2) iterando por todos os elementos
void matrix_print_sparse(Matrix* matrix) {
    for (int i=0; i<matrix->row_amt; i++) {
        Node* curr = matrix->rows[i];

        while (curr) {
            printf("(%d, %d) -> %.2f |", curr->row, curr->column, curr->value);
            curr = curr->next_row;
        }
        printf("\n");
    }
    printf("\n");
}

// O(n2) iterando por todos os elementos
void matrix_print_dense(Matrix* matrix) {
    // last_col represents the last empty column
    int max_col=matrix->column_amt, last_col=0, actual_col=0;
    
    for (int i = 0; i < matrix->row_amt; i++) {
        Node* node = matrix->rows[i];
        last_col = actual_col = 0;
        while (node) {
            actual_col = node->column;
            
            for (int i=last_col; i<actual_col; i++) {
                printf("0.00 ");
            }

            printf("%.2f ", node->value);

            node = node->next_row;
            last_col = actual_col+1;
        }

        for (int i=last_col; i<max_col; i++) {
            printf("0.00 ");
        }
        printf("\n");

    }
    printf("\n");
}


// O(n2) iterando por todos os elementos
void matrix_save_binary(Matrix* matrix, char* file_path) {
    FILE* file = fopen(file_path, "wb");
    float aux = 0;

    fwrite(&matrix->row_amt, sizeof(int), 1, file);
    fwrite(&matrix->column_amt, sizeof(int), 1, file);

    for (int i=0; i<matrix->row_amt; i++) {
        Node* node = matrix->rows[i];

        while (node) {
            fwrite(&node->value, sizeof(float), 1, file);
            fwrite(&node->row, sizeof(int), 1, file);
            fwrite(&node->column, sizeof(int), 1, file);

            node = node->next_row;
        }
    }
    fwrite(&aux, sizeof(float), 1, file);

    fclose(file);
}

// O(n) * O(n) = O(n2) le todos os valores da matriz e realiza o add
Matrix* matrix_read_binary(char* file_path) {
    int row_amt, column_amt;
    FILE* file = fopen(file_path, "rb");

    fread(&row_amt, sizeof(float), 1, file);
    fread(&column_amt, sizeof(float), 1, file);
    Matrix* matrix = matrix_create(row_amt, column_amt);
    int row, column;
    float value;

    fread(&value, sizeof(float), 1, file);

    while (value != 0 && !feof(file)) {
        fread(&row, sizeof(int), 1, file);
        fread(&column, sizeof(int), 1, file);
        matrix_add(matrix, value, row, column);
        fread(&value, sizeof(float), 1, file);
    }
    fclose(file);

    return matrix;
}


// O(1) tempo constante
void node_destroy(Node* node) {
    free(node);
}
// O(n2) iterando por todos os elementos da matriz 
void matrix_destroy(Matrix* matrix) {
    for (int i=0; i<matrix->row_amt; i++) {
        Node* node = matrix->rows[i];
        Node* next;
        while (node) {
            next = node->next_row;
            node_destroy(node);
            node = next;
        }
    }

    free(matrix->rows);
    free(matrix->columns);
    free(matrix);
}