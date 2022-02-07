#include <stdio.h>

int main() {
    char str1[64], str2[64], buffer[64];
    int n, j = 0, flag = 0;
    fgets(str1, 64, stdin);
    fgets(str2, 64, stdin);
    printf("%s", "n=");
    scanf_s("%d", &n);
    for (int i = 0; i < 64; i++) {
        if (str1[i] == '\n' || flag == 1) {
            flag = 1;
            if (j < n) {
                buffer[i] = str2[j];
                j++;
            } else {
                buffer[i] = '\0';
                break;
            }
        } else {
            buffer[i] = str1[i];
        }
    }
    printf("%s\n%s", buffer, "n=");

    scanf_s("%d", &n);
    for (int i = 0; i < n; i++) {
        if (str1[i] != str2[i]) {
            flag = 0;
            break;
        }
    }
    printf("%s%s", (flag == 1) ? "First n char of the string are equal" : "First n char of the string are NOT equal", "\nsymbol=");

    int it1 = -1;
    int it2 = -1;
    char symbol;
    getchar();
    scanf_s("%c", &symbol);
    for (int i = 0; i < 64; i++) {
        if (str1[i] == symbol) {
            it1 = i + 1;
        }
        if (str2[i] == symbol) {
            it2 = i + 1;
        }
    }
    if (it1 != -1) {
        printf("%s%d\n", "Last appearance in the string1 of the symbol: ", it1);
    }
    else {
        printf("%s\n", "This char is not in the string1");
    }
    if (it2 != -1) {
        printf("%s%d\n", "Last appearance int the string2 of the symbol: ", it2);
    }
    else {
        printf("%s\n", "This char is not in the string2");
    }

    int size = 1;
    for (int i = 0; i < 64; i++) {
        if (str1[i] == '\n') {
            break;
        }
        for (int k = 0; k < 64; k++) {
            if (str1[i] == str2[k]) {
                size = 0;
                break;
            }
        }
        size++;
    }
    printf("Length of the segment string1 containing char from the set string2: %d\n", size - 1);

    for (int i = 0; i < 64; i++) {
        if (str1[i] == '\n') {
            break;
        }
        flag = 1;
        for (int k = 0; k < 64; k++) {
            if (str1[i] == str2[k]) {
                flag = 0;
                break;
            }
        }
        if (flag == 1) {
            printf("%c", str1[i]);
        }
        else {
            printf("\n");
        }
    }
    return 0;
}
