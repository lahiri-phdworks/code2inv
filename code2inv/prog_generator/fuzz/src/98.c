#include <98.h>
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

#define INV(i, j, x, y) PHI

// TODO : Automate generation of this snippet
void precheck(long long int i, int j, int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "j", j, "x", x, "y", y);
  aflcrash(INV(i, j, x, y));
}

// TODO : Automate generation of this snippet
void loopcheck(long long int i, int j, int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "j", j, "x", x, "y", y);
  aflcrash(INV(i, j, x, y));
}

// TODO : Automate generation of this snippet
void postcheck(long long int i, int j, int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "j", j, "x", x, "y", y);
  aflcrash(INV(i, j, x, y));
}

int main()
{
  // variable declarations
  int i;
  int j;
  int x;
  int y;

  freopen("models.txt", "w", stderr);

  scanf("%d", &x);
  scanf("%d", &y);

  // pre-conditions
  (j = 0);
  (i = 0);
  (y = 2);

  assume((x >= 0 && x <= 1000))
      assume((y >= 0 && y <= 1000))
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
