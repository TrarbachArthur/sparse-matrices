#ifndef MATRIX_H
#define MATRIX_H

typedef struct node {
    int row, column;
    float value;
    struct node *next_row, *next_column;
} Node;

typedef struct matrix {
    int row_size, column_size;
    Node **rows, **columns;
} Matrix;

Node* node_create(float value, int row, int column);
Matrix* matrix_create(int row_size, int column_size);

void matrix_add(Matrix* matrix, float value, int row, int column);

void node_destroy(Node* node);
void matrix_destroy(Matrix* matrix);

#endif