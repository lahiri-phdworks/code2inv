#include <89.h>
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

#define INV(lock, v1, v2, v3, x, y) PHI

// COMMENT : precheck template
void precheck(int lock, int v1, int v2, int v3, int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "lock", lock, "v1", v1, "v2", v2, "v3", v3, "x", x, "y", y);
  aflcrash(INV(lock, v1, v2, v3, x, y));
}
// COMMENT : loopcheck template
void loopcheck(int lock, int v1, int v2, int v3, int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "lock", lock, "v1", v1, "v2", v2, "v3", v3, "x", x, "y", y);
  aflcrash(INV(lock, v1, v2, v3, x, y));
}
// COMMENT : postcheck template
void post(int lock, int v1, int v2, int v3, int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "lock", lock, "v1", v1, "v2", v2, "v3", v3, "x", x, "y", y);
  aflcrash(INV(lock, v1, v2, v3, x, y));
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
  int v1;
  int v2;
  int v3;
  int x;
  int y;

  scanf("%d", &y);
  freopen("postmodels.txt", "w", stderr);

  // pre-conditions
  assume((-10000 <= y && y <= 10000));
  (x = y);
  (lock = 1);

  // post-check program
  assume(INV(lock, v1, v2, v3, x, y));
  assume(!(x != y));
  fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", lock, v1, v2, v3, x, y);
  // post-condition
  assert((lock == 1));
}
