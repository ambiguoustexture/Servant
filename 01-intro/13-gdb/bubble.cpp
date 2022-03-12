#include "sort.h"
#include <bits/stdc++.h>
#include <tuple>

using std::swap;

void bubbleSort(int *array, int len) {
  for (int i = 0; i < len - 1; i++)
    for (int j = 0; j < len - i - 1; j++)
      if (array[j] > array[j + 1])
        swap(array[j], array[j + 1]);
}
