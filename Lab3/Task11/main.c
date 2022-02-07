#include <stdio.h>
#include "Functions.h"

int main() {
    struct Figure IsoscelesTriangle;
    scanf_s("Ax = %lf", &IsoscelesTriangle.x_a);
    scanf_s("Ay = %lf", &IsoscelesTriangle.y_a);
    scanf_s("Bx = %lf", &IsoscelesTriangle.x_b);
    scanf_s("By = %lf", &IsoscelesTriangle.y_b);
    scanf_s("Cx = %lf", &IsoscelesTriangle.x_c);
    scanf_s("Cy = %lf", &IsoscelesTriangle.y_c);
    Perimeter(IsoscelesTriangle);
    Area(IsoscelesTriangle);
    printf("P = %lf\n", IsoscelesTriangle.P);
    printf("P = %lf\n", IsoscelesTriangle.S);
    return 0;
}
