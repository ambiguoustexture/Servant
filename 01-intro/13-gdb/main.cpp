#include "sort.h"
#include <iostream>

using namespace std;

int main() {

  int array[] = {12, 27, 55, 22, 67};
  int len = sizeof(array) / sizeof(int);

  bubbleSort(array, len);

  cout << "bubble sorted array: \n";
  for (int i = 0; i < len; i++) {
    cout << array[i] << " ";
  }
  cout << endl;

  int array1[] = {25, 47, 36, 80, 11};
  len = sizeof(array1) / sizeof(int);

  selectSort(array1, len);

  cout << "selective sorted array: \n";
  for (int i = 0; i < len; i++) {
    cout << array1[i] << " ";
  }
  cout << endl;

  return 0;
}
