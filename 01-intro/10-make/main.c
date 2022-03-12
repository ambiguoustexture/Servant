#include "head.h"
#include <stdio.h>

int main() {

  int a = 20;
  int b = 42;
  printf("a = %d, b = %d\n", a, b);
  printf("a + b = %d\n", add(a, b));
  printf("a - b = %d\n", subtract(a, b));
  printf("a * b = %d\n", multiply(a, b));
  printf("a / b = %f\n", divide(a, b));
  return 0;
}
