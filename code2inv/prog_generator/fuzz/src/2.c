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
  fprintf(stderr, "Pre : %s : %d, %s : %d\n", "x", x, "y", y);
  aflcrash(INV(x, y));
}

// TODO : Automate generation of this snippet
void postcheck(int x, int y)
{
  char buffer[30];
  fprintf(stderr, "Pre : %s : %d, %s : %d\n", "x", x, "y", y);
  aflcrash(INV(x, y));
}

int main()
{

  freopen("models.txt", "w", stderr);

  // variable declarations
  int x;
  int y;

  // pre-conditions
  (x = 1);
  (y = 0);

  scanf("%d", &y);
  assume((y > 0 && y <= 1000))

      precheck(x, y);

  // loop body
  while ((y < 1000))
  {
    {
      (x = (x + y));
      (y = (y + 1));
    }
    loopcheck(x, y);
  }
  // post-condition
  postcheck(x, y);
  assert((x >= y));
}
