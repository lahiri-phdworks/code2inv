#include <110.h>
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

#define INV(i, n, sn) PHI

// TODO : Automate generation of this snippet
void precheck(int i, int n, int sn)
{
  char buffer[30];
  fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d\n", "i", i, "n", n, "sn", sn);
  aflcrash(INV(i, n, sn));
}

// TODO : Automate generation of this snippet
void loopcheck(int i, int n, int sn)
{
  char buffer[30];
  fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d\n", "i", i, "n", n, "sn", sn);
  aflcrash(INV(i, n, sn));
}

// TODO : Automate generation of this snippet
void postcheck(int i, int n, int sn)
{
  char buffer[30];
  fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d\n", "i", i, "n", n, "sn", sn);
  aflcrash(INV(i, n, sn));
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
  int i;
  int n;
  int sn;

  // pre-conditions
  (sn = 0);
  (i = 1);
  scanf("%d", &n);

  assume((n >= 0 && n <= 10000))
      precheck(i, n, sn);

  // loop body
  while ((i <= n))
  {
    {
      (i = (i + 1));
      (sn = (sn + 1));
    }
    loopcheck(i, n, sn);
  }

  postcheck(i, n, sn);
  // post-condition
  if ((sn != n))
    assert((sn == 0));
}
