#include <stdio.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

enum OS {
    SYMBIAN,
    EMBEDDED_LINUX,
    WINDOWS_CE,
    VXWORKS,
    QNX
};

struct Figure {
    int x, y, a, b, r, S, P, L;
};

struct byte {
    unsigned NumLock : 1;
    unsigned CapsLock : 1;
    unsigned ScrollLock : 1;
};

union Byte {
    unsigned char value;
    struct byte bitfield;
};

union test {
    char a;
    int b;
};

int main() {
    printf("=== 1 ===\n");
    enum OS a;
    a = SYMBIAN;
    printf("a = %d\n", a);

    printf("\n=== 2 ===\n");
    struct Figure circle;
    circle.r = 5;
    printf("L = %f\n", 2 * M_PI * circle.r);

    printf("\n=== 3 ===\nvalue:");
    union Byte keyboard;
    scanf_s("%x", &keyboard.value);
    printf ("%i%i%i", keyboard.bitfield.NumLock, keyboard.bitfield.CapsLock, keyboard.bitfield.ScrollLock);


    union test t;
    t.b = 257;

    printf("\n%d", t.b);
    return 0;
}
