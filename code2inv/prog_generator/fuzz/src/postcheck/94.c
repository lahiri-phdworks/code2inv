#include <94.h>
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

#define INV(i, j, k, n) PHI

// COMMENT : precheck template
void precheck(int i, int j, int k, int n)
{
  char buffer[30];
  fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "j", j, "k", k, "n", n);
  aflcrash(INV(i, j, k, n));
}
// COMMENT : loopcheck template
void loopcheck(int i, int j, int k, int n)
{
  char buffer[30];
  fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "j", j, "k", k, "n", n);
  aflcrash(INV(i, j, k, n));
}
// COMMENT : postcheck template
void post(int i, int j, int k, int n)
{
  char buffer[30];
  fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d\n", "i", i, "j", j, "k", k, "n", n);
  aflcrash(INV(i, j, k, n));
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
  int k;
  int n;

  scanf("%d", &k);
  scanf("%d", &n);
  freopen("postmodels.txt", "w", stderr);

  // pre-conditions
  assume((-10000 <= k && k <= 10000));
  assume((-10000 <= n && n <= 10000));
  (i = 0);
  (j = 0);

  // post-check program
  assume(INV(i, j, k, n));
  assume(!(i <= n));
  fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d\n", i, j, k, n);
  // post-condition
  assert(((i + (j + k)) > (2 * n)));
}
