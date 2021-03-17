#include <54.h>
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

#define INV(c, n, v1, v2, v3) PHI

// COMMENT : loopcheck template
void loopcheck(int c, int n, int v1, int v2, int v3)
{
  char buffer[30];
  fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "c", c, "n", n, "v1", v1, "v2", v2, "v3", v3);
  aflcrash(INV(c, n, v1, v2, v3));
}
// COMMENT : postcheck template
void post(int c, int n, int v1, int v2, int v3)
{
  char buffer[30];
  fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "c", c, "n", n, "v1", v1, "v2", v2, "v3", v3);
  aflcrash(INV(c, n, v1, v2, v3));
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
  int c;
  int n;
  int v1;
  int v2;
  int v3;

  scanf("%d", &c);
  scanf("%d", &n);
  freopen("loopmodels.txt", "w", stderr);

  // pre-conditions
  assume((-10000 <= n && n <= 10000));
  (c = 0);
  assume((n > 0));

  // loopcond : (unknown())
  // loop-check program
  assume(INV(c, n, v1, v2, v3));
  // loop body
  {
    {
      if (unknown())
      {
        if ((c > n))
        {
          (c = (c + 1));
        }
      }
      else
      {
        if ((c == n))
        {
          (c = 1);
        }
      }
    }
  }
  loopcheck(c, n, v1, v2, v3);
}
