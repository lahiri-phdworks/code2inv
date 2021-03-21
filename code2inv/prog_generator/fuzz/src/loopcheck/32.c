#include <32.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define aflcrash(cond, flag) \
  if (!cond)                 \
    flag = 1;

// Guide AFL to proper values
// exit(0) is not a crash
#define assume(cond) \
  if (!cond)         \
    exit(0);

#define INV(n, v1, v2, v3, x) PHI

int preflag = 0, loopflag = 0, postflag = 0;

// TODO : Automate generation of this snippet
void precheck(int n, int v1, int v2, int v3, int x, int preflag)
{
  int f = preflag;
  aflcrash(INV(n, v1, v2, v3, x), preflag);
  if (f == 0 && preflag == 1)
    fprintf(stderr, "Pre : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\npreflag : %d\n", "n", n, "v1", v1, "v2", v2, "v3", v3, "x", x, preflag);
}

// TODO : Automate generation of this snippet
void loopcheck(int n, int v1, int v2, int v3, int x, int loopflag)
{
  fprintf(stderr, "Loop : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\nloopflag : %d\n", "n", n, "v1", v1, "v2", v2, "v3", v3, "x", x, loopflag);
  aflcrash(INV(n, v1, v2, v3, x), loopflag);
}

// TODO : Automate generation of this snippet
void postcheck(int n, int v1, int v2, int v3, int x, int postflag)
{
  fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\npostflag : %d\n", "n", n, "v1", v1, "v2", v2, "v3", v3, "x", x, postflag);
  aflcrash(INV(n, v1, v2, v3, x), postflag);
}

int choices[] = {1, -1, 1, -1, 1, 1, -1, 1, -2, -1, 0, 0, 0, 1, 1, -1, 1, 0, 1, -1, 1, 1, 2, 1};
int unknown()
{
  int nums = sizeof(choices) / sizeof(choices[0]);
  return choices[(rand() % nums) - 1];
}

int main(int argc, const char **argv)
{
  // variable declarations
  int n;
  int v1;
  int v2;
  int v3;
  int x;
  int choice;

  // int preflag = 0, loopflag = 0, postflag = 0;
  freopen(argv[1], "a", stderr);

  // while (__AFL_LOOP(1000))
  {
    // pre-conditions
    read(0, &n, sizeof(int));
    read(0, &choice, sizeof(int));

    // AFL Sanity
    assume((-10000 <= n && n <= 10000));

    if (choice > 0)
    {
      assume((preflag == 0));
      x = n;
      precheck(n, v1, v2, v3, x, preflag);
    }
    else
    {
      assume((loopflag + postflag < 2));
      assume(INV(n, v1, v2, v3, x));

      // Loop Condition.
      if (x > 1)
      {
        assume((loopflag == 0));
        x -= 1;
        loopcheck(n, v1, v2, v3, x, loopflag);
      }
      else
      {
        assume((postflag == 0));
        if ((n >= 0))
        {
          aflcrash((x == 1), postflag);
          if (postflag == 1)
          {
            fprintf(stderr, "Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\npostflag : %d\n", "n", n, "v1", v1, "v2", v2, "v3", v3, "x", x, postflag);
          }
        }
      }
    }
  }

  // (x = n);

  // // loop body
  // assume(INV(n, v1, v2, v3, x));
  // assume((x > 1))
  // {
  //   (x = (x - 1));
  // }
  // loopcheck(n, v1, v2, v3, x);
}
