#include <121.h>
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

#define INV(i, sn) PHI

// COMMENT : precheck template
void precheck(int i, int sn)
{
  char buffer[30];
  fprintf(stderr, "Pre : %s : %d, %s : %d\n", "i", i, "sn", sn);
  aflcrash(INV(i, sn));
}
// COMMENT : loopcheck template
void loopcheck(int i, int sn)
{
  char buffer[30];
  fprintf(stderr, "Loop : %s : %d, %s : %d\n", "i", i, "sn", sn);
  aflcrash(INV(i, sn));
}
// COMMENT : postcheck template
void post(int i, int sn)
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

  scanf("%d", &i);
  freopen("premodels.txt", "w", stderr);

  // pre-conditions
  assume((-10000 <= i && i <= 10000));
  (sn = 0);
  (i = 1);
  precheck(i, sn);
}
