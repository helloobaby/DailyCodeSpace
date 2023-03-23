#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include "decision_tree.h"

struct CompareResult {
  double distance;
  enum classfy label;
};

struct CompareResult kArray[135];
int SearchSortCompareFunction(void const* a, void const*b) {
  struct CompareResult* aa = a;
  struct CompareResult* bb = b;
  if (aa->distance > bb->distance)
    return 1;
  else
    return -1;
}

int main() {
  struct Iris* dataset = create_data_set();
  struct Iris* test_dataset = create_test_data_set();
  int correct = 0;

  for (int j = 0; j < 15; j++) {
    for (int i = 0; i < 135; i++) {
      kArray[i].distance = computedistance(i, j, dataset, test_dataset);
      kArray[i].label = dataset[i].label;
    }
    qsort(kArray, 135, sizeof(struct CompareResult), SearchSortCompareFunction);
    int k = 10;

    int count_A = 0;
    int count_B = 0;
    int count_C = 0;

    for (int i = 0; i < k; i++) {
      if (kArray[i].label == A) count_A++;
      if (kArray[i].label == B) count_B++;
      if (kArray[i].label == C) count_C++;
    }

    // 判断正确样本数
    if (j < 5 && (count_A > count_B) && (count_A > count_C)) correct++;
    if ((j>=5&&j<10) && (count_B > count_A) && (count_B > count_C)) correct++;
    if (j >10 && (count_C > count_B) && (count_C > count_A)) correct++;
  }

  log("correct : %d test samples : %d\n", correct, 15);



  return 0;
}