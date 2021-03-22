// #include <32.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

/* this lets the source compile without afl-clang-fast/lto */
#ifndef __AFL_FUZZ_TESTCASE_LEN

ssize_t fuzz_len;
unsigned char fuzz_buf[1024000];

#define __AFL_FUZZ_TESTCASE_LEN fuzz_len
#define __AFL_FUZZ_TESTCASE_BUF fuzz_buf
#define __AFL_FUZZ_INIT() void sync(void);
#define __AFL_LOOP(x) \
  ((fuzz_len = read(0, fuzz_buf, sizeof(fuzz_buf))) > 0 ? 1 : 0)
#define __AFL_INIT() sync()

#endif

__AFL_FUZZ_INIT();

#define aflcrash(cond, flag) \
  if (!cond)                 \
  {                          \
    flag = 1;                \
  }

// Guide AFL to proper values
// exit(0) is not a crash
#define assume(cond) \
  if (!cond)         \
    continue;

#define INV(n, v1, v2, v3, x) (x < (10000 - 1) || (n > (-10000 + n) && n == (10000 * n)) || n <= (n - x))

int preflag = 0, loopflag = 0, postflag = 0;

// TODO : Automate generation of this snippet
void precheck(int n, int v1, int v2, int v3, int x, int preflag)
{
  int f = preflag;
  aflcrash(INV(n, v1, v2, v3, x), preflag);
  if (f == 0 && preflag == 1)
    printf("Pre : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\npreflag : %d\n", "n", n, "v1", v1, "v2", v2, "v3", v3, "x", x, preflag);
}

// TODO : Automate generation of this snippet
void loopcheck(int n, int v1, int v2, int v3, int x, int loopflag)
{
  printf("Loop : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\nloopflag : %d\n", "n", n, "v1", v1, "v2", v2, "v3", v3, "x", x, loopflag);
  aflcrash(INV(n, v1, v2, v3, x), loopflag);
}

// TODO : Automate generation of this snippet
void postcheck(int n, int v1, int v2, int v3, int x, int postflag)
{
  printf("Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\npostflag : %d\n", "n", n, "v1", v1, "v2", v2, "v3", v3, "x", x, postflag);
  aflcrash(INV(n, v1, v2, v3, x), postflag);
}

int choices[] = {1, -1, 1, -1, 1, 1, -1, 1, -2, -1, 0, 0, 0, 1, 1, -1, 1, 0, 1, -1, 1, 1, 2, 1};
int unknown()
{
  int nums = sizeof(choices) / sizeof(choices[0]);
  return choices[(rand() % nums) - 1];
}

/* To ensure checks are not optimized out it is recommended to disable
   code optimization for the fuzzer harness main() */
#pragma clang optimize off
#pragma GCC optimize("O0")

int main(int argc, const char **argv)
{

  unsigned char *buf = __AFL_FUZZ_TESTCASE_BUF;

  // variable declarations
  int n;
  int v1;
  int v2;
  int v3;
  int choice;

  // int preflag = 0, loopflag = 0, postflag = 0;
  freopen("models.txt", "a", stdout);
  // printf("Fuzzing Starts\n");

  read(0, &n, sizeof(int));
  read(0, &choice, sizeof(int));

  __AFL_INIT();
  while (__AFL_LOOP(1000000000))
  {

    int len = __AFL_FUZZ_TESTCASE_LEN;

    // pre-conditions
    // n = 0;
    // choice = 0;

    // AFL Sanity
    // assume((-10000 <= n && n <= 10000));

    // printf("Fuzzing Loop\n");
    // printf("n : %d, choice : %d\n", n, choice);
    int x;

    if (choice > 0)
    {
      // printf("Pre-body\n");
      assume((preflag == 0));
      x = n;
      precheck(n, v1, v2, v3, x, preflag);
    }
    else
    {
      // We try this optimization later.
      // assume((loopflag + postflag < 2));
      assume(INV(n, v1, v2, v3, x));

      // Loop Condition.
      if (x > 1)
      {
        // printf("Loop-body\n");
        assume((loopflag == 0));
        x -= 1;
        loopcheck(n, v1, v2, v3, x, loopflag);
      }
      else
      {
        // printf("Post-body\n");
        assume((postflag == 0));
        if ((n >= 0))
        {
          aflcrash((x == 1), postflag);
          if (postflag == 1)
          {
            printf("Post : %s : %d, %s : %d, %s : %d, %s : %d, %s : %d\npostflag : %d\n", "n", n, "v1", v1, "v2", v2, "v3", v3, "x", x, postflag);
          }
        }
        if ((postflag + loopflag + preflag >= 3))
        {
          assert(0);
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
