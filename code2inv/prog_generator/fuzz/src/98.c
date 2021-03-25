#include <98.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define aflcrash(cond) \
  if (!cond)           \
    assert(0);

// Guide AFL to proper values
// exit(0) is not a crash
#define assume(cond) \
  if (!cond)         \
    exit(0);

#define INV(i, j, x, y) PHI

// TODO : Automate generation of this snippet
void loopcheck(int i, int j, int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "j", j, "x", x, "y", y);
  aflcrash(INV(i, j, x, y));
}

// TODO : Automate generation of this snippet
void postcheck(int i, int j, int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "j", j, "x", x, "y", y);
  aflcrash(INV(i, j, x, y));
}

int choices[] = {1, -1, 1, -1, 1, 1, -1, 1, -2, -1, 0, 0, 0, 1, 1, -1, 1, 0, 1, -1, 1, 1, 2, 1};
int unknown()
{
  int nums = sizeof(choices) / sizeof(choices[0]);
  return choices[(rand() % nums) - 1];
}

int main()
{
  // variable declarations
  int i;
  int j;
  int x;
  int y;

  freopen("loopmodels.txt", "w", stderr);

  scanf("%d", &x);
  scanf("%d", &y);

  // pre-conditions
  (j = 0);
  (i = 0);
  (y = 2);

  // loop body
  assume(INV(i, j, x, y));
  assume((i <= x));
  (i = (i + 1));
  (j = (j + y));
  loopcheck(i, j, x, y);
}
