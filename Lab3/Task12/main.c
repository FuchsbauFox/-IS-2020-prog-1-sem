#include <stdio.h>

int main(int argc, char *argv[]) {
    int first_val, second_val;
    char *Array[20];
    FILE *new_output;
    if (argc < 4){
        printf("ERROR: Not enough arguments");
        return 0;
    }
    if (argc > 4){
        printf("ERROR: Too many arguments");
        return 0;
    }
    sscanf_s(argv[1], "%d", &first_val);
    sscanf_s(argv[2], "%d", &second_val);
    if ((new_output = freopen(argv[3], "w", stdout)) == NULL){
        printf("ERROR: Wrong open of output stream.");
        return 0;
    }
    printf("Answer: %d", first_val+second_val);
    return 0;
}