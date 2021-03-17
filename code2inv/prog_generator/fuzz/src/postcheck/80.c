#include <80.h>
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

#define INV(i, x, y, z1, z2, z3) PHI

// COMMENT : precheck template
void precheck(int i, int x, int y, int z1, int z2, int z3)
{
  char buffer[30];
  fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "x", x, "y", y, "z1", z1, "z2", z2, "z3", z3);
  aflcrash(INV(i, x, y, z1, z2, z3));
}
// COMMENT : loopcheck template
void loopcheck(int i, int x, int y, int z1, int z2, int z3)
{
  char buffer[30];
  fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "x", x, "y", y, "z1", z1, "z2", z2, "z3", z3);
  aflcrash(INV(i, x, y, z1, z2, z3));
}
// COMMENT : postcheck template
void post(int i, int x, int y, int z1, int z2, int z3)
{
  char buffer[30];
  fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "x", x, "y", y, "z1", z1, "z2", z2, "z3", z3);
  aflcrash(INV(i, x, y, z1, z2, z3));
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
  int x;
  int y;
  int z1;
  int z2;
  int z3;

  scanf("%d", &y);
  freopen("postmodels.txt", "w", stderr);

  // pre-conditions
  assume((-10000 <= y && y <= 10000));
  (i = 0);
  assume((x >= 0));
  assume((y >= 0));
  assume((x >= y));

  // post-check program
  assume(INV(i, x, y, z1, z2, z3));
  assume(!(unknown()));
  fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", i, x, y, z1, z2, z3);
  // post-condition
  if ((i < y))
    assert((i < x));
}
