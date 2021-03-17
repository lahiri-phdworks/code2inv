#include <23.h>
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

#define INV(i, j) PHI

// COMMENT : loopcheck template
void loopcheck(int i, int j)
{
  char buffer[30];
  fprintf(stderr, "Loop : %s : %d, %s : %d\n", "i", i, "j", j);
  aflcrash(INV(i, j));
}
// COMMENT : postcheck template
void post(int i, int j)
{
  char buffer[30];
  fprintf(stderr, "Post : %s : %d, %s : %d\n", "i", i, "j", j);
  aflcrash(INV(i, j));
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
  int j;

  scanf("%d", &i);
  freopen("loopmodels.txt", "w", stderr);

  // pre-conditions
  (i = 1);
  (j = 20);

  // loopcond : (j >= i)
  // loop-check program
  assume(INV(i, j));
  assume((j >= i));
  // loop body
  {
    {
      (i = (i + 2));
      (j = (j - 1));
    }
  }
  loopcheck(i, j);
}
