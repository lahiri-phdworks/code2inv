#include <2.h>
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

#define INV(x, y) PHI

// COMMENT : precheck template
void precheck(int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Pre : %s : %d, %s : %d\n", "x", x, "y", y);
  aflcrash(INV(x, y));
}

// COMMENT : loopcheck template
void loopcheck(int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Loop : %s : %d, %s : %d\n", "x", x, "y", y);
  aflcrash(INV(x, y));
}

// COMMENT : postcheck template
void post(int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Post : %s : %d, %s : %d\n", "x", x, "y", y);
  aflcrash(INV(x, y));
}

int main()
{

  freopen("premodels.txt", "w", stderr);

  // variable declarations
  int x;
  int y;

  // pre-conditions
  scanf("%d", &y);
  (x = 1);
  (y = 0);

  assume((x == 1));
  assume((y == 0));

  precheck(x, y);
}
