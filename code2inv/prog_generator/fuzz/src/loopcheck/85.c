#include <85.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define aflcrash(cond) \
  if (!cond)           \
    assert(0);

#define assume(cond) \
  if (!cond)         \
    exit(0);

#define INV(x, y, z1, z2, z3) PHI

// COMMENT : loopcheck template
void loopcheck(int x, int y, int z1, int z2, int z3)
{
  char buffer[30];
  fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "x", x, "y", y, "z1", z1, "z2", z2, "z3", z3);
  aflcrash(INV(x, y, z1, z2, z3));
}
// COMMENT : postcheck template
void post(int x, int y, int z1, int z2, int z3)
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

  scanf("%d", &y);
  freopen("loopmodels.txt", "w", stderr);

  // pre-conditions
  assume((-10000 <= y && y <= 10000));
  (x = -15000);

  // loopcond : (x < 0)
  // loop-check program
  assume(INV(x, y, z1, z2, z3));
  assume((x < 0));
  // loop body
  {
    {
      (x = (x + y));
      (y = (y + 1));
    }
  }
  loopcheck(x, y, z1, z2, z3);
}
