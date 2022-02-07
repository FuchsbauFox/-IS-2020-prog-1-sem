#include <stdio.h>

int main() {
    int array[] = {123, 123, 123, 123, 456, 321, 1};
    int matrix1[2][2] = {{1, 2},
                         {3, 4}
    };
    int matrix2[2][2] = {{1, 0},
                         {0, 1}
    };
    int matrix[2][2];
    printf("%s\n", "=== 1 ===");
    for (int i = 0; i < 7; i++) {
        printf("%d\t", array[i]);
    }
    printf("\n%s\n", "=== 2 ===");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            matrix[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                matrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}
