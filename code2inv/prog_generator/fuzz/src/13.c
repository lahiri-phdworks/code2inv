#include <13.h>
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

#define INV(x, y) PHI

// TODO : Automate generation of this snippet
void loopcheck(int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Loop : %s : %d, %s : %d\n", "x", x, "y", y);
  aflcrash(INV(x, y));
}

// TODO : Automate generation of this snippet
void postcheck(int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Post : %s : %d, %s : %d\n", "x", x, "y", y);
  aflcrash(INV(x, y));
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
  int x;
  int y;
  int z1;
  int z2;
  int z3;

  freopen("loopmodels.txt", "w", stderr);
  scanf("%d", &x);
  scanf("%d", &y);

  // loop body
  assume(INV(x, y));
  // loop-cond : unknown()
  (x = (x + 2));
  (y = (y + 2));
  loopcheck(x, y);
}
