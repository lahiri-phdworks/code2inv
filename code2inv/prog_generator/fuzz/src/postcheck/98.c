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
void precheck(int i, int j, int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "j", j, "x", x, "y", y);
  aflcrash(INV(i, j, x, y));
}

// TODO : Automate generation of this snippet
void loopcheck(int i, int j, int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "j", j, "x", x, "y", y);
  aflcrash(INV(i, j, x, y));
}

// TODO : Automate generation of this snippet
void postcheck(int i, int j, int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "j", j, "x", x, "y", y);
  aflcrash(INV(i, j, x, y));
}

int main()
{
  // variable declarations
  int i;
  int j;
  int x;
  int y;

  freopen("postmodels.txt", "w", stderr);

  scanf("%d", &x);
  scanf("%d", &y);

  // pre-conditions
  (j = 0);
  (i = 0);
  (y = 2);

  assume((x >= 0 && x <= 1000));
  assume((y >= 0 && y <= 1000));

  // post-condition
  assume(INV(i, j, x, y));
  assume(!(i <= x));

  if ((i != j))
  {
    char buffer[30];
    fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "j", j, "x", x, "y", y);
    assert((y != 1));
  }
}
