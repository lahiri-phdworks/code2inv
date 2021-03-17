#include <100.h>
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

#define INV(n, x, y) PHI

// COMMENT : loopcheck template
void loopcheck(int n, int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d\n", "n", n, "x", x, "y", y);
  aflcrash(INV(n, x, y));
}
// COMMENT : postcheck template
void post(int n, int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d\n", "n", n, "x", x, "y", y);
  aflcrash(INV(n, x, y));
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
  int n;
  int x;
  int y;

  scanf("%d", &n);
  freopen("loopmodels.txt", "w", stderr);

  // pre-conditions
  assume((-10000 <= n && n <= 10000));
  (x = n);
  (y = 0);

  // loopcond : (x > 0)
  // loop-check program
  assume(INV(n, x, y));
  assume((x > 0));
  // loop body
  {
    {
      (y = (y + 1));
      (x = (x - 1));
    }
  }
  loopcheck(n, x, y);
}
