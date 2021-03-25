#include <1.h>
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

  freopen("loopmodels.txt", "w", stderr);

  // variable declarations
  int x;
  int y;

  // pre-conditions
  scanf("%d", &y);
  (x = 1);
  (y = 0);

  // loop body
  assume(INV(x, y));
  assume((y < 100000));
  (x = (x + y));
  (y = (y + 1));
  loopcheck(x, y);
}
