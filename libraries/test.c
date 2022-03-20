#include <stdio.h>

int add(int a, int b);
int sub(int a, int b);
float div(float a, float b);
void print_int(int a);
void print_float(float a);

int main() {
    int sum, difference;
    float quotient;
    sum = add(1, 2);
    difference = sub(10, 8);
    quotient = div(9, 2);

    printf("Sum = ");
    print_int(sum);
    printf("\n");

    printf("Difference = ");
    print_int(difference);
    printf("\n");

    printf("Quotient = ");
    print_float(quotient);
    printf("\n");

    return 0;
}