#include <stdio.h>
#include <malloc.h>

int main() {
    int array1[4];
    int *it;
    array1[0] = -1;
    array1[1] = -12;
    array1[2] = -123;
    array1[3] = -1234;
    it = array1;
    printf("%s\n", "=== 1 ===");
    for (int i = 0; i < 4; i++) {
        printf("%d\t", *it);
        it++;
    }
    int *array2 = (int*)malloc((4) * sizeof(int));
    array2[0] = -1;
    array2[1] = -12;
    array2[2] = -123;
    array2[3] = -1234;
    printf("\n%s\n", "=== 2 ===");
    for (int i = 0; i < 4; i++) {
        printf("%d\t", array2[i]);
    }
    free(array2);
    return 0;
}
