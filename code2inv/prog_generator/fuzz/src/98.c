#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <ssum.h>

#define fail(cond) \
  if (!cond)       \
    assert(0);

#define exitpass(cond) \
  if (!cond)           \
    exit(-1);

#define assume(cond) \
  if (!cond)         \
    exit(0);

#define INV(sum, n, i, y) PHI

// TODO : Automate generation of this snippet
void precheck(long long int sum, int n, int i, int y, int i2)
{
  char buffer[30];
  fprintf(stderr, "Pre : %s : %lld, %s : %d, %s : %d, %s : %d, %s : %d\n", "sum", sum, "n", n, "i", i, "y", y, "i2", i2);
  fail(INV(sum, n, i, y));
}

// TODO : Automate generation of this snippet
void loopcheck(long long int sum, int n, int i, int y, int i2)
{
  char buffer[30];
  fprintf(stderr, "Loop : %s : %lld, %s : %d, %s : %d, %s : %d, %s : %d\n", "sum", sum, "n", n, "i", i, "y", y, "i2", i2);
  fail(INV(sum, n, i, y));
}

// TODO : Automate generation of this snippet
void postcheck(long long int sum, int n, int i, int y, int i2)
{
  char buffer[30];
  fprintf(stderr, "Post : %s : %lld, %s : %d, %s : %d, %s : %d, %s : %d\n", "sum", sum, "n", n, "i", i, "y", y, "i2", i2);
  assume(INV(sum, n, i, y));
}

int main()
{
  // variable declarations
  int i;
  int j;
  int x;
  int y;

  scanf("%d", &x);
  scanf("%d", &y);

  // pre-conditions
  (j = 0);
  (i = 0);
  (y = 2);

  pre_check(i, j, x, y);
  // loop body
  while ((i <= x))
  {
    {
      (i = (i + 1));
      (j = (j + y));
    }
    loop_check(i, j, x, y);
  }

  // post-condition
  post_check(i, j, x, y);
  if ((i != j))
    assert((y != 1));
}
