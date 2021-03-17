#include <129.h>
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

#define INV(x, y, z1, z2, z3) PHI

// TODO : Automate generation of this snippet
void loopcheck(int x, int y, int z1, int z2, int z3)
{
  char buffer[30];
  fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "x", x, "y", y, "z1", z1, "z2", z2, "z3", z3);
  aflcrash(INV(x, y, z1, z2, z3));
}

// TODO : Automate generation of this snippet
void postcheck(int x, int y, int z1, int z2, int z3)
{
  char buffer[30];
  fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "x", x, "y", y, "z1", z1, "z2", z2, "z3", z3);
  aflcrash(INV(x, y, z1, z2, z3));
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

  // pre-conditions
  (x = 1);
  scanf("%d", &y);

  // loop body
  assume(INV(x, y, z1, z2, z3));
  assume((x < y));
  (x = (x + x));
  loopcheck(x, y, z1, z2, z3);
}
