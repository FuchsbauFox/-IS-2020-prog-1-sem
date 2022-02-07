#include <stdio.h>
#include <malloc.h>

int main() {
    int digits = 0, letters = 0;
    char str[255];
    fgets(str, 255, stdin);
    for (int i = 0; i < 255; i++) {
        if (str[i] == '\n') {
            break;
        }
        if ((int)str[i] >= 48 && (int)str[i] <= 57) {
            digits++;
        }
        if ((int)str[i] >= 65 && (int)str[i] <= 90 || (int)str[i] >= 97 && (int)str[i] <= 122) {
            letters++;
        }
    }
    printf("Number of digits in string: %d\n", digits);
    printf("Number of Latin characters in string: %d\n", letters);

    int n;
    scanf_s("%d", &n);
    int *boolean = (int*)malloc((n) * sizeof(int));
    for (int i = 2; i < n; i++){
        boolean[i] = 1;
    }
    for (int i = 2; i <= n; i++) {
        if (boolean[i] == 1) {
            for (int j = i * i; j <= n; j += i) {
                boolean[j] = 0;
            }
        }
    }
    printf("Prime numbers <= n:\n");
    for (int i = 2; i < n; i++) {
        if (boolean[i] == 1) {
            printf("%d\n", i);
        }
    }
    return 0;
}
