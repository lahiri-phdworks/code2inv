#include <75.h>
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

#define INV(c, x1, x2, x3, y, z) PHI

// TODO : Automate generation of this snippet
void loopcheck(int c, int x1, int x2, int x3, int y, int z)
{
  char buffer[30];
  fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "c", c, "x1", x1, "x2", x2, "x3", x3, "y", y, "z", z);
  aflcrash(INV(c, x1, x2, x3, y, z));
}

// TODO : Automate generation of this snippet
void postcheck(int c, int x1, int x2, int x3, int y, int z)
{
  char buffer[30];
  fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "c", c, "x1", x1, "x2", x2, "x3", x3, "y", y, "z", z);
  aflcrash(INV(c, x1, x2, x3, y, z));
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
  int c;
  int x1;
  int x2;
  int x3;
  int y;
  int z;

  freopen("loopmodels.txt", "w", stderr);
  scanf("%d", &y);

  // pre-conditions
  assume((y >= 127));
  (c = 0);
  (z = (36 * y));

  // loop body
  assume(INV(c, x1, x2, x3, y, z));
  // loop-cond : unknown()
  if ((c < 36))
  {
    (z = (z + 1));
    (c = (c + 1));
  }
  loopcheck(c, x1, x2, x3, y, z);
}
