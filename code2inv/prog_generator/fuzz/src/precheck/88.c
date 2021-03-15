#include <88.h>
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

#define INV(lock, x, y) PHI

// TODO : Automate generation of this snippet
void precheck(int lock, int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d\n", "lock", lock, "x", x, "y", y);
  aflcrash(INV(lock, x, y));
}

// TODO : Automate generation of this snippet
void loopcheck(int lock, int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d\n", "lock", lock, "x", x, "y", y);
  aflcrash(INV(lock, x, y));
}

// TODO : Automate generation of this snippet
void postcheck(int lock, int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d\n", "lock", lock, "x", x, "y", y);
  aflcrash(INV(lock, x, y));
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
  int lock;
  int x;
  int y;

  freopen("premodels.txt", "w", stderr);
  scanf("%d", &x);

  // pre-conditions
  (y = (x + 1));
  (lock = 0);

  assume((y == (x + 1)));
  assume((lock == 0));

  precheck(lock, x, y);
}
