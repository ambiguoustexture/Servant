#include "sort.h"
#include <bits/stdc++.h>

using std::swap;

void selectSort(int *array, int len) {
  for (int j = 0; j < len - 1; j++)
    for (int i = j + 1; i < len; i++)
      if (array[j] > array[i])
        swap(array[i], array[j]);
}
