#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

#include "tests/convolution.c"
#include "tests/swap.c"
#include "tests/sum.c"
#include "tests/get.c"
#include "tests/multiply_escalar.c"
#include "tests/multiply_matrix.c"
#include "tests/multiply_point.c"
#include "tests/slice.c"
#include "tests/transpose.c"

int main(void) {
    int choice = 0;
    printf("Welcome to the linked matrix tester!\n\n");
    
    do {
        printf("\nThose are the option for testing the data structure:\n\n");
        printf("1 - Get value based on the coordinates\n2 - Sum matrices\n3 - Multiply by escalar\n");
        printf("4 - Multiply matrices\n5 - Multiply point-by-point\n6 - Swap\n7 - Slice\n8 - Transpose\n");
        printf("9 - Convolution (keep in mind it also tests binary saving and reading)\n0 - Exit\n\n");

        printf("Please enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                get();
                break;
            case 2:
                sum();
                break;
            case 3:
                multEscalar();
                break;
            case 4:
                multMatrix();
                break;
            case 5:
                multPoint();
                break;
            case 6:
                swap();
                break;
            case 7:
                slice();
                break;
            case 8:
                transpose();
                break;
            case 9:
                convolution();
                break;
        }
    } while (choice != 0);
    
    return 0;
}