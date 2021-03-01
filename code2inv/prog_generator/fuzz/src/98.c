#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <base.h>
#include <98.h>

#define INV(i, j, x, y) PHI

void pre_check(int i, int j, int x, int y)
{
  char buffer[30];
  logModel(buffer, "%c : %d, %c : %d, %c : %d, %c : %d", "i", i, "j", j, "x", x, "y", y);
  __assert(buffer, INV(i, j, x, y), -1);
}

void loop_check(int i, int j, int x, int y)
{
  char buffer[30];
  logModel(buffer, "%c : %d, %c : %d, %c : %d, %c : %d", "i", i, "j", j, "x", x, "y", y);
  __assert(buffer, INV(i, j, x, y), -2);
}

void post_check(int i, int j, int x, int y)
{
  assume(INV(i, j, x, y));
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
