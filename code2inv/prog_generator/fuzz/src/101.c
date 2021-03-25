#include <101.h>
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

#define INV(n, x) PHI

// COMMENT : loopcheck template
void loopcheck(int n, int x)
{
  char buffer[30];
  fprintf(stderr, "Loop : %s : %d, %s : %d\n", "n", n, "x", x);
  aflcrash(INV(n, x));
}
// COMMENT : postcheck template
void post(int n, int x)
{
  char buffer[30];
  fprintf(stderr, "Post : %s : %d, %s : %d\n", "n", n, "x", x);
  aflcrash(INV(n, x));
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

  scanf("%d", &n);
  freopen("loopmodels.txt", "w", stderr);

  // pre-conditions
  assume((-10000 <= n && n <= 10000));
  (x = 0);

  // loopcond : (x < n)
  // loop-check program
  assume(INV(n, x));
  assume((x < n));
  // loop body
  {
    {
      (x = (x + 1));
    }
  }
  loopcheck(n, x);
}
