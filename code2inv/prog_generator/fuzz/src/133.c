#include <133.h>
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

#define INV(n, x) PHI

// TODO : Automate generation of this snippet
void loopcheck(int n, int x)
{
  char buffer[30];
  fprintf(stderr, "Loop : %s : %d, %s : %d\n", "n", n, "x", x);
  aflcrash(INV(n, x));
}

// TODO : Automate generation of this snippet
void postcheck(int n, int x)
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

  freopen("loopmodels.txt", "w", stderr);

  // pre-conditions
  (x = 0);
  scanf("%d", &n);
  assume((n >= 0));

  // loop body
  assume(INV(n, x));
  assume((x < n));
  (x = (x + 1));
  loopcheck(n, x);
}
