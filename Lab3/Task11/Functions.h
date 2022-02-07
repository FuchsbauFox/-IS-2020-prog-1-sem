#ifndef INC_2_FUNCTIONS_H
#define INC_2_FUNCTIONS_H

struct Figure {
    double x_a;
    double y_a;
    double x_b;
    double y_b;
    double x_c;
    double y_c;
    double P;
    double S;
};

void Area(struct Figure obj);
void Perimeter(struct Figure obj);

#endif //INC_2_FUNCTIONS_H
