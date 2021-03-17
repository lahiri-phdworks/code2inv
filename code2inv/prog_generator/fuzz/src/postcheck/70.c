#include <70.h>
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

#define INV(n, v1, v2, v3, x, y) PHI

// COMMENT : precheck template
void precheck(int n, int v1, int v2, int v3, int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "n", n, "v1", v1, "v2", v2, "v3", v3, "x", x, "y", y);
  aflcrash(INV(n, v1, v2, v3, x, y));
}
// COMMENT : loopcheck template
void loopcheck(int n, int v1, int v2, int v3, int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "n", n, "v1", v1, "v2", v2, "v3", v3, "x", x, "y", y);
  aflcrash(INV(n, v1, v2, v3, x, y));
}
// COMMENT : postcheck template
void post(int n, int v1, int v2, int v3, int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "n", n, "v1", v1, "v2", v2, "v3", v3, "x", x, "y", y);
  aflcrash(INV(n, v1, v2, v3, x, y));
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
  int v1;
  int v2;
  int v3;
  int x;
  int y;

  scanf("%d", &n);
  scanf("%d", &v1);
  freopen("postmodels.txt", "w", stderr);

  // pre-conditions
  (x = 1);

  // post-check program
  assume(INV(n, v1, v2, v3, x, y));
  assume(!(x <= n));
  // post-condition
  if (n > 0)
  {
    fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", n, v1, v2, v3, x, y);
    assert(y < n);
  }
}
