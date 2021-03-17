#include <35.h>
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

#define INV(c) PHI

// COMMENT : precheck template
void precheck(int c)
{
  char buffer[30];
  fprintf(stderr, "Pre : %s : %d\n", "c", c);
  aflcrash(INV(c));
}
// COMMENT : loopcheck template
void loopcheck(int c)
{
  char buffer[30];
  fprintf(stderr, "Loop : %s : %d\n", "c", c);
  aflcrash(INV(c));
}
// COMMENT : postcheck template
void post(int c)
{
  char buffer[30];
  fprintf(stderr, "Post : %s : %d\n", "c", c);
  aflcrash(INV(c));
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
  int c;

  scanf("%d", &c);
  freopen("postmodels.txt", "w", stderr);

  // pre-conditions
  (c = 0);

  // post-check program
  assume(INV(c));
  assume(!(unknown()));
  fprintf(stderr, "Post : %s : %d\n", c);
  // post-condition
  if ((c != 40))
    assert((c >= 0));
}
