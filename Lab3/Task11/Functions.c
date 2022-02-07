#include "Functions.h"
#include <math.h>

double L(double x1, double y1, double x2, double y2) {
    return (pow(pow(x1 - x2, 2) + pow(y1 - y2, 2), 1/2));
}

void Area(struct Figure obj) {
    obj.S = pow(obj.P * (obj.P - L(obj.x_a, obj.y_a, obj.x_b, obj.y_b)) * (obj.P - L(obj.x_c, obj.y_c, obj.x_b, obj.y_b)) * (obj.P - L(obj.x_a, obj.y_a, obj.x_c, obj.y_c)), 1/2);
}

void Perimeter(struct Figure obj) {
    obj.P = L(obj.x_a, obj.y_a, obj.x_b, obj.y_b) + L(obj.x_c, obj.y_c, obj.x_b, obj.y_b) + L(obj.x_a, obj.y_a, obj.x_c, obj.y_c);
}
