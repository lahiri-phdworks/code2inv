#include <95.h>
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

  scanf("%d", &i);
  scanf("%d", &y);
  freopen("loopmodels.txt", "w", stderr);

  // pre-conditions
  (j = 0);
  (i = 0);
  (y = 1);

  // loopcond : (i <= x)
  // loop-check program
  assume(INV(i, j, x, y));
  assume((i <= x));
  // loop body
  {
    {
      (i = (i + 1));
      (j = (j + y));
    }
  }
  loopcheck(i, j, x, y);
}
