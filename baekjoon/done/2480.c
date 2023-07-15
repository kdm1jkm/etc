#include <stdio.h>

void setRead() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
}

int solve(int *counts) {
  int max = 0;
  for (int i = 0; i < 6; i++) {
    if (counts[i] == 3)
      return 11000 + i * 1000;
    else if (counts[i] == 2)
      return 1100 + 100 * i;
    else if (counts[i] == 1)
      max = i;
  }
  return 100 + max * 100;
}

int main(void) {
  setRead();
  int a, b, c;
  scanf("%d %d %d", &a, &b, &c);

  int counts[6] = {0, 0, 0, 0, 0, 0};
  counts[a - 1] += 1;
  counts[b - 1] += 1;
  counts[c - 1] += 1;

  printf("%d\n", solve(counts));

  return 0;
}
