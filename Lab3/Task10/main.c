#include <stdio.h>

int NOD(int ina, int inb) {
    while (ina != 0 && inb != 0) {
        if (ina > inb) {
            ina = ina % inb;
        }
        else {
            inb = inb % ina;
        }
    }
    return (ina + inb);
}

int NOK(int ina, int inb) {
    return (ina * inb / NOD(ina, inb));
}

int Sum(int number) {
    if (number / 10 != 0) {
        return (number % 10 + Sum(number / 10));
    }
    else {
        return (number % 10);
    }
}

int main() {
    int a, b;
    scanf_s("%d%d", &a, &b);
    printf("NOD = %d\n", NOD(a, b));
    printf("NOK = %d\n", NOK(a, b));

    int num;
    scanf_s("%d", &num);
    printf("Sum = %d", Sum(num));
    return 0;
}
