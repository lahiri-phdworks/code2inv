#include <116.h>
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

#define INV(sn, v1, v2, v3, x) PHI

// TODO : Automate generation of this snippet
void precheck(int sn, int v1, int v2, int v3, int x)
{
  char buffer[30];
  fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "n", sn, "v1", v1, "v2", v2, "v3", v3, "x", x);
  aflcrash(INV(sn, v1, v2, v3, x));
}

// TODO : Automate generation of this snippet
void loopcheck(int sn, int v1, int v2, int v3, int x)
{
  char buffer[30];
  fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "n", sn, "v1", v1, "v2", v2, "v3", v3, "x", x);
  aflcrash(INV(sn, v1, v2, v3, x));
}

// TODO : Automate generation of this snippet
void postcheck(int sn, int v1, int v2, int v3, int x)
{
  char buffer[30];
  fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "n", sn, "v1", v1, "v2", v2, "v3", v3, "x", x);
  aflcrash(INV(sn, v1, v2, v3, x));
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
  int sn;
  int v1;
  int v2;
  int v3;
  int x;

  freopen("postmodels.txt", "w", stderr);

  scanf("%d", &sn);
  scanf("%d", &x);

  // pre-conditions
  (sn = 0);
  (x = 0);

  // loop body
  (x = (x + 1));
  (sn = (sn + 1));

  // post-condition
  assume(INV(sn, v1, v2, v3, x));
  if ((sn != x))
  {
    char buffer[30];
    fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\n", "n", sn, "v1", v1, "v2", v2, "v3", v3, "x", x);
    assert((sn == -1));
  }
}
