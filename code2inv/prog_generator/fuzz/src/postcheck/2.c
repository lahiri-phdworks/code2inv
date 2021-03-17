#include <2.h>
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
void precheck(int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Pre : %s : %d, %s : %d\n", "x", x, "y", y);
  aflcrash(INV(x, y));
}

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

int main()
{

  freopen("postmodels.txt", "w", stderr);

  // variable declarations
  int x;
  int y;

  // pre-conditions
  scanf("%d", &y);
  (x = 1);
  (y = 0);

  // post-condition
  assume(INV(x, y));
  assume(!(y < 1000));

  char buffer[30];
  fprintf(stderr, "Post : %s : %d, %s : %d\n", "x", x, "y", y);
  assert((x >= y));
}
