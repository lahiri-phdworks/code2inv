#include <30.h>
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

#define INV(x) PHI

// COMMENT : loopcheck template
void loopcheck(int x)
{
  char buffer[30];
  fprintf(stderr, "Loop : %s : %d\n", "x", x);
  aflcrash(INV(x));
}
// COMMENT : postcheck template
void post(int x)
{
  char buffer[30];
  fprintf(stderr, "Post : %s : %d\n", "x", x);
  aflcrash(INV(x));
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

  scanf("%d", &x);
  freopen("loopmodels.txt", "w", stderr);

  // pre-conditions
  (x = 100);

  // loopcond : (x > 0)
  // loop-check program
  assume(INV(x));
  assume((x > 0));
  // loop body
  {
    {
      (x = (x - 1));
    }
  }
  loopcheck(x);
}
