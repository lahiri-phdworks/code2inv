#include <124.h>
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

#define INV(i, j, x, y) PHI

// COMMENT : precheck template
void precheck(int i, int j, int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "j", j, "x", x, "y", y);
  aflcrash(INV(i, j, x, y));
}
// COMMENT : loopcheck template
void loopcheck(int i, int j, int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "j", j, "x", x, "y", y);
  aflcrash(INV(i, j, x, y));
}
// COMMENT : postcheck template
void post(int i, int j, int x, int y)
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

  scanf("%d", &x);
  scanf("%d", &y);
  freopen("postmodels.txt", "w", stderr);

  // pre-conditions
  assume((-10000 <= y && y <= 10000));
  assume((-10000 <= x && x <= 10000));
  (i = x);
  (j = y);

  // post-check program
  assume(INV(i, j, x, y));
  assume(!(x != 0));
  fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d\n", i, j, x, y);
  // post-condition
  if ((i == j))
    assert((y == 0));
}
