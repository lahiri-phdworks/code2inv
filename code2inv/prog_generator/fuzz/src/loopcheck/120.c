#include <120.h>
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

#define INV(i, sn) PHI

// TODO : Automate generation of this snippet
void loopcheck(int i, int sn)
{
  char buffer[30];
  fprintf(stderr, "Loop : %s : %d, %s : %d\n", "i", i, "sn", sn);
  aflcrash(INV(i, sn));
}

// TODO : Automate generation of this snippet
void postcheck(int i, int sn)
{
  char buffer[30];
  fprintf(stderr, "Post : %s : %d, %s : %d\n", "i", i, "sn", sn);
  aflcrash(INV(i, sn));
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
  int sn;

  freopen("loopmodels.txt", "w", stderr);

  scanf("%d", &sn);
  scanf("%d", &i);

  // pre-conditions
  (sn = 0);
  (i = 1);

  // loop body
  assume(INV(i, sn));
  assume((i <= 8));
  (i = (i + 1));
  (sn = (sn + 1));
  loopcheck(i, sn);
}
